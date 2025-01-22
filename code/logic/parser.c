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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern char *_custom_strdup(const char *str);


// Helper function to create a new argument
static fossil_sanity_parser_argument_t* fossil_sanity_parser_create_argument(const char *name, fossil_sanity_parser_arg_type_t type) {
    fossil_sanity_parser_argument_t *arg = (fossil_sanity_parser_argument_t*)malloc(sizeof(fossil_sanity_parser_argument_t));
    arg->name = _custom_strdup(name);
    arg->type = type;
    arg->value = NULL;
    arg->next = NULL;
    return arg;
}

// Helper function to create a new command
static fossil_sanity_parser_command_t* fossil_sanity_parser_create_command(const char *name, const char *description) {
    fossil_sanity_parser_command_t *command = (fossil_sanity_parser_command_t*)malloc(sizeof(fossil_sanity_parser_command_t));
    command->name = _custom_strdup(name);
    command->description = _custom_strdup(description);
    command->arguments = NULL;
    command->prev = NULL;
    command->next = NULL;
    return command;
}

// Create a command palette
fossil_sanity_parser_palette_t* fossil_sanity_parser_create_palette(const char *name, const char *description) {
    fossil_sanity_parser_palette_t *palette = (fossil_sanity_parser_palette_t*)malloc(sizeof(fossil_sanity_parser_palette_t));
    palette->name = _custom_strdup(name);
    palette->description = _custom_strdup(description);
    palette->commands = NULL;
    return palette;
}

// Add a command to the command palette
void fossil_sanity_parser_add_command(fossil_sanity_parser_palette_t *palette, const char *command_name, const char *description) {
    fossil_sanity_parser_command_t *command = fossil_sanity_parser_create_command(command_name, description);
    
    if (!palette->commands) {
        palette->commands = command;
    } else {
        fossil_sanity_parser_command_t *last = palette->commands;
        while (last->next) {
            last = last->next;
        }
        last->next = command;
        command->prev = last;
    }
}

// Add an argument to a command
void fossil_sanity_parser_add_argument(fossil_sanity_parser_command_t *command, const char *arg_name, fossil_sanity_parser_arg_type_t arg_type) {
    fossil_sanity_parser_argument_t *arg = fossil_sanity_parser_create_argument(arg_name, arg_type);
    
    if (!command->arguments) {
        command->arguments = arg;
    } else {
        fossil_sanity_parser_argument_t *last = command->arguments;
        while (last->next) {
            last = last->next;
        }
        last->next = arg;
    }
}

// Parse the arguments from the command line input
void fossil_sanity_parser_parse(fossil_sanity_parser_palette_t *palette, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        bool found_command = false;
        fossil_sanity_parser_command_t *command = palette->commands;

        while (command) {
            if (strcmp(argv[i], command->name) == 0) {
                printf("Executing command: %s\n", command->name);
                found_command = true;
                fossil_sanity_parser_argument_t *arg = command->arguments;

                for (int j = i + 1; j < argc && arg; j++, arg = arg->next) {
                    if (arg->type == FOSSIL_SANITY_PARSER_BOOL) {
                        if (strcmp(argv[j], "enable") == 0) {
                            arg->value = (void*)1; // Set to true
                        } else if (strcmp(argv[j], "disable") == 0) {
                            arg->value = (void*)0; // Set to false
                        }
                    } else if (arg->type == FOSSIL_SANITY_PARSER_STRING) {
                        arg->value = _custom_strdup(argv[j]);
                    } else if (arg->type == FOSSIL_SANITY_PARSER_INT) {
                        long int val = strtol(argv[j], NULL, 10);
                        arg->value = (void*)(intptr_t)val; // Cast to intptr_t before casting to void*
                    }
                }
                break;
            }
            command = command->next;
        }
        if (!found_command) {
            printf("Unknown command: %s\n", argv[i]);
        }
    }
}

// Free memory allocated for the command palette and all its commands and arguments
void fossil_sanity_parser_free(fossil_sanity_parser_palette_t *palette) {
    if (!palette) return;

    fossil_sanity_parser_command_t *command = palette->commands;
    while (command) {
        fossil_sanity_parser_argument_t *arg = command->arguments;
        while (arg) {
            free(arg->name);
            if (arg->value && arg->type == FOSSIL_SANITY_PARSER_STRING) {
                free(arg->value);
            }
            fossil_sanity_parser_argument_t *temp = arg;
            arg = arg->next;
            free(temp);
        }
        free(command->name);
        free(command->description);
        fossil_sanity_parser_command_t *temp = command;
        command = command->next;
        free(temp);
    }
    free(palette->name);
    free(palette->description);
    free(palette);
}
