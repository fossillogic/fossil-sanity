/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/sanity/parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

// Static storage for options and subcommands
#define MAX_OPTIONS 100
#define MAX_SUBCOMMANDS 10
#define MAX_LINE_LENGTH 256

static fossil_sanity_parser_option_t options[MAX_OPTIONS];
static int option_count = 0;

static fossil_sanity_parser_subcommand_t subcommands[MAX_SUBCOMMANDS];
static int subcommand_count = 0;

// Add a CLI option
void fossil_sanity_parser_add_option(const char *name, char short_name, fossil_sanity_parser_option_type_t type, void *value, const char *description) {
    if (option_count >= MAX_OPTIONS) {
        fprintf(stderr, "Error: Maximum number of options reached.\n");
        exit(EXIT_FAILURE);
    }
    options[option_count++] = (fossil_sanity_parser_option_t){name, short_name, type, value, description};
}

// Add a subcommand
void fossil_sanity_parser_add_subcommand(const char *name, const char *description, fossil_sanity_parser_option_t *options, int option_count, int (*handler)(int argc, char **argv)) {
    if (subcommand_count >= MAX_SUBCOMMANDS) {
        fprintf(stderr, "Error: Maximum number of subcommands reached.\n");
        exit(EXIT_FAILURE);
    }
    subcommands[subcommand_count++] = (fossil_sanity_parser_subcommand_t){name, options, option_count, description, handler};
}

// Parse the CLI arguments
int fossil_sanity_parser_parse(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        // Check for subcommand
        for (int j = 0; j < subcommand_count; ++j) {
            if (strcmp(argv[i], subcommands[j].name) == 0) {
                return subcommands[j].handler(argc - i, &argv[i]);
            }
        }

        // Check for options
        for (int j = 0; j < option_count; ++j) {
            if (strcmp(argv[i], options[j].name) == 0 || 
               (options[j].short_name && argv[i][0] == '-' && argv[i][1] == options[j].short_name)) {
                switch (options[j].type) {
                    case FOSSIL_SANITY_PARSER_TYPE_BOOL:
                        *(bool *)options[j].value = true;
                        break;
                    case FOSSIL_SANITY_PARSER_TYPE_INT:
                        if (i + 1 < argc) *(int *)options[j].value = atoi(argv[++i]);
                        else return -1;
                        break;
                    case FOSSIL_SANITY_PARSER_TYPE_STRING:
                        if (i + 1 < argc) {
                            free(*(char **)options[j].value);  // Free existing memory
                            *(char **)options[j].value = strdup(argv[++i]);
                        } else return -1;
                        break;
                    case FOSSIL_SANITY_PARSER_TYPE_ARRAY:
                        if (i + 1 < argc) {
                            free(*(char **)options[j].value);  // Free existing memory
                            *(char **)options[j].value = strdup(argv[++i]);
                        } else return -1;
                        break;
                    case FOSSIL_SANITY_PARSER_TYPE_FEATURE:
                        *(bool *)options[j].value = strcmp(argv[++i], "enable") == 0;
                        break;
                    default:
                        return -1;
                }
            }
        }
    }
    return 0;
}

// Print help for all commands and options
void fossil_sanity_parser_print_help(void) {
    printf("Usage:\n");
    for (int i = 0; i < subcommand_count; ++i) {
        printf("  %s: %s\n", subcommands[i].name, subcommands[i].description);
        for (int j = 0; j < subcommands[i].option_count; ++j) {
            printf("    --%s, -%c: %s\n", subcommands[i].options[j].name, subcommands[i].options[j].short_name, subcommands[i].options[j].description);
        }
    }
    for (int i = 0; i < option_count; ++i) {
        printf("  --%s, -%c: %s\n", options[i].name, options[i].short_name, options[i].description);
    }
}

// Cleanup function
void fossil_sanity_parser_cleanup(void) {
    for (int i = 0; i < option_count; ++i) {
        if (options[i].type == FOSSIL_SANITY_PARSER_TYPE_STRING || options[i].type == FOSSIL_SANITY_PARSER_TYPE_ARRAY) {
            free(*(char **)options[i].value);
            *(char **)options[i].value = NULL;
        }
    }
}

// ==================================================================
// INI file handling
// ==================================================================

