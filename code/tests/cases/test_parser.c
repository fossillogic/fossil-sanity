/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/test/framework.h>
#include <fossil/sanity/framework.h>


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(c_parser_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_parser_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_parser_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_parser_add_option) {
    bool bool_option = false;
    int int_option = 0;
    char string_option[100] = {0};

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_TYPE_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_TYPE_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_TYPE_STRING, string_option, "Set string value");

    // Assuming we have a way to simulate command-line input
    char *argv[] = {"program", "--enable-feature", "--set-value", "42", "--set-name", "test"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_parse(argc, argv) == 0, "Parser should succeed");
    FOSSIL_TEST_ASSUME(bool_option == true, "Boolean option should be true");
    FOSSIL_TEST_ASSUME(int_option == 42, "Integer option should be 42");
    FOSSIL_TEST_ASSUME(strcmp(string_option, "test") == 0, "String option should be 'test'");
} // end case

bool subcommand_called = false;

int subcommand_handler(int argc, char **argv) {
    (void)argc;
    (void)argv;
    subcommand_called = true;
    return 0;
}

FOSSIL_TEST_CASE(c_parser_add_subcommand) {
    fossil_sanity_parser_option_t options[] = {
        {"--enable-feature", 'e', FOSSIL_SANITY_PARSER_TYPE_BOOL, NULL, "Enable feature"}
    };

    fossil_sanity_parser_add_subcommand("subcmd", "Test subcommand", options, 1, subcommand_handler);

    // Assuming we have a way to simulate command-line input
    char *argv[] = {"program", "subcmd", "--enable-feature"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_parse(argc, argv) == 0, "Parser should succeed");
    FOSSIL_TEST_ASSUME(subcommand_called == true, "Subcommand handler should be called");
} // end case

FOSSIL_TEST_CASE(c_parser_load_ini) {
    // Assuming we have a temporary INI file for testing
    const char *ini_file_path = "test.ini";
    FILE *file = fopen(ini_file_path, "w");
    fprintf(file, "[options]\nenable-feature=true\nset-value=42\nset-name=test\n");
    fclose(file);

    bool bool_option = false;
    int int_option = 0;
    char string_option[100] = {0};

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_TYPE_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_TYPE_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_TYPE_STRING, string_option, "Set string value");

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_load_ini(ini_file_path) == 0, "INI file should load successfully");
    FOSSIL_TEST_ASSUME(bool_option == true, "Boolean option should be true");
    FOSSIL_TEST_ASSUME(int_option == 42, "Integer option should be 42");
    FOSSIL_TEST_ASSUME(strcmp(string_option, "test") == 0, "String option should be 'test'");

    remove(ini_file_path);
} // end case

FOSSIL_TEST_CASE(c_parser_save_ini) {
    // Assuming we have a temporary INI file for testing
    const char *ini_file_path = "test.ini";

    bool bool_option = true;
    int int_option = 42;
    char string_option[100] = "test";

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_TYPE_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_TYPE_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_TYPE_STRING, string_option, "Set string value");

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_save_ini(ini_file_path) == 0, "INI file should save successfully");

    // Verify the contents of the saved INI file
    FILE *file = fopen(ini_file_path, "r");
    char buffer[1024];
    size_t read_size = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[read_size] = '\0'; // Null-terminate the buffer
    fclose(file);

    FOSSIL_TEST_ASSUME(strstr(buffer, "enable-feature=true") != NULL, "INI file should contain 'enable-feature=true'");
    FOSSIL_TEST_ASSUME(strstr(buffer, "set-value=42") != NULL, "INI file should contain 'set-value=42'");
    FOSSIL_TEST_ASSUME(strstr(buffer, "set-name=test") != NULL, "INI file should contain 'set-name=test'");

    remove(ini_file_path);
} // end case

FOSSIL_TEST_CASE(c_parser_set_defaults_with_ai) {
    bool bool_option = false;
    int int_option = 0;
    char string_option[100] = {0};

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_TYPE_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_TYPE_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_TYPE_STRING, string_option, "Set string value");

    fossil_sanity_parser_set_defaults_with_ai();

    // Assuming AI sets some default values
    FOSSIL_TEST_ASSUME(bool_option == true, "Boolean option should be set to true by AI");
    FOSSIL_TEST_ASSUME(int_option == 100, "Integer option should be set to 100 by AI");
    FOSSIL_TEST_ASSUME(strcmp(string_option, "default") == 0, "String option should be set to 'default' by AI");
} // end case



// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_parser_test_cases) {
    FOSSIL_TEST_ADD(c_parser_suite, c_parser_add_option);
    FOSSIL_TEST_ADD(c_parser_suite, c_parser_add_subcommand);
    FOSSIL_TEST_ADD(c_parser_suite, c_parser_load_ini);
    FOSSIL_TEST_ADD(c_parser_suite, c_parser_save_ini);
    FOSSIL_TEST_ADD(c_parser_suite, c_parser_set_defaults_with_ai);

    FOSSIL_TEST_REGISTER(c_parser_suite);
} // end of group
