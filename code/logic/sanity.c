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

// Sanitize string (removes non-printable characters)
fossil_sanity_out_error_t fossil_sanity_out_sanitize_string(const char *input, char *output, size_t output_size) {
    if (!input || !output) return FOSSIL_SANITY_OUT_ERR_NULL_INPUT;
    size_t input_len = strlen(input);
    if (input_len >= output_size) return FOSSIL_SANITY_OUT_ERR_BUFFER_OVERFLOW;

    size_t j = 0;
    for (size_t i = 0; i < input_len; ++i) {
        if (isprint((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return FOSSIL_SANITY_OUT_SUCCESS;
}

// Logging function (console output)
void fossil_sanity_out_log(fossil_sanity_out_severity_t severity, const char *message, ...) {
    const char *severity_str;
    switch (severity) {
        case FOSSIL_SANITY_OUT_INFO:    severity_str = "[INFO]";    break;
        case FOSSIL_SANITY_OUT_WARNING: severity_str = "[WARNING]"; break;
        case FOSSIL_SANITY_OUT_ERROR:   severity_str = "[ERROR]";   break;
        case FOSSIL_SANITY_OUT_DEBUG:   severity_str = "[DEBUG]";   break;
        default:                        severity_str = "[UNKNOWN]"; break;
    }

    char sanitized_message[FOSSIL_SANITY_MAX_STR_LEN];
    fossil_sanity_out_sanitize_string(message, sanitized_message, sizeof(sanitized_message));

    va_list args;
    va_start(args, message);
    printf("%s ", severity_str);
    vprintf(sanitized_message, args);
    printf("\n");
    va_end(args);
}

// Logging function (file output)
void fossil_sanity_out_log_to_file(const char *file_path, fossil_sanity_out_severity_t severity, const char *message, ...) {
    if (!file_path || !message) return;

    FILE *file = fopen(file_path, "a");
    if (!file) return;

    const char *severity_str;
    switch (severity) {
        case FOSSIL_SANITY_OUT_INFO:    severity_str = "[INFO]";    break;
        case FOSSIL_SANITY_OUT_WARNING: severity_str = "[WARNING]"; break;
        case FOSSIL_SANITY_OUT_ERROR:   severity_str = "[ERROR]";   break;
        case FOSSIL_SANITY_OUT_DEBUG:   severity_str = "[DEBUG]";   break;
        default:                        severity_str = "[UNKNOWN]"; break;
    }

    char sanitized_message[FOSSIL_SANITY_MAX_STR_LEN];
    fossil_sanity_out_sanitize_string(message, sanitized_message, sizeof(sanitized_message));

    va_list args;
    va_start(args, message);
    fprintf(file, "%s ", severity_str);
    vfprintf(file, sanitized_message, args);
    fprintf(file, "\n");
    va_end(args);

    fclose(file);
}

// Notification function (console notification)
void fossil_sanity_out_notify(const char *title, const char *message) {
    printf("[NOTIFICATION] %s: %s\n", title, message);
}

// Notification function with severity
void fossil_sanity_out_notify_with_severity(fossil_sanity_out_severity_t severity, const char *title, const char *message) {
    const char *severity_str;
    switch (severity) {
        case FOSSIL_SANITY_OUT_INFO:    severity_str = "[INFO]";    break;
        case FOSSIL_SANITY_OUT_WARNING: severity_str = "[WARNING]"; break;
        case FOSSIL_SANITY_OUT_ERROR:   severity_str = "[ERROR]";   break;
        case FOSSIL_SANITY_OUT_DEBUG:   severity_str = "[DEBUG]";   break;
        default:                        severity_str = "[UNKNOWN]"; break;
    }
    printf("%s [NOTIFICATION] %s: %s\n", severity_str, title, message);
}

// Secure print function
fossil_sanity_out_error_t fossil_sanity_out_print_secure(const char *format, ...) {
    if (!format) return FOSSIL_SANITY_OUT_ERR_NULL_INPUT;

    char sanitized_format[FOSSIL_SANITY_MAX_STR_LEN];
    if (fossil_sanity_out_sanitize_string(format, sanitized_format, sizeof(sanitized_format)) != FOSSIL_SANITY_OUT_SUCCESS) {
        return FOSSIL_SANITY_OUT_ERR_INVALID_FORMAT;
    }

    va_list args;
    va_start(args, format);
    vprintf(sanitized_format, args);
    va_end(args);

    return FOSSIL_SANITY_OUT_SUCCESS;
}

// Get error message
const char *fossil_sanity_out_error_message(fossil_sanity_out_error_t error) {
    switch (error) {
        case FOSSIL_SANITY_OUT_SUCCESS:        return "Success";
        case FOSSIL_SANITY_OUT_ERR_NULL_INPUT: return "Null input provided";
        case FOSSIL_SANITY_OUT_ERR_INVALID_FORMAT: return "Invalid format";
        case FOSSIL_SANITY_OUT_ERR_BUFFER_OVERFLOW: return "Buffer overflow detected";
        default:                                return "Unknown error";
    }
}

fossil_sanity_out_error_t fossil_sanity_out_log_with_rotation(const char *file_path, size_t max_size, fossil_sanity_out_severity_t severity, const char *message, ...) {
    if (!file_path || !message) return FOSSIL_SANITY_OUT_ERR_NULL_INPUT;

    // Check file size
    FILE *file = fopen(file_path, "a+");
    if (!file) return FOSSIL_SANITY_OUT_ERR_NULL_INPUT;

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fclose(file);

    // Rotate log if needed
    if (file_size >= max_size) {
        char rotated_path[1024];
        snprintf(rotated_path, sizeof(rotated_path), "%s.old", file_path);
        rename(file_path, rotated_path);
    }

    // Write log
    file = fopen(file_path, "a");
    if (!file) return FOSSIL_SANITY_OUT_ERR_NULL_INPUT;

    const char *severity_str = "UNKNOWN";
    switch (severity) {
        case FOSSIL_SANITY_OUT_INFO:    severity_str = "INFO";    break;
        case FOSSIL_SANITY_OUT_WARNING: severity_str = "WARNING"; break;
        case FOSSIL_SANITY_OUT_ERROR:   severity_str = "ERROR";   break;
        case FOSSIL_SANITY_OUT_DEBUG:   severity_str = "DEBUG";   break;
    }

    va_list args;
    va_start(args, message);
    fprintf(file, "[%s] ", severity_str);
    vfprintf(file, message, args);
    fprintf(file, "\n");
    va_end(args);

    fclose(file);
    return FOSSIL_SANITY_OUT_SUCCESS;
}