// Helper function: Trim whitespace
static char *trim_whitespace(char *str) {
    if (!str) return NULL;

    // Trim leading whitespace
    while (isspace((unsigned char)*str)) str++;

    // If string is empty, return it
    if (*str == '\0') return str;

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    return str;
}

// Load INI file
int fossil_sanity_parser_load_ini(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open INI file '%s'\n", file_path);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    char current_section[MAX_LINE_LENGTH] = {0};

    while (fgets(line, sizeof(line), file)) {
        // Ensure null-termination of the line
        line[MAX_LINE_LENGTH - 1] = '\0';
        char *trimmed = trim_whitespace(line);
        if (!trimmed || *trimmed == '#' || *trimmed == ';' || *trimmed == '\0') {
            continue;  // Skip comments or empty lines
        }

        if (*trimmed == '[') {
            // Section line (e.g., [section])
            char *end = strchr(trimmed, ']');
            if (!end) {
                fprintf(stderr, "Error: Malformed section header in INI file.\n");
                fclose(file);
                return -1;
            }
            *end = '\0';
            snprintf(current_section, sizeof(current_section), "%s", trimmed + 1);
        } else {
            // Key-value pair
            char *equals = strchr(trimmed, '=');
            if (!equals) {
                fprintf(stderr, "Error: Malformed key-value pair in INI file.\n");
                fclose(file);
                return -1;
            }
            *equals = '\0';
            char *key = trim_whitespace(trimmed);
            char *value = trim_whitespace(equals + 1);

            if (!key || !value) {
                fprintf(stderr, "Error: Missing key or value in INI file.\n");
                fclose(file);
                return -1;
            }

            // Match key with options
            for (int i = 0; i < option_count; i++) {
                if (strcmp(options[i].name, key) == 0) {
                    switch (options[i].type) {
                        case FOSSIL_SANITY_PARSER_TYPE_BOOL:
                            *(int *)options[i].value = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
                            break;
                        case FOSSIL_SANITY_PARSER_TYPE_INT:
                            *(int *)options[i].value = atoi(value);
                            break;
                        case FOSSIL_SANITY_PARSER_TYPE_STRING:
                            snprintf((char *)options[i].value, MAX_LINE_LENGTH, "%s", value);
                            break;
                        case FOSSIL_SANITY_PARSER_TYPE_ARRAY:
                            snprintf((char *)options[i].value, MAX_LINE_LENGTH, "%s", value);
                            break;
                        case FOSSIL_SANITY_PARSER_TYPE_FEATURE:
                            *(int *)options[i].value = (strcmp(value, "enabled") == 0);
                            break;
                        default:
                            fprintf(stderr, "Error: Unknown option type.\n");
                            fclose(file);
                            return -1;
                    }
                }
            }
        }
    }

    fclose(file);
    return 0;
}

// Save INI file
int fossil_sanity_parser_save_ini(const char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (!file) {
        fprintf(stderr, "Error: Unable to open INI file '%s' for writing\n", file_path);
        return -1;
    }

    fprintf(file, "# Generated INI file\n");
    fprintf(file, "\n[settings]\n");

    for (int i = 0; i < option_count; i++) {
        switch (options[i].type) {
            case FOSSIL_SANITY_PARSER_TYPE_BOOL:
                fprintf(file, "%s=%s\n", options[i].name, (*(int *)options[i].value) ? "true" : "false");
                break;
            case FOSSIL_SANITY_PARSER_TYPE_INT:
                fprintf(file, "%s=%d\n", options[i].name, *(int *)options[i].value);
                break;
            case FOSSIL_SANITY_PARSER_TYPE_STRING:
                fprintf(file, "%s=%s\n", options[i].name, (char *)options[i].value);
                break;
            case FOSSIL_SANITY_PARSER_TYPE_ARRAY:
                fprintf(file, "%s=%s\n", options[i].name, (char *)options[i].value);
                break;
            case FOSSIL_SANITY_PARSER_TYPE_FEATURE:
                fprintf(file, "%s=%s\n", options[i].name, (*(int *)options[i].value) ? "enabled" : "disabled");
                break;
            default:
                fprintf(stderr, "Error: Unknown option type.\n");
                fclose(file);
                return -1;
        }
    }

    if (fclose(file) != 0) {
        fprintf(stderr, "Error: Failed to close INI file '%s'.\n", file_path);
        return -1;
    }

    return 0;
}

