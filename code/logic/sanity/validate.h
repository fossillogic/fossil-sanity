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
#ifndef FOSSIL_SANITY_IO_H
#define FOSSIL_SANITY_IO_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Validate if a string is not null and meets a specific length
bool fossil_sanity_validate_string(const char *input, size_t min_length, size_t max_length);

// Validate if an integer is within a specified range
bool fossil_sanity_validate_int_range(int input, int min_value, int max_value);

// Validate if a float is within a specified range
bool fossil_sanity_validate_float_range(float input, float min_value, float max_value);

// Validate if a string is numeric (integer or float)
bool fossil_sanity_is_numeric(const char *input);

// Validate if a string matches a specific format (basic regex-like functionality)
bool fossil_sanity_match_format(const char *input, const char *format);

// Sanitize a string by removing unwanted characters
char *fossil_sanity_sanitize_string(const char *input, const char *allowed_chars);

// Validate if an email address format is valid
bool fossil_sanity_validate_email(const char *email);

// Validate if a file path is safe and accessible
bool fossil_sanity_validate_file_path(const char *file_path);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_IO_H
