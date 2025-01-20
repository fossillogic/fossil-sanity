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
#include "fossil/sanity/validate.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef __WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


// Validate integer input
bool fossil_sanity_validate_is_int(const char *input, int *output) {
    if (!input || !output) return false;
    char *endptr;
    long value = strtol(input, &endptr, 10);
    if (*endptr != '\0' || value > FOSSIL_SANITY_MAX_INT) {
        return false;
    }
    *output = (int)value;
    return true;
}

// Validate float input
bool fossil_sanity_validate_is_float(const char *input, float *output) {
    if (!input || !output) return false;
    char *endptr;
    float value = strtof(input, &endptr);
    if (*endptr != '\0') return false;
    *output = value;
    return true;
}

// Validate alphanumeric string
bool fossil_sanity_validate_is_alnum(const char *input) {
    if (!input) return false;
    while (*input) {
        if (!isalnum((unsigned char)*input)) {
            return false;
        }
        input++;
    }
    return true;
}

// Validate email format (basic)
bool fossil_sanity_validate_is_email(const char *input) {
    if (!input) return false;
    const char *at = strchr(input, '@');
    const char *dot = strrchr(input, '.');
    return at && dot && at < dot && (dot - at > 1);
}

// Validate string length
bool fossil_sanity_validate_is_length(const char *input, size_t max_length) {
    if (!input) return false;
    return strlen(input) <= max_length;
}

// Sanitize string (remove non-printable characters)
fossil_sanity_validate_error_t fossil_sanity_validate_sanitize_string(const char *input, char *output, size_t output_size) {
    if (!input || !output) return FOSSIL_SANITY_IN_ERR_NULL_INPUT;
    size_t input_len = strlen(input);
    if (input_len >= output_size) return FOSSIL_SANITY_ERR_INVALID_LENGTH;

    size_t j = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (isprint((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return FOSSIL_SANITY_IN_SUCCESS;
}

// Securely read a line of input
fossil_sanity_validate_error_t fossil_sanity_validate_read_secure_line(char *buffer, size_t buffer_size) {
    if (!buffer) return FOSSIL_SANITY_IN_ERR_NULL_INPUT;
    if (!fgets(buffer, buffer_size, stdin)) {
        return FOSSIL_SANITY_ERR_INVALID_FORMAT;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == buffer_size - 1) {
        return FOSSIL_SANITY_ERR_MEMORY_OVERFLOW;
    }
    return FOSSIL_SANITY_IN_SUCCESS;
}

// Get error message
const char *fossil_sanity_validate_error_message(fossil_sanity_validate_error_t error) {
    switch (error) {
        case FOSSIL_SANITY_IN_SUCCESS: return "Success";
        case FOSSIL_SANITY_IN_ERR_NULL_INPUT: return "Null input provided";
        case FOSSIL_SANITY_ERR_INVALID_LENGTH: return "Invalid input length";
        case FOSSIL_SANITY_ERR_INVALID_FORMAT: return "Invalid input format";
        case FOSSIL_SANITY_ERR_MEMORY_OVERFLOW: return "Memory overflow detected";
        default: return "Unknown error";
    }
}

fossil_sanity_validate_error_t fossil_sanity_validate_get_password(char *output, size_t output_size) {
    if (!output || output_size == 0) return FOSSIL_SANITY_IN_ERR_NULL_INPUT;

    printf("Enter password: ");
    fflush(stdout);

    // Disable terminal echo
    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
    #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    #endif

    // Read password
    fgets(output, output_size, stdin);

    // Re-enable terminal echo
    #if defined(_WIN32) || defined(_WIN64)
        SetConsoleMode(hStdin, mode);
    #else
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif

    // Strip newline character
    size_t len = strlen(output);
    if (len > 0 && output[len - 1] == '\n') {
        output[len - 1] = '\0';
    }

    return FOSSIL_SANITY_IN_SUCCESS;
}
