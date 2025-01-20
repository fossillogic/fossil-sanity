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

#include <stddef.h>
#include <stdbool.h>

// Maximum limits
#define FOSSIL_SANITY_MAX_STR_LEN 1024

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

#endif // FOSSIL_SANITY_IO_H
