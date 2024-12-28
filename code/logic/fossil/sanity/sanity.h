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

enum {
    FOSSIL_SANITY_TRUE = ENABLE,
    FOSSIL_SANITY_FALSE = DISABLE
};

/**
 * @enum fossil_sanity_log_level
 * @brief Enumeration of log levels.
 */
typedef enum {
    FOSSIL_SANITY_LOG_PROD,      /**< Production log level */
    FOSSIL_SANITY_LOG_WARN,      /**< Warning log level */
    FOSSIL_SANITY_LOG_ERROR,     /**< Error log level */
    FOSSIL_SANITY_LOG_CRITICAL,  /**< Critical log level */
    FOSSIL_SANITY_LOG_DEBUG      /**< Debug log level */
} fossil_sanity_log_level;

/**
 * @struct fossil_sanity_config
 * @brief Configuration structure for the Fossil Sanity library.
 */
typedef struct {
    fossil_sanity_bool debug_enabled;    /**< Enable/disable debug mode */
    fossil_sanity_bool logs_enabled;     /**< Enable/disable logging */
    fossil_sanity_log_level log_level;   /**< Log level */
    FILE *log_output;                    /**< Output file for logs */
    fossil_sanity_bool use_colors;       /**< Enable/disable colors in logs */
} fossil_sanity_config;

/**
 * @brief Initialize the configuration structure with default values.
 *
 * @param config Pointer to the configuration structure to initialize.
 */
void fossil_sanity_init_config(fossil_sanity_config *config);

/**
 * @brief Parse command-line arguments to configure the library.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param config Pointer to the configuration structure to populate.
 */
void fossil_sanity_parse_args(int argc, char *argv[], fossil_sanity_config *config);

/**
 * @brief Load configuration from a file.
 *
 * @param filename Path to the configuration file.
 * @param config Pointer to the configuration structure to populate.
 */
void fossil_sanity_load_config(const char *filename, fossil_sanity_config *config);

/**
 * @brief Log a message with the specified log level.
 *
 * @param config Pointer to the configuration structure.
 * @param level Log level of the message.
 * @param message Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
void fossil_sanity_log(const fossil_sanity_config *config, fossil_sanity_log_level level, const char *message, ...);

/**
 * @brief Get a response message based on the log level.
 *
 * @param level Log level.
 * @return Response message.
 */
const char *fossil_sanity_get_response(fossil_sanity_log_level level);

/**
 * @brief Validate if the input string is a valid integer.
 *
 * @param input Input string to validate.
 * @return Boolean indicating if the input is a valid integer.
 */
fossil_sanity_bool fossil_sanity_validate_integer(const char *input);

/**
 * @brief Validate if the input string contains only allowed characters.
 *
 * @param input Input string to validate.
 * @param allowed_chars String of allowed characters.
 * @return Boolean indicating if the input is valid.
 */
fossil_sanity_bool fossil_sanity_validate_string(const char *input, const char *allowed_chars);

/**
 * @brief Get the color code for the specified log level.
 *
 * @param level Log level.
 * @return Color code string.
 */
const char *fossil_sanity_get_color_code(fossil_sanity_log_level level);

/**
 * @brief Check the clarity of a message.
 *
 * @param message Message to check.
 * @return Boolean indicating if the message is clear.
 */
fossil_sanity_bool fossil_sanity_check_message_clarity(const char *message);

/**
 * @brief Check the grammar of a message.
 *
 * @param message Message to check.
 * @return Boolean indicating if the message has correct grammar.
 */
fossil_sanity_bool fossil_sanity_check_grammar(const char *message);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_CORE_H
