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

char *custom_strdup(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str) {
        memcpy(new_str, str, len);
    }
    return new_str;
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
    config->debug_enabled = DISABLE;
    config->logs_enabled = ENABLE;
    config->log_level = FOSSIL_SANITY_LOG_WARN;
    config->log_output = NULL;
    config->use_colors = ENABLE;
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

// Parse command-line arguments (with and without `=` sign)
void fossil_sanity_parse_args(int argc, char *argv[], fossil_sanity_config *config) {
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        if (strstr(arg, "=")) {
            char *key = strtok(arg, "=");
            char *value = strtok(NULL, "=");

            if (strcmp(key, "debug") == 0) {
                config->debug_enabled = (strcmp(value, "enable") == 0) ? ENABLE : DISABLE;
            } else if (strcmp(key, "logs") == 0) {
                config->logs_enabled = (strcmp(value, "enable") == 0) ? ENABLE : DISABLE;
            } else if (strcmp(key, "colors") == 0) {
                config->use_colors = (strcmp(value, "enable") == 0) ? ENABLE : DISABLE;
            } else if (strcmp(key, "show") == 0) {
                if (strcmp(value, "prod") == 0) config->log_level = FOSSIL_SANITY_LOG_PROD;
                else if (strcmp(value, "warn") == 0) config->log_level = FOSSIL_SANITY_LOG_WARN;
                else if (strcmp(value, "error") == 0) config->log_level = FOSSIL_SANITY_LOG_ERROR;
                else if (strcmp(value, "critical") == 0) config->log_level = FOSSIL_SANITY_LOG_CRITICAL;
                else if (strcmp(value, "debug") == 0) config->log_level = FOSSIL_SANITY_LOG_DEBUG;
            }
        } else {
            if (strcmp(arg, "debug") == 0) config->debug_enabled = ENABLE;
            else if (strcmp(arg, "no-debug") == 0) config->debug_enabled = DISABLE;
            else if (strcmp(arg, "logs") == 0) config->logs_enabled = ENABLE;
            else if (strcmp(arg, "no-logs") == 0) config->logs_enabled = DISABLE;
            else if (strcmp(arg, "colors") == 0) config->use_colors = ENABLE;
            else if (strcmp(arg, "no-colors") == 0) config->use_colors = DISABLE;
        }
    }
}

// Validate if input is an integer
fossil_sanity_bool fossil_sanity_validate_integer(const char *input) {
    if (!input || *input == '\0') return DISABLE;
    while (*input) {
        if (!isdigit(*input)) return DISABLE;
        input++;
    }
    return ENABLE;
}

// Validate if input string contains only allowed characters
fossil_sanity_bool fossil_sanity_validate_string(const char *input, const char *allowed_chars) {
    if (!input || !allowed_chars) return DISABLE;
    while (*input) {
        if (!strchr(allowed_chars, *input)) return DISABLE;
        input++;
    }
    return ENABLE;
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

// Clarity check: more robust heuristic for checking confusing messages
fossil_sanity_bool fossil_sanity_check_message_clarity(const char *message) {
    // Example checks for common confusing words or phrases
    const char *confusing_keywords[] = {
        "error", "confusing", "complicated", "unintelligible", "undefined", 
        "failure", "incorrect", "issue", "problem", "not working", 
        "crash", "does not compute", "unexpected", "unknown", "complex", 
        "malfunction", "corrupted", "missing", "unsolvable", "fatal"
    };
    
    // Check for confusing keywords
    for (size_t i = 0; i < sizeof(confusing_keywords) / sizeof(confusing_keywords[0]); i++) {
        if (strstr(message, confusing_keywords[i])) {
            return DISABLE; // Confusing message found
        }
    }

    // Check for excessive jargon or overly complex words
    const char *complex_keywords[] = {"algorithm", "heuristic", "asynchronous", "depreciation", "concurrency"};
    for (size_t i = 0; i < sizeof(complex_keywords) / sizeof(complex_keywords[0]); i++) {
        if (strstr(message, complex_keywords[i])) {
            return DISABLE; // Complex terminology detected
        }
    }

    // Check for messages that are too short (less than 5 words) or too vague
    int word_count = 0;
    const char *delimiters = " .,!?";
    char *message_copy = custom_strdup(message);
    char *token = strtok(message_copy, delimiters);
    while (token != NULL) {
        word_count++;
        token = strtok(NULL, delimiters);
    }
    free(message_copy);

    if (word_count < 5) {
        return DISABLE; // Too few words to be meaningful
    }

    return ENABLE; // Message is clear
}

// Simple grammar check: enhanced to check for sentence structure and avoid fragments
fossil_sanity_bool fossil_sanity_check_grammar(const char *message) {
    if (!message || strlen(message) < 5) return DISABLE; // Too short to be a proper sentence

    // Check for sentence-ending punctuation (., !, ?)
    if (strchr(message, '.') == NULL && strchr(message, '!') == NULL && strchr(message, '?') == NULL) {
        return DISABLE; // No sentence-ending punctuation
    }

    // Check if the first character is a capital letter (helps to identify proper sentences)
    if (!isupper(message[0])) {
        return DISABLE; // Sentence doesn't start with a capital letter
    }

    // Look for fragments: ensure at least one subject-verb structure
    int has_verb = 0, has_subject = 0;
    const char *verbs[] = {"is", "are", "was", "were", "be", "being", "been", "am", "have", "has", "do", "does", "did"};
    
    // Simplified check for subject-verb agreement
    for (size_t i = 0; i < sizeof(verbs) / sizeof(verbs[0]); i++) {
        if (strstr(message, verbs[i])) {
            has_verb = 1;
            break;
        }
    }

    if (has_verb) {
        has_subject = 1; // Assume subject exists if verb is found (simplification)
    }

    if (!has_verb || !has_subject) {
        return DISABLE; // Sentence might be incomplete or a fragment
    }

    return ENABLE; // Grammar looks fine
}
