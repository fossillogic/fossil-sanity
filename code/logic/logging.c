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
#include "fossil/sanity/logging.h"
#include <stdlib.h>
#include <string.h>

static FILE *log_file = NULL;
static fossil_log_level_t current_log_level = FOSSIL_LOG_INFO;
static const char *log_file_path = "default_log.txt";

// Function to initialize the logging system
void fossil_sanity_init(const char *file_path, fossil_log_level_t log_level) {
    if (file_path != NULL) {
        log_file_path = file_path;
    }

    log_file = fopen(log_file_path, "a");
    if (log_file == NULL) {
        fprintf(stderr, "Error opening log file\n");
        exit(EXIT_FAILURE);
    }

    current_log_level = log_level;
}

// Function to log messages at different levels
void fossil_sanity_log(fossil_log_level_t level, const char *format, ...) {
    if (level < current_log_level) {
        return;
    }

    const char *level_strings[] = { "INFO", "DEBUG", "WARNING", "ERROR", "CRITICAL" };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buffer[26];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", tm_info);

    va_list args;
    va_start(args, format);

    fprintf(log_file, "[%s] [%s] ", time_buffer, level_strings[level]);
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");

    va_end(args);
    fflush(log_file);
}

// Function to set the log level dynamically
void fossil_sanity_set_level(fossil_log_level_t level) {
    current_log_level = level;
}

// Function to rotate log files based on size
void fossil_sanity_rotate_logs(size_t max_size) {
    if (log_file == NULL) {
        return;
    }

    fseek(log_file, 0, SEEK_END);
    long file_size = ftell(log_file);

    if (file_size >= max_size) {
        fclose(log_file);

        // Rename the current log to a backup
        char backup_file[255];
        snprintf(backup_file, sizeof(backup_file), "%s.bak", log_file_path);
        rename(log_file_path, backup_file);

        // Reopen the log file for writing
        log_file = fopen(log_file_path, "a");
        if (log_file == NULL) {
            fprintf(stderr, "Error opening log file after rotation\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to clear logs
void fossil_sanity_clear_logs(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = fopen(log_file_path, "w");
    }
}

// Function to view current logs
void fossil_sanity_view_logs(void) {
    if (log_file != NULL) {
        fseek(log_file, 0, SEEK_SET);
        char ch;
        while ((ch = fgetc(log_file)) != EOF) {
            putchar(ch);
        }
    }
}

// Function to shutdown the logging system and clean up resources
void fossil_sanity_shutdown(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}
