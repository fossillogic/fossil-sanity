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
#ifndef FOSSIL_SANITY_PARSER_H
#define FOSSIL_SANITY_PARSER_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Data types for parser options
typedef enum {
    FOSSIL_SANITY_PARSER_TYPE_BOOL,
    FOSSIL_SANITY_PARSER_TYPE_INT,
    FOSSIL_SANITY_PARSER_TYPE_STRING,
    FOSSIL_SANITY_PARSER_TYPE_ARRAY,
    FOSSIL_SANITY_PARSER_TYPE_FEATURE
} fossil_sanity_parser_option_type_t;

typedef struct {
    const char *name;  // Long option name (e.g., "--enable-feature")
    char short_name;   // Short option name (e.g., "-e")
    fossil_sanity_parser_option_type_t type;  // Type of the option
    void *value;       // Pointer to the value to store the result
    const char *description;  // Description for help output
} fossil_sanity_parser_option_t;

// CLI subcommand structure
typedef struct {
    const char *name;  // Subcommand name
    fossil_sanity_parser_option_t *options;  // Options for the subcommand
    int option_count;  // Number of options
    const char *description;  // Description for the subcommand
    int (*handler)(int argc, char **argv);  // Handler function for the subcommand
} fossil_sanity_parser_subcommand_t;

typedef struct {
    const char *file_path;  // Path to the INI file
} fossil_sanity_parser_ini_t;

// ==================================================================
// Functions
// ==================================================================

/** @brief Adds a CLI option.
 * 
 * @param name The long name of the option (e.g., "--enable-feature").
 * @param short_name The short name of the option (e.g., "-e").
 * @param type The type of the option (e.g., bool, int, string).
 * @param value Pointer to the variable where the value will be stored.
 * @param description Description of the option for help output.
 */
void fossil_sanity_parser_add_option(const char *name, char short_name, fossil_sanity_parser_option_type_t type, void *value, const char *description);

/** @brief Adds a subcommand.
 * 
 * @param name The name of the subcommand.
 * @param description Description of the subcommand for help output.
 * @param options Array of options for the subcommand.
 * @param option_count Number of options in the array.
 * @param handler Function to handle the subcommand.
 */
void fossil_sanity_parser_add_subcommand(const char *name, const char *description, fossil_sanity_parser_option_t *options, int option_count, int (*handler)(int argc, char **argv));

/** @brief Parses the command-line arguments.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, -1 on error.
 */
int fossil_sanity_parser_parse(int argc, char **argv);

/** @brief Prints help for all commands and options.
 */
void fossil_sanity_parser_print_help(void);

// ==================================================================
// INI functions
// ==================================================================

/** @brief Loads an INI file and populates the options.
 * 
 * @param file_path Path to the INI file.
 * @return 0 on success, -1 on error.
 */
int fossil_sanity_parser_load_ini(const char *file_path);

/** @brief Saves the current options to an INI file.
 * 
 * @param file_path Path to the INI file.
 * @return 0 on success, -1 on error.
 */
int fossil_sanity_parser_save_ini(const char *file_path);

// ==================================================================
// AI enhancements
// ==================================================================

/** @brief Suggests corrections for invalid commands.
 * 
 * @param invalid_command The invalid command to suggest corrections for.
 */
void fossil_sanity_parser_suggest_correction(const char *invalid_command);

/** @brief Sets default values for options using AI.
 */
void fossil_sanity_parser_set_defaults_with_ai(void);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_PARSER_H
