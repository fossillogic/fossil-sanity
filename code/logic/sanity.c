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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *_custom_strdup(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char *copy = (char *)malloc(len + 1);
    if (!copy) return NULL;
    strcpy(copy, str);
    return copy;
}

// Static variable to hold the smart log format setting
static bool smart_log_format = false;

// Initialize the log queue
void fossil_sanity_log_init(fossil_sanity_log_queue_t *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

// Push a log entry into the queue based on priority and severity
void fossil_sanity_log_push(fossil_sanity_log_queue_t *queue, const char *message, int priority, int severity) {
    fossil_sanity_log_entry_t *new_entry = (fossil_sanity_log_entry_t *)malloc(sizeof(fossil_sanity_log_entry_t));
    if (!new_entry) {
        perror("Failed to allocate memory for log entry");
        return;
    }

    new_entry->priority = priority;
    new_entry->severity = severity;
    strncpy(new_entry->message, message, MAX_LOG_MESSAGE_LENGTH - 1);
    new_entry->message[MAX_LOG_MESSAGE_LENGTH - 1] = '\0';  // Ensure null-termination

    new_entry->next = NULL;
    new_entry->prev = NULL;

    // Add the new log entry to the queue based on priority (Descending order)
    if (!queue->head) {
        queue->head = new_entry;
        queue->tail = new_entry;
    } else {
        fossil_sanity_log_entry_t *current = queue->head;
        while (current && current->priority >= priority) {
            current = current->next;
        }
        if (!current) {
            // Add to the tail
            queue->tail->next = new_entry;
            new_entry->prev = queue->tail;
            queue->tail = new_entry;
        } else if (current == queue->head) {
            // Insert at the front
            new_entry->next = queue->head;
            queue->head->prev = new_entry;
            queue->head = new_entry;
        } else {
            // Insert between current and current->prev
            new_entry->prev = current->prev;
            new_entry->next = current;
            current->prev->next = new_entry;
            current->prev = new_entry;
        }
    }
}

// Pop the log with the highest priority
char *fossil_sanity_log_pop(fossil_sanity_log_queue_t *queue) {
    if (!queue->head) {
        return NULL;
    }

    fossil_sanity_log_entry_t *log_to_pop = queue->head;
    char *message = _custom_strdup(log_to_pop->message);
    
    queue->head = log_to_pop->next;
    if (queue->head) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;  // Queue is empty now
    }

    free(log_to_pop);
    return message;
}

// Print all logs in the queue
void fossil_sanity_log_print(fossil_sanity_log_queue_t *queue) {
    fossil_sanity_log_entry_t *current = queue->head;
    while (current) {
        if (smart_log_format) {
            switch (current->priority) {
                case FOSSIL_SANITY_LOG_LEVEL_DEBUG:
                    printf("[DEBUG]: %s\n", current->message);
                    break;
                case FOSSIL_SANITY_LOG_LEVEL_INFO:
                    printf("[INFO]: %s\n", current->message);
                    break;
                case FOSSIL_SANITY_LOG_LEVEL_WARNING:
                    printf("[WARNING]: %s\n", current->message);
                    break;
                case FOSSIL_SANITY_LOG_LEVEL_ERROR:
                    printf("[ERROR]: %s\n", current->message);
                    break;
                case FOSSIL_SANITY_LOG_LEVEL_FATAL:
                    printf("[FATAL]: %s\n", current->message);
                    break;
                default:
                    printf("[UNKNOWN]: %s\n", current->message);
            }
        } else {
            printf("%s\n", current->message);
        }
        current = current->next;
    }
}

// Clear all logs in the queue
void fossil_sanity_log_clear(fossil_sanity_log_queue_t *queue) {
    fossil_sanity_log_entry_t *current = queue->head;
    while (current) {
        fossil_sanity_log_entry_t *next = current->next;
        free(current);
        current = next;
    }
    queue->head = queue->tail = NULL;
}

// Sort logs in descending order of priority (Highest priority first)
void fossil_sanity_log_sort(fossil_sanity_log_queue_t *queue) {
    if (!queue->head) return;

    bool swapped;
    do {
        swapped = false;
        fossil_sanity_log_entry_t *current = queue->head;
        while (current && current->next) {
            if (current->priority < current->next->priority) {
                // Swap the log entries
                int temp_priority = current->priority;
                int temp_severity = current->severity;
                char temp_message[MAX_LOG_MESSAGE_LENGTH];
                strcpy(temp_message, current->message);

                current->priority = current->next->priority;
                current->severity = current->next->severity;
                strcpy(current->message, current->next->message);

                current->next->priority = temp_priority;
                current->next->severity = temp_severity;
                strcpy(current->next->message, temp_message);

                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Filter logs based on minimum priority (Only logs with higher or equal priority will be shown)
void fossil_sanity_log_filter(fossil_sanity_log_queue_t *queue, int min_priority) {
    fossil_sanity_log_entry_t *current = queue->head;
    while (current) {
        if (current->priority < min_priority) {
            // Remove log entry
            fossil_sanity_log_entry_t *to_remove = current;
            current = current->next;
            if (to_remove->prev) to_remove->prev->next = to_remove->next;
            if (to_remove->next) to_remove->next->prev = to_remove->prev;

            if (to_remove == queue->head) queue->head = current;
            if (to_remove == queue->tail) queue->tail = current;

            free(to_remove);
        } else {
            current = current->next;
        }
    }
}

// Search for a log entry containing the keyword
char *fossil_sanity_log_search(fossil_sanity_log_queue_t *queue, const char *keyword) {
    fossil_sanity_log_entry_t *current = queue->head;
    while (current) {
        if (strstr(current->message, keyword)) {
            return current->message;
        }
        current = current->next;
    }
    return NULL;
}

// Rotate log file when the size exceeds a threshold
void fossil_sanity_log_rotate(fossil_sanity_log_rotation_t *rotation) {
    FILE *file = fopen(rotation->log_file_path, "a");
    if (!file) {
        perror("Failed to open log file");
        return;
    }

    fseek(file, 0, SEEK_END);
    rotation->current_size = ftell(file);
    if (rotation->current_size > MAX_LOG_FILE_SIZE) {
        // Rotate the log file (move the current log to a backup and create a new one)
        fclose(file);
        rename(rotation->log_file_path, "log_backup.txt");
        file = fopen(rotation->log_file_path, "w");
    }

    fclose(file);
}

// Send a notification for critical logs (e.g., FATAL level)
void fossil_sanity_log_notify(const char *message) {
    printf("ALERT: Critical log - %s\n", message);  // Example notification (can be email or SMS in real applications)
}

// Log with smart formatting based on severity and level
void fossil_sanity_log_smart_log(fossil_sanity_log_queue_t *queue, int level, int severity, const char *message) {
    if (severity == FOSSIL_SANITY_LOG_SEVERITY_HIGH) {
        fossil_sanity_log_notify(message);  // Notify if severity is high
    }
    fossil_sanity_log_push(queue, message, level, severity);
}

// Enable or disable smart log format
void fossil_sanity_log_set_smart_format(bool enable) {
    smart_log_format = enable;
}
