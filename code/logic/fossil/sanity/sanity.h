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
#ifndef FOSSIL_SANITY_LOG_H
#define FOSSIL_SANITY_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Log Levels (Priority-based)
#define FOSSIL_SANITY_LOG_LEVEL_DEBUG    0
#define FOSSIL_SANITY_LOG_LEVEL_INFO     1
#define FOSSIL_SANITY_LOG_LEVEL_WARNING  2
#define FOSSIL_SANITY_LOG_LEVEL_ERROR    3
#define FOSSIL_SANITY_LOG_LEVEL_FATAL    4

// Severity Levels
#define FOSSIL_SANITY_LOG_SEVERITY_LOW    0
#define FOSSIL_SANITY_LOG_SEVERITY_MEDIUM 1
#define FOSSIL_SANITY_LOG_SEVERITY_HIGH   2

// Max length for log message
#define MAX_LOG_MESSAGE_LENGTH 256
#define MAX_LOG_FILE_SIZE      1024 * 1024  // 1 MB for log file size

#ifdef __cplusplus
extern "C" {
#endif

// Log entry structure
typedef struct fossil_sanity_log_entry {
    int priority;                // Log level priority
    int severity;                // Severity level of the log
    char message[MAX_LOG_MESSAGE_LENGTH];  // Log message
    struct fossil_sanity_log_entry *prev;
    struct fossil_sanity_log_entry *next;
} fossil_sanity_log_entry_t;

// Double-ended priority queue (DEPQ)
typedef struct fossil_sanity_log_queue {
    fossil_sanity_log_entry_t *head;
    fossil_sanity_log_entry_t *tail;
} fossil_sanity_log_queue_t;

// Log rotation state
typedef struct fossil_sanity_log_rotation {
    char log_file_path[MAX_LOG_MESSAGE_LENGTH]; // Log file path for rotation
    size_t current_size;   // Current size of the log file
} fossil_sanity_log_rotation_t;

/**
 * @brief Initialize the log queue.
 *
 * @param queue Pointer to the log queue to initialize.
 */
void fossil_sanity_log_init(fossil_sanity_log_queue_t *queue);

/**
 * @brief Push a log message onto the queue.
 *
 * @param queue Pointer to the log queue.
 * @param message The log message to push.
 * @param priority The priority of the log message.
 * @param severity The severity of the log message.
 */
void fossil_sanity_log_push(fossil_sanity_log_queue_t *queue, const char *message, int priority, int severity);

/**
 * @brief Pop a log message from the queue.
 *
 * @param queue Pointer to the log queue.
 * @return The popped log message.
 */
char *fossil_sanity_log_pop(fossil_sanity_log_queue_t *queue);

/**
 * @brief Print all log messages in the queue.
 *
 * @param queue Pointer to the log queue.
 */
void fossil_sanity_log_print(fossil_sanity_log_queue_t *queue);

/**
 * @brief Clear all log messages from the queue.
 *
 * @param queue Pointer to the log queue.
 */
void fossil_sanity_log_clear(fossil_sanity_log_queue_t *queue);

/**
 * @brief Sort the log messages in the queue.
 *
 * @param queue Pointer to the log queue.
 */
void fossil_sanity_log_sort(fossil_sanity_log_queue_t *queue);

/**
 * @brief Filter log messages in the queue by minimum priority.
 *
 * @param queue Pointer to the log queue.
 * @param min_priority The minimum priority to filter by.
 */
void fossil_sanity_log_filter(fossil_sanity_log_queue_t *queue, int min_priority);

/**
 * @brief Search for a log message in the queue by keyword.
 *
 * @param queue Pointer to the log queue.
 * @param keyword The keyword to search for.
 * @return The found log message.
 */
char *fossil_sanity_log_search(fossil_sanity_log_queue_t *queue, const char *keyword);

/**
 * @brief Rotate the log files based on the rotation policy.
 *
 * @param rotation Pointer to the log rotation policy.
 */
void fossil_sanity_log_rotate(fossil_sanity_log_rotation_t *rotation);

/**
 * @brief Send a notification with the given message.
 *
 * @param message The message to notify.
 */
void fossil_sanity_log_notify(const char *message);

/**
 * @brief Log a message using the smart log system.
 *
 * @param queue Pointer to the log queue.
 * @param level The log level.
 * @param severity The severity of the log message.
 * @param message The log message.
 */
void fossil_sanity_log_smart_log(fossil_sanity_log_queue_t *queue, int level, int severity, const char *message);

/**
 * @brief Enable or disable the smart log format.
 *
 * @param enable Boolean flag to enable or disable the smart log format.
 */
void fossil_sanity_log_set_smart_format(bool enable);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_LOG_H
