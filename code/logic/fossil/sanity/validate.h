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
#ifndef FOSSIL_SANITY_VALIDATE_H
#define FOSSIL_SANITY_VALIDATE_H

#include <stddef.h>
#include <stdbool.h>

// Maximum limits
#define FOSSIL_SANITY_MAX_INT 2147483647
#define FOSSIL_SANITY_MIN_INT -2147483648

#ifdef __cplusplus
extern "C" {
#endif

// Error codes
typedef enum {
    FOSSIL_SANITY_IN_SUCCESS = 0,
    FOSSIL_SANITY_IN_ERR_NULL_INPUT,
    FOSSIL_SANITY_ERR_INVALID_LENGTH,
    FOSSIL_SANITY_ERR_INVALID_FORMAT,
    FOSSIL_SANITY_ERR_MEMORY_OVERFLOW
} fossil_sanity_validate_error_t;

/**
 * @brief Validates if the input string is a valid integer.
 * 
 * @param input The input string to validate.
 * @param output Pointer to an integer where the parsed value will be stored if valid.
 * @return true if the input is a valid integer, false otherwise.
 */
bool fossil_sanity_validate_is_int(const char *input, int *output);

/**
 * @brief Validates if the input string is a valid float.
 * 
 * @param input The input string to validate.
 * @param output Pointer to a float where the parsed value will be stored if valid.
 * @return true if the input is a valid float, false otherwise.
 */
bool fossil_sanity_validate_is_float(const char *input, float *output);

/**
 * @brief Validates if the input string contains only alphanumeric characters.
 * 
 * @param input The input string to validate.
 * @return true if the input is alphanumeric, false otherwise.
 */
bool fossil_sanity_validate_is_alnum(const char *input);

/**
 * @brief Validates if the input string is a valid email address.
 * 
 * @param input The input string to validate.
 * @return true if the input is a valid email address, false otherwise.
 */
bool fossil_sanity_validate_is_email(const char *input);

/**
 * @brief Validates if the input string does not exceed the specified maximum length.
 * 
 * @param input The input string to validate.
 * @param max_length The maximum allowed length of the input string.
 * @return true if the input length is within the specified limit, false otherwise.
 */
bool fossil_sanity_validate_is_length(const char *input, size_t max_length);

/**
 * @brief Sanitizes the input string and stores the sanitized result in the output buffer.
 * 
 * @param input The input string to sanitize.
 * @param output The buffer where the sanitized string will be stored.
 * @param output_size The size of the output buffer.
 * @return A fossil_sanity_validate_error_t indicating the result of the sanitization process.
 */
fossil_sanity_validate_error_t fossil_sanity_validate_sanitize_string(const char *input, char *output, size_t output_size);

/**
 * @brief Reads a secure line of input into the provided buffer.
 * 
 * @param buffer The buffer where the input will be stored.
 * @param buffer_size The size of the buffer.
 * @return A fossil_sanity_validate_error_t indicating the result of the input reading process.
 */
fossil_sanity_validate_error_t fossil_sanity_validate_read_secure_line(char *buffer, size_t buffer_size);

/**
 * @brief Returns a human-readable error message corresponding to the given error code.
 * 
 * @param error The error code for which to retrieve the message.
 * @return A string containing the error message.
 */
const char *fossil_sanity_validate_error_message(fossil_sanity_validate_error_t error);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_IO_H
