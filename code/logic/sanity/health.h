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
#ifndef FOSSIL_SANITY_HEALTH_H
#define FOSSIL_SANITY_HEALTH_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Health Monitoring Functions

// Get the application's current uptime in seconds
uint64_t fossil_sanity_get_uptime(void);

// Get the application's current memory usage
size_t fossil_sanity_get_memory_usage(void);

// Get the current number of active threads
size_t fossil_sanity_get_active_threads(void);

// Check if the application is in a healthy state
bool fossil_sanity_is_healthy(void);

// Profiling Functions

// Start profiling a specific section of code
void fossil_sanity_start_profiling(const char *section_name);

// Stop profiling a specific section and return elapsed time in microseconds
uint64_t fossil_sanity_stop_profiling(const char *section_name);

// Generate a detailed profile report (output to console or log file)
void fossil_sanity_generate_profile_report(void);

// Utility

// Reset all health and profiling metrics
void fossil_sanity_reset_metrics(void);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_HEALTH_H
