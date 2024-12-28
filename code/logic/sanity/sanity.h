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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Boolean values
#define ENABLE  1
#define DISABLE 0

typedef int fossil_sanity_bool;

#ifdef __cplusplus
extern "C" {
#endif

// Log levels
typedef enum {
    FOSSIL_SANITY_LOG_PROD,
    FOSSIL_SANITY_LOG_WARN,
    FOSSIL_SANITY_LOG_ERROR,
    FOSSIL_SANITY_LOG_CRITICAL,
    FOSSIL_SANITY_LOG_DEBUG
} fossil_sanity_log_level;

// Configuration structure
typedef struct {
    fossil_sanity_bool debug_enabled;
    fossil_sanity_bool logs_enabled;
    fossil_sanity_log_level log_level;
    FILE *log_output;
    fossil_sanity_bool use_colors; // Enable/disable colors
} fossil_sanity_config;

// Function declarations
void fossil_sanity_init_config(fossil_sanity_config *config);
void fossil_sanity_parse_args(int argc, char *argv[], fossil_sanity_config *config);
void fossil_sanity_load_config(const char *filename, fossil_sanity_config *config);
void fossil_sanity_log(const fossil_sanity_config *config, fossil_sanity_log_level level, const char *message, ...);
const char *fossil_sanity_get_response(fossil_sanity_log_level level);

// Input validation
fossil_sanity_bool fossil_sanity_validate_integer(const char *input);
fossil_sanity_bool fossil_sanity_validate_string(const char *input, const char *allowed_chars);

// Colors
const char *fossil_sanity_get_color_code(fossil_sanity_log_level level);

// Clarity and grammar checks
fossil_sanity_bool fossil_sanity_check_message_clarity(const char *message);
fossil_sanity_bool fossil_sanity_check_grammar(const char *message);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_CORE_H
