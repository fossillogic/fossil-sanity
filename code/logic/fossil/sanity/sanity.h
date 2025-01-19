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
#ifndef FOSSIL_SANITY_CORE_H
#define FOSSIL_SANITY_CORE_H

#include <stddef.h>
#include <stdbool.h>

// Maximum limits
#define FOSSIL_SANITY_MAX_STR_LEN 1024
#define FOSSIL_SANITY_MAX_INT 2147483647
#define FOSSIL_SANITY_MIN_INT -2147483648

#ifdef __cplusplus
extern "C" {
#endif

// Severity levels for logs and notifications
typedef enum {
    FOSSIL_SANITY_OUT_INFO,
    FOSSIL_SANITY_OUT_WARNING,
    FOSSIL_SANITY_OUT_ERROR,
    FOSSIL_SANITY_OUT_DEBUG
} fossil_sanity_out_severity_t;

// Error codes
typedef enum {
    FOSSIL_SANITY_OUT_SUCCESS = 0,
    FOSSIL_SANITY_OUT_ERR_NULL_INPUT,
    FOSSIL_SANITY_OUT_ERR_INVALID_FORMAT,
    FOSSIL_SANITY_OUT_ERR_BUFFER_OVERFLOW
} fossil_sanity_out_error_t;

// Error codes
typedef enum {
    FOSSIL_SANITY_IN_SUCCESS = 0,
    FOSSIL_SANITY_ERR_NULL_INPUT,
    FOSSIL_SANITY_ERR_INVALID_LENGTH,
    FOSSIL_SANITY_ERR_INVALID_FORMAT,
    FOSSIL_SANITY_ERR_MEMORY_OVERFLOW
} fossil_sanity_in_error_t;

/**
 * @brief Validates if the input string is a valid integer.
 * 
 * @param input The input string to validate.
 * @param output Pointer to an integer where the parsed value will be stored if valid.
 * @return true if the input is a valid integer, false otherwise.
 */
bool fossil_sanity_in_is_valid_int(const char *input, int *output);

/**
 * @brief Validates if the input string is a valid float.
 * 
 * @param input The input string to validate.
 * @param output Pointer to a float where the parsed value will be stored if valid.
 * @return true if the input is a valid float, false otherwise.
 */
bool fossil_sanity_in_is_valid_float(const char *input, float *output);

/**
 * @brief Validates if the input string contains only alphanumeric characters.
 * 
 * @param input The input string to validate.
 * @return true if the input is alphanumeric, false otherwise.
 */
bool fossil_sanity_in_is_valid_alnum(const char *input);

/**
 * @brief Validates if the input string is a valid email address.
 * 
 * @param input The input string to validate.
 * @return true if the input is a valid email address, false otherwise.
 */
bool fossil_sanity_in_is_valid_email(const char *input);

/**
 * @brief Validates if the input string does not exceed the specified maximum length.
 * 
 * @param input The input string to validate.
 * @param max_length The maximum allowed length of the input string.
 * @return true if the input length is within the specified limit, false otherwise.
 */
bool fossil_sanity_in_is_valid_length(const char *input, size_t max_length);

/**
 * @brief Sanitizes the input string and stores the sanitized result in the output buffer.
 * 
 * @param input The input string to sanitize.
 * @param output The buffer where the sanitized string will be stored.
 * @param output_size The size of the output buffer.
 * @return A fossil_sanity_in_error_t indicating the result of the sanitization process.
 */
fossil_sanity_in_error_t fossil_sanity_in_sanitize_string(const char *input, char *output, size_t output_size);

/**
 * @brief Reads a secure line of input into the provided buffer.
 * 
 * @param buffer The buffer where the input will be stored.
 * @param buffer_size The size of the buffer.
 * @return A fossil_sanity_in_error_t indicating the result of the input reading process.
 */
fossil_sanity_in_error_t fossil_sanity_in_read_secure_line(char *buffer, size_t buffer_size);

/**
 * @brief Returns a human-readable error message corresponding to the given error code.
 * 
 * @param error The error code for which to retrieve the message.
 * @return A string containing the error message.
 */
const char *fossil_sanity_in_error_message(fossil_sanity_in_error_t error);

// ============================================================================
// Output functions
// ============================================================================

/**
 * @brief Sanitizes the input string and stores the result in the output buffer.
 * 
 * @param input The input string to be sanitized.
 * @param output The buffer to store the sanitized output string.
 * @param output_size The size of the output buffer.
 * @return fossil_sanity_out_error_t Error code indicating the result of the sanitization.
 */
fossil_sanity_out_error_t fossil_sanity_out_sanitize_string(const char *input, char *output, size_t output_size);

/**
 * @brief Logs a message with the specified severity.
 * 
 * @param severity The severity level of the log message.
 * @param message The format string for the log message.
 * @param ... Additional arguments for the format string.
 */
void fossil_sanity_out_log(fossil_sanity_out_severity_t severity, const char *message, ...);

/**
 * @brief Logs a message with the specified severity to a file.
 * 
 * @param file_path The path to the log file.
 * @param severity The severity level of the log message.
 * @param message The format string for the log message.
 * @param ... Additional arguments for the format string.
 */
void fossil_sanity_out_log_to_file(const char *file_path, fossil_sanity_out_severity_t severity, const char *message, ...);

/**
 * @brief Sends a notification with the specified title and message.
 * 
 * @param title The title of the notification.
 * @param message The message of the notification.
 */
void fossil_sanity_out_notify(const char *title, const char *message);

/**
 * @brief Sends a notification with the specified severity, title, and message.
 * 
 * @param severity The severity level of the notification.
 * @param title The title of the notification.
 * @param message The message of the notification.
 */
void fossil_sanity_out_notify_with_severity(fossil_sanity_out_severity_t severity, const char *title, const char *message);

/**
 * @brief Securely prints a formatted string.
 * 
 * @param format The format string.
 * @param ... Additional arguments for the format string.
 * @return fossil_sanity_out_error_t Error code indicating the result of the secure printing.
 */
fossil_sanity_out_error_t fossil_sanity_out_print_secure(const char *format, ...);

/**
 * @brief Retrieves the error message corresponding to the given error code.
 * 
 * @param error The error code.
 * @return const char* The error message.
 */
const char *fossil_sanity_out_error_message(fossil_sanity_out_error_t error);

/**
 * @brief Logs a message with rotation support.
 * 
 * @param file_path The path to the log file.
 * @param max_size The maximum size of the log file before rotation.
 * @param severity The severity level of the log message.
 * @param message The format string for the log message.
 * @param ... Additional arguments for the format string.
 * @return fossil_sanity_out_error_t Error code indicating the result of the logging operation.
 */
fossil_sanity_out_error_t fossil_sanity_out_log_with_rotation(const char *file_path, size_t max_size, fossil_sanity_out_severity_t severity, const char *message, ...);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_CORE_H
