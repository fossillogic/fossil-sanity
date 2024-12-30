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
#include "fossil/sanity/sanity.h"
#include <stdarg.h>
#include <ctype.h>

// Dynamic responses for each log level (30 responses per category)
static const char *fossil_sanity_responses[][30] = {
    // PROD responses
    {
        "Operation completed successfully.",
        "All tasks finished without any issues.",
        "Process completed with no errors.",
        "Everything is running smoothly.",
        "No problems encountered during execution.",
        "Task completed as expected.",
        "Success: All actions are validated.",
        "Execution was flawless.",
        "No errors were found.",
        "Everything is fine, no issues detected.",
        "The operation was successful without any issues.",
        "The system is working as intended.",
        "The process finished successfully with no hitches.",
        "The task was completed without any failure.",
        "Success: No errors were encountered.",
        "The system is running efficiently.",
        "Operation successful: No problems found.",
        "The result is satisfactory.",
        "The task was completed in a timely manner.",
        "No errors or problems during execution.",
        "The operation has been verified as correct.",
        "The action was performed successfully.",
        "System performance is stable.",
        "Everything completed without any interruptions.",
        "All tests passed successfully.",
        "Success: Operation finished cleanly.",
        "Everything is working perfectly.",
        "The result is as expected.",
        "Task completed with no significant issues."
    },

    // WARN responses
    {
        "Warning: Potential issue detected.",
        "Caution: Something might need attention.",
        "Notice: Minor irregularity observed.",
        "Warning: The operation might not be fully optimal.",
        "Alert: This action might cause unexpected results.",
        "Minor issue detected, but proceeding.",
        "Warning: Unusual behavior observed.",
        "Alert: Consider reviewing the output.",
        "Notice: There's a slight anomaly in the process.",
        "Warning: Something seems off, proceed with caution.",
        "Warning: This might affect performance, check details.",
        "Heads up: A small issue was found.",
        "Notice: Not critical, but worth considering.",
        "Warning: The result could be improved.",
        "Alert: This operation might need additional checks.",
        "Notice: Potential improvement found in the process.",
        "Warning: A minor issue could impact future results.",
        "Heads up: You might want to adjust some settings.",
        "Notice: A potential issue was noted during the process.",
        "Warning: This task may need re-evaluation.",
        "Alert: It’s suggested to verify the settings.",
        "Notice: There could be an issue with the configuration.",
        "Warning: Some settings may not be optimal.",
        "Heads up: Verify configuration to prevent problems.",
        "Warning: The task executed, but with minor issues.",
        "Notice: Check the configuration for possible improvements.",
        "Alert: Results are as expected, but some variance exists.",
        "Warning: Proceeding with minor concerns."
    },

    // ERROR responses
    {
        "Error: The operation failed unexpectedly.",
        "Critical error encountered during execution.",
        "Error: The task could not be completed.",
        "An error occurred, halting the process.",
        "Operation failed: Unable to proceed.",
        "Error: Invalid configuration detected.",
        "The process failed to complete successfully.",
        "System error: Action could not be executed.",
        "Error: Unexpected failure encountered.",
        "An error has interrupted the operation.",
        "Process aborted due to an error.",
        "Critical error: Immediate attention needed.",
        "Error: Unexpected result, operation aborted.",
        "Failure detected, unable to proceed.",
        "Error: Problem encountered while processing.",
        "Error: Action could not be completed.",
        "System failure: Unable to continue.",
        "Error: Unable to proceed with the given input.",
        "Critical failure: Immediate action required.",
        "Error: Task completion was unsuccessful.",
        "Operation failed: Unexpected error occurred.",
        "Error: Configuration mismatch detected.",
        "Critical error: Intervention required immediately.",
        "Error: Execution was halted due to failure.",
        "Process terminated due to error.",
        "Error: Unable to process the requested action.",
        "Error: An issue has prevented completion.",
        "System error: Please check logs for more details.",
        "Error: Operation could not be finished."
    },

    // CRITICAL responses
    {
        "Critical: System failure, immediate action required.",
        "Critical issue: Immediate intervention needed.",
        "Critical failure: The system is not responsive.",
        "System-wide failure: Immediate attention is required.",
        "Critical issue encountered: Action must be taken immediately.",
        "Major failure detected: The system is unstable.",
        "Critical error: System is at risk of crashing.",
        "Critical system failure: Action required immediately.",
        "Immediate action required: Critical issue detected.",
        "System-wide shutdown required: Critical issue found.",
        "Critical failure: All operations halted.",
        "Critical failure detected: System instability.",
        "Immediate action required: The system is compromised.",
        "Critical error: The process is not recoverable.",
        "System failure: No further actions possible.",
        "Critical issue: The process has failed completely.",
        "Critical: Urgent fix needed to avoid downtime.",
        "Critical: Severe instability detected.",
        "Failure: The system is unable to recover.",
        "System failure: Data may be compromised.",
        "Immediate shutdown: The system cannot continue.",
        "Critical failure: Restart the system to continue.",
        "System failure: Essential services are down.",
        "Critical: Unable to continue operation.",
        "Critical error: Major system fault detected.",
        "System compromised: Immediate fix needed.",
        "Critical failure: Unable to recover the system.",
        "System down: Critical failure in progress.",
        "Critical: Please escalate to a senior technician."
    },

    // DEBUG responses
    {
        "Debug: Internal status check successful.",
        "Debug: Verbose output shows no anomalies.",
        "Debug: All debug checks have completed successfully.",
        "Debug: Internal log shows normal operation.",
        "Debug: Debug mode active, no issues detected.",
        "Debug: Verbose logging enabled for analysis.",
        "Debug: All test cases passed successfully.",
        "Debug: Output matched expected results.",
        "Debug: Verbose mode reveals no significant errors.",
        "Debug: No errors found in debug mode.",
        "Debug: Internal check passed without errors.",
        "Debug: Debug output shows expected results.",
        "Debug: Diagnostics show no operational issues.",
        "Debug: Verbose log confirms expected behavior.",
        "Debug: All internal checks return normal values.",
        "Debug: Debugging process completed without issues.",
        "Debug: The system is functioning as expected.",
        "Debug: No discrepancies found in debug mode.",
        "Debug: No debug-level issues were encountered.",
        "Debug: Diagnostic checks completed successfully.",
        "Debug: Verbose log confirms correct configuration.",
        "Debug: Output matches expected debug-level details.",
        "Debug: Internal status matches anticipated values.",
        "Debug: Debugging completed without incident.",
        "Debug: Verbose logging shows all systems running smoothly.",
        "Debug: Internal test passed with no errors.",
        "Debug: No issues detected during debug execution.",
        "Debug: Debugging confirmed all components are functional.",
        "Debug: Output verification complete, no issues found."
    }
};

