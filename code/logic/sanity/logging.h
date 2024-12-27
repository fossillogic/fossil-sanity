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
#ifndef FOSSIL_SANITY_LOGGING_H
#define FOSSIL_SANITY_LOGGING_H

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// Log Levels
typedef enum {
    FOSSIL_LOG_INFO,
    FOSSIL_LOG_DEBUG,
    FOSSIL_LOG_WARNING,
    FOSSIL_LOG_ERROR,
    FOSSIL_LOG_CRITICAL
} fossil_log_level_t;

// Function to initialize the logging system
void fossil_sanity_init(const char *log_file, fossil_log_level_t log_level);

// Function to log messages at different levels
void fossil_sanity_log(fossil_log_level_t level, const char *format, ...);

// Function to set the log level dynamically
void fossil_sanity_set_level(fossil_log_level_t level);

// Function to rotate log files based on size
void fossil_sanity_rotate_logs(size_t max_size);

// Function to clear logs
void fossil_sanity_clear_logs(void);

// Function to view current logs (could open the log file for reading)
void fossil_sanity_view_logs(void);

// Function to shutdown the logging system and clean up resources
void fossil_sanity_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_LOGGING_H
