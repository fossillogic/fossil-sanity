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
#include <stdlib.h>
#include <string.h>

// Validate if a string is not null and meets a specific length
bool fossil_sanity_validate_string(const char *input, size_t min_length, size_t max_length) {
    if (!input) return false;
    size_t length = strlen(input);
    return length >= min_length && length <= max_length;
}

// Validate if an integer is within a specified range
bool fossil_sanity_validate_int_range(int input, int min_value, int max_value) {
    return input >= min_value && input <= max_value;
}

// Validate if a float is within a specified range
bool fossil_sanity_validate_float_range(float input, float min_value, float max_value) {
    return input >= min_value && input <= max_value;
}

// Validate if a string is numeric (integer or float)
bool fossil_sanity_is_numeric(const char *input) {
    if (!input || *input == '\0') return false;

    char *end_ptr;
    strtod(input, &end_ptr);

    return *end_ptr == '\0';
}

// Validate if a string matches a specific format (basic regex-like functionality)
bool fossil_sanity_match_format(const char *input, const char *format) {
    if (!input || !format) return false;

    while (*input && *format) {
        if (*format == '?') {
            // Match any single character
            input++;
            format++;
        } else if (*format == '*') {
            // Match zero or more characters
            if (fossil_sanity_match_format(input + 1, format) || fossil_sanity_match_format(input, format + 1)) {
                return true;
            }
            return false;
        } else if (*input == *format) {
            input++;
            format++;
        } else {
            return false;
        }
    }

    return *input == '\0' && *format == '\0';
}

// Sanitize a string by removing unwanted characters
char *fossil_sanity_sanitize_string(const char *input, const char *allowed_chars) {
    if (!input || !allowed_chars) return NULL;

    size_t input_len = strlen(input);
    char *sanitized = (char *)malloc(input_len + 1);
    if (!sanitized) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (strchr(allowed_chars, input[i])) {
            sanitized[j++] = input[i];
        }
    }
    sanitized[j] = '\0';

    return sanitized;
}

// Validate if an email address format is valid
bool fossil_sanity_validate_email(const char *email) {
    if (!email || strlen(email) < 3) return false;

    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    return at && dot && at < dot && dot - at > 1 && dot[1] != '\0';
}

// Validate if a file path is safe and accessible
bool fossil_sanity_validate_file_path(const char *file_path) {
    if (!file_path || file_path[0] == '\0') return false;

    FILE *file = fopen(file_path, "r");
    if (file) {
        fclose(file);
        return true;
    }

    return false;
}
