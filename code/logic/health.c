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
#include "fossil/sanity/health.h"
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <processthreadsapi.h>
#else
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#endif

// Internal variables
static uint64_t start_time_ms = 0;

#ifdef _WIN32
// Windows-specific implementation
static uint64_t get_current_time_ms(void) {
    FILETIME ft;
    ULARGE_INTEGER ui;
    GetSystemTimeAsFileTime(&ft);
    ui.LowPart = ft.dwLowDateTime;
    ui.HighPart = ft.dwHighDateTime;
    return (ui.QuadPart / 10000ULL);
}

static size_t get_memory_usage(void) {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    return 0;
}

static size_t get_active_threads(void) {
    return GetProcessHandleCount(GetCurrentProcess());
}

#else
// POSIX-specific implementation
static uint64_t get_current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL);
}

static size_t get_memory_usage(void) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss * 1024; // Convert KB to bytes
    }
    return 0;
}

static size_t get_active_threads(void) {
    return sysconf(_SC_NPROCESSORS_ONLN); // Threads per processor
}
#endif

bool fossil_sanity_health_init(void) {
    start_time_ms = get_current_time_ms();
    return (start_time_ms != 0);
}

void fossil_sanity_health_cleanup(void) {
    // No specific resources to free, placeholder for extensibility
}

uint64_t fossil_sanity_get_uptime(void) {
    return get_current_time_ms() - start_time_ms;
}

size_t fossil_sanity_get_memory_usage(void) {
    return get_memory_usage();
}

size_t fossil_sanity_get_active_threads(void) {
    return get_active_threads();
}

bool fossil_sanity_is_healthy(void) {
    // Example: Define health checks (e.g., uptime > 0, memory usage under a limit)
    if (fossil_sanity_get_uptime() > 0 && fossil_sanity_get_memory_usage() < (1024 * 1024 * 512)) {
        return true;
    }
    return false;
}