const char *ARTICLES[] = {
    "a", "an", "the"
};

const char *NOUNS[] = {
    "message", "example", "sentence", "structure", "clarity", "grammar", "system", "operation", "task", "process",
    "result", "issue", "error", "failure", "problem", "configuration", "output", "input", "log", "level", "response",
    "action", "attention", "behavior", "check", "details", "execution", "intervention", "performance", "settings",
    "shutdown", "stability", "status", "verification"
};

const char *VERBS[] = {
    "is", "are", "was", "were", "be", "being", "been", "has", "have", "does", "do", "completed",
    "detected", "encountered", "executed", "failed", "found", "halted", "interrupted", "logged", "matched", "observed",
    "passed", "performed", "proceeded", "processed", "recovered", "required", "returned", "running", "showed", "terminated",
    "validated", "verified"
};

const char *PREPOSITIONS[] = {
    "in", "on", "at", "since", "for", "ago", "before", "to", "past", "by", "about", "under", "over", "with", "without", "between", "among"
};

const char *ADJECTIVES[] = {
    "clear", "good", "writing", "valid", "understandable", "correct", "incorrect", "poor", "vague", "long", "short",
    "unusual", "minor", "critical", "unexpected", "invalid", "unrecoverable", "unstable", "severe", "major", "immediate",
    "system-wide", "internal", "verbose", "normal", "expected", "successful", "flawless", "timely", "optimal", "unresponsive",
    "unrecoverable", "compromised", "unrecoverable", "essential", "severe", "major", "senior"
};

const char *ROTBRAIN[] = {
    "rizz", "skibidi", "yeet", "sus", "vibe", "lit", "no cap", "bet", "fam", "bruh",
    "flex", "ghost", "goat", "gucci", "hype", "janky", "lowkey", "mood", "salty", "shade",
    "slay", "snatched", "stan", "tea", "thirsty", "woke", "yolo", "zaddy", "drip", "fire"
};


char *custom_strdup(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str) {
        memcpy(new_str, str, len);
    }
    return new_str;
}

