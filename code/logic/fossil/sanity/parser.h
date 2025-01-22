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

// ==================================================================
// Types
// ==================================================================

// Types of command argument
typedef enum {
    FOSSIL_SANITY_PARSER_BOOL,   // Boolean (enable/disable)
    FOSSIL_SANITY_PARSER_STRING, // String argument
    FOSSIL_SANITY_PARSER_INT,    // Integer argument
    FOSSIL_SANITY_PARSER_COMBO   // Combo of predefined values
} fossil_sanity_parser_arg_type_t;

// Structure to represent each argument in the command
typedef struct fossil_sanity_parser_argument_s {
    char *name;                                   // Argument name
    fossil_sanity_parser_arg_type_t type;         // Argument type
    char *value;                                  // Parsed value
    char **combo_options;                         // Valid options for COMBO type
    int combo_count;                              // Number of valid options
    struct fossil_sanity_parser_argument_s *next; // Next argument in the list
} fossil_sanity_parser_argument_t;

// Structure for a command
typedef struct fossil_sanity_parser_command_s {
    char *name;                                  // Command name
    char *description;                           // Command description
    fossil_sanity_parser_argument_t *arguments;  // List of arguments
    struct fossil_sanity_parser_command_s *prev; // Previous command in the list
    struct fossil_sanity_parser_command_s *next; // Next command in the list
} fossil_sanity_parser_command_t;

// Structure for the command palette
typedef struct fossil_sanity_parser_palette_s {
    char *name;                               // Palette name
    char *description;                        // Palette description
    fossil_sanity_parser_command_t *commands; // List of commands
} fossil_sanity_parser_palette_t;

// ==================================================================
// Functions
// ==================================================================

/**
 * @brief Creates a new parser palette.
 *
 * @param name The name of the palette.
 * @param description A description of the palette.
 * @return A pointer to the newly created parser palette.
 */
fossil_sanity_parser_palette_t *fossil_sanity_parser_create_palette(const char *name, const char *description);

/**
 * @brief Adds a command to the parser palette.
 *
 * @param palette The parser palette to which the command will be added.
 * @param command_name The name of the command.
 * @param description A description of the command.
 * @return A pointer to the newly added command.
 */
fossil_sanity_parser_command_t *fossil_sanity_parser_add_command(fossil_sanity_parser_palette_t *palette, const char *command_name, const char *description);

/**
 * @brief Adds an argument to a command.
 *
 * @param command The command to which the argument will be added.
 * @param arg_name The name of the argument.
 * @param arg_type The type of the argument.
 * @param combo_options (Optional) Array of valid options for COMBO type.
 * @param combo_count (Optional) Number of options for COMBO type.
 * @return A pointer to the newly added argument.
 */
fossil_sanity_parser_argument_t *fossil_sanity_parser_add_argument(fossil_sanity_parser_command_t *command, const char *arg_name, fossil_sanity_parser_arg_type_t arg_type, char **combo_options, int combo_count);

/**
 * @brief Parses the command-line arguments using the parser palette.
 *
 * @param palette The parser palette to use for parsing.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 */
void fossil_sanity_parser_parse(
    fossil_sanity_parser_palette_t *palette,
    int argc,
    char **argv);

/**
 * @brief Frees the memory allocated for the parser palette.
 *
 * @param palette The parser palette to be freed.
 */
void fossil_sanity_parser_free(fossil_sanity_parser_palette_t *palette);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_SANITY_PARSER_H
