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
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialize health monitoring (call during application startup)
bool fossil_sanity_health_init(void);

// Cleanup health monitoring resources (call during application shutdown)
void fossil_sanity_health_cleanup(void);

// Get the application's current uptime in milliseconds
uint64_t fossil_sanity_get_uptime(void);

// Get the application's current memory usage in bytes
size_t fossil_sanity_get_memory_usage(void);

// Get the current number of active threads
size_t fossil_sanity_get_active_threads(void);

// Check if the application is in a healthy state
bool fossil_sanity_is_healthy(void);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_HEALTH_H