int custom_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (unsigned char)tolower((unsigned char)*s1);
        char c2 = (unsigned char)tolower((unsigned char)*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return (unsigned char)tolower((unsigned char)*s1) - (unsigned char)tolower((unsigned char)*s2);
}

// Get a random response based on the log level
const char *fossil_sanity_get_response(fossil_sanity_log_level level) {
    srand((unsigned int)time(NULL));
    int index = rand() % 30;  // Get a random response from the list (0-29)
    return fossil_sanity_responses[level][index];
}

// Color codes for each log level
static const char *fossil_sanity_color_codes[] = {
    "\033[1;32m", // Green: PROD
    "\033[1;33m", // Yellow: WARN
    "\033[1;31m", // Red: ERROR
    "\033[1;35m", // Magenta: CRITICAL
    "\033[1;36m"  // Cyan: DEBUG
};

// Reset color
#define COLOR_RESET "\033[0m"

// Initialize configuration
void fossil_sanity_init_config(fossil_sanity_config *config) {
    if (!config) {
        return;
    }

    config->debug_enabled = false;
    config->logs_enabled = true;
    config->log_level = FOSSIL_SANITY_LOG_WARN;
    config->log_output = NULL;
    config->use_colors = true;
}

// Log with filtering and colors
void fossil_sanity_log(const fossil_sanity_config *config, fossil_sanity_log_level level, const char *message, ...) {
    const char *level_str[] = {"PROD", "WARN", "ERROR", "CRITICAL", "DEBUG"};

    if (!config->logs_enabled || level > config->log_level) {
        return;
    }

    // Check if message is clear and grammatically correct
    if (!fossil_sanity_check_message_clarity(message)) {
        fprintf(stderr, "[ERROR] Message may confuse users: %s\n", message);
        return;
    }

    if (!fossil_sanity_check_grammar(message)) {
        fprintf(stderr, "[ERROR] Message contains grammatical issues: %s\n", message);
        return;
    }

    // Get timestamp
    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    FILE *output = config->log_output ? config->log_output : stdout;

    va_list args;
    va_start(args, message);

    if (config->use_colors) {
        fprintf(output, "%s[%s] [%s] ", fossil_sanity_get_color_code(level), time_str, level_str[level]);
    } else {
        fprintf(output, "[%s] [%s] ", time_str, level_str[level]);
    }

    vfprintf(output, message, args);
    fprintf(output, "%s\n", config->use_colors ? COLOR_RESET : "");
    va_end(args);
}

// Get color code based on log level
const char *fossil_sanity_get_color_code(fossil_sanity_log_level level) {
    return fossil_sanity_color_codes[level];
}

void show_usage(void) {
    printf("Usage: program [options]\n");
    printf("Options:\n");
    printf("  --debug          Enable debug mode\n");
    printf("  --no-debug       Disable debug mode\n");
    printf("  --logs           Enable logging\n");
    printf("  --no-logs        Disable logging\n");
    printf("  --colors         Enable colored output\n");
    printf("  --no-colors      Disable colored output\n");
    printf("  --show-prod      Set log level to PROD\n");
    printf("  --show-warn      Set log level to WARN\n");
    printf("  --show-error     Set log level to ERROR\n");
    printf("  --show-critical  Set log level to CRITICAL\n");
    printf("  --show-debug     Set log level to DEBUG\n");
    printf("  --help           Display this help message\n");
    printf("  --version        Display the program version\n");
}

void fossil_sanity_parse_args(int argc, char *argv[], fossil_sanity_config *config) {
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        // Handle each argument as a flag or option
        if (strcmp(arg, "--debug") == 0) {
            config->debug_enabled = true;
        } else if (strcmp(arg, "--no-debug") == 0) {
            config->debug_enabled = false;
        } else if (strcmp(arg, "--logs") == 0) {
            config->logs_enabled = true;
        } else if (strcmp(arg, "--no-logs") == 0) {
            config->logs_enabled = false;
        } else if (strcmp(arg, "--colors") == 0) {
            config->use_colors = true;
        } else if (strcmp(arg, "--no-colors") == 0) {
            config->use_colors = false;
        } else if (strcmp(arg, "--show-prod") == 0) {
            config->log_level = FOSSIL_SANITY_LOG_PROD;
        } else if (strcmp(arg, "--show-warn") == 0) {
            config->log_level = FOSSIL_SANITY_LOG_WARN;
        } else if (strcmp(arg, "--show-error") == 0) {
            config->log_level = FOSSIL_SANITY_LOG_ERROR;
        } else if (strcmp(arg, "--show-critical") == 0) {
            config->log_level = FOSSIL_SANITY_LOG_CRITICAL;
        } else if (strcmp(arg, "--show-debug") == 0) {
            config->log_level = FOSSIL_SANITY_LOG_DEBUG;
        } else if (strcmp(arg, "--help") == 0) {
            show_usage();
            exit(0);
        } else if (strcmp(arg, "--version") == 0) {
            puts("Fossil Sanity version 0.1.0\n");
            exit(0);
        } else {
            fprintf(stderr, "Warning: Unknown argument '%s'.\n", arg);
        }
    }
}