// ==================================================================
// AI enhancements
// ==================================================================

// Levenshtein distance calculation
static int levenshtein_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = fmin(dp[i - 1][j] + 1,       // Deletion
                            fmin(dp[i][j - 1] + 1,  // Insertion
                                 dp[i - 1][j - 1] + cost)); // Substitution
        }
    }

    return dp[len1][len2];
}

// Suggest corrections for invalid commands
void fossil_sanity_parser_suggest_correction(const char *invalid_command) {
    printf("Invalid command: %s\n", invalid_command);

    int best_match_index = -1;
    int min_distance = INT_MAX;

    for (int i = 0; i < option_count; ++i) {
        int distance = levenshtein_distance(invalid_command, options[i].name);
        if (distance < min_distance) {
            min_distance = distance;
            best_match_index = i;
        }
    }

    if (best_match_index >= 0 && min_distance <= 3) {  // Allow suggestions if the match is "close enough"
        printf("Did you mean: --%s?\n", options[best_match_index].name);
    } else {
        printf("No similar commands found. Use --help for a list of valid options.\n");
    }
}

// Set defaults for options using AI logic
void fossil_sanity_parser_set_defaults_with_ai(void) {
    for (int i = 0; i < option_count; ++i) {
        // Handle each type of option intelligently
        switch (options[i].type) {
            case FOSSIL_SANITY_PARSER_TYPE_BOOL:
                if (*(bool *)options[i].value == false) {
                    // Enable by default if it's a feature or critical setting
                    if (strstr(options[i].name, "enable") || strstr(options[i].name, "feature")) {
                        *(bool *)options[i].value = true;
                    } else {
                        *(bool *)options[i].value = false;
                    }
                }
                break;

            case FOSSIL_SANITY_PARSER_TYPE_INT:
                if (*(int *)options[i].value == 0) {
                    // Suggest common default values for integers
                    if (strstr(options[i].name, "timeout")) {
                        *(int *)options[i].value = 30;  // 30 seconds default for timeouts
                    } else if (strstr(options[i].name, "max") || strstr(options[i].name, "limit")) {
                        *(int *)options[i].value = 100;  // Default limit
                    } else if (strstr(options[i].name, "retries")) {
                        *(int *)options[i].value = 3;  // Default retries
                    }
                }
                break;

            case FOSSIL_SANITY_PARSER_TYPE_STRING:
                if (strlen((char *)options[i].value) == 0) {
                    // Suggest default strings based on the name
                    if (strstr(options[i].name, "username")) {
                        strncpy((char *)options[i].value, "default_user", MAX_LINE_LENGTH - 1);
                    } else if (strstr(options[i].name, "path")) {
                        strncpy((char *)options[i].value, "/default/path", MAX_LINE_LENGTH - 1);
                    }
                }
                break;

            case FOSSIL_SANITY_PARSER_TYPE_ARRAY:
                if (strlen((char *)options[i].value) == 0) {
                    // Set default for arrays (e.g., IP ranges)
                    if (strstr(options[i].name, "ips")) {
                        strncpy((char *)options[i].value, "127.0.0.1", MAX_LINE_LENGTH - 1);  // Default to localhost
                    }
                }
                break;

            case FOSSIL_SANITY_PARSER_TYPE_FEATURE:
                if (*(int *)options[i].value == 0) {
                    // Default to enabled for features
                    *(int *)options[i].value = 1;
                }
                break;

            default:
                fprintf(stderr, "Warning: Unknown option type for '%s'. No default applied.\n", options[i].name);
                break;
        }

        // Optional debug output for testing
        printf("Default set for '%s': ", options[i].name);
        switch (options[i].type) {
            case FOSSIL_SANITY_PARSER_TYPE_BOOL:
                printf("%s\n", (*(bool *)options[i].value) ? "true" : "false");
                break;
            case FOSSIL_SANITY_PARSER_TYPE_INT:
                printf("%d\n", *(int *)options[i].value);
                break;
            case FOSSIL_SANITY_PARSER_TYPE_STRING:
            case FOSSIL_SANITY_PARSER_TYPE_ARRAY:
                printf("%s\n", (char *)options[i].value);
                break;
            case FOSSIL_SANITY_PARSER_TYPE_FEATURE:
                printf("%s\n", (*(int *)options[i].value) ? "enabled" : "disabled");
                break;
        }
    }
}