// Validate if input is an integer
bool fossil_sanity_validate_integer(const char *input) {
    if (!input || *input == '\0') return false;
    while (*input) {
        if (!isdigit(*input)) return false;
        input++;
    }
    return true;
}

// Validate if input string contains only allowed characters
bool fossil_sanity_validate_string(const char *input, const char *allowed_chars) {
    if (!input || !allowed_chars) return false;
    while (*input) {
        if (!strchr(allowed_chars, *input)) return false;
        input++;
    }
    return true;
}

// Load configuration from INI file
void fossil_sanity_load_config(const char *filename, fossil_sanity_config *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "[ERROR] Unable to open config file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        fossil_sanity_parse_args(2, (char*[]){line, line}, config);
    }

    fclose(file);
}

bool is_in_array(const char *word, const char *array[], size_t array_size) {
    for (size_t i = 0; i < array_size; i++) {
        if (custom_strcasecmp(word, array[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool fossil_sanity_check_message_clarity(const char *message) {
    if (!message || strlen(message) == 0) {
        return false;
    }

    const char *delimiters = " .,!?";
    char *message_copy = custom_strdup(message);
    if (!message_copy) {
        return false;
    }

    size_t word_count = 0;
    size_t noun_count = 0, verb_count = 0, adj_count = 0, rotbrain_count = 0;
    char *token = strtok(message_copy, delimiters);

    while (token) {
        word_count++;

        if (is_in_array(token, NOUNS, sizeof(NOUNS) / sizeof(NOUNS[0]))) {
            noun_count++;
        } else if (is_in_array(token, VERBS, sizeof(VERBS) / sizeof(VERBS[0]))) {
            verb_count++;
        } else if (is_in_array(token, ADJECTIVES, sizeof(ADJECTIVES) / sizeof(ADJECTIVES[0]))) {
            adj_count++;
        } else if (is_in_array(token, ROTBRAIN, sizeof(ROTBRAIN) / sizeof(ROTBRAIN[0]))) {
            rotbrain_count++;
        }

        token = strtok(NULL, delimiters);
    }

    free(message_copy);

    if (noun_count > 0 && verb_count > 0 && adj_count > 0 && rotbrain_count < 3 && word_count <= 20) {
        return true;
    }

    return false;
}

bool fossil_sanity_check_grammar(const char *message) {
    if (!message || strlen(message) == 0) {
        return false;
    }

    const char *delimiters = " .,!?";
    char *message_copy = custom_strdup(message);
    if (!message_copy) {
        return false;
    }

    bool started_with_article = false;
    bool has_verb = false;
    bool has_noun = false;
    bool has_adj_or_prep = false;
    bool rotbrain_used = false;

    char *token = strtok(message_copy, delimiters);

    while (token) {
        if (is_in_array(token, ARTICLES, sizeof(ARTICLES) / sizeof(ARTICLES[0]))) {
            started_with_article = true;
        }

        if (is_in_array(token, NOUNS, sizeof(NOUNS) / sizeof(NOUNS[0]))) {
            has_noun = true;
        }

        if (is_in_array(token, VERBS, sizeof(VERBS) / sizeof(VERBS[0]))) {
            has_verb = true;
        }

        if (is_in_array(token, ADJECTIVES, sizeof(ADJECTIVES) / sizeof(ADJECTIVES[0])) ||
            is_in_array(token, PREPOSITIONS, sizeof(PREPOSITIONS) / sizeof(PREPOSITIONS[0]))) {
            has_adj_or_prep = true;
        }

        if (is_in_array(token, ROTBRAIN, sizeof(ROTBRAIN) / sizeof(ROTBRAIN[0]))) {
            rotbrain_used = true;
        }

        token = strtok(NULL, delimiters);
    }

    free(message_copy);

    if (started_with_article && has_noun && has_verb && has_adj_or_prep && !rotbrain_used) {
        return true;
    }

    return false;
}
