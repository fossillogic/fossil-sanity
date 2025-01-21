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
FOSSIL_TEST_SUITE(c_sanity_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_sanity_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_sanity_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_validate_int) {
    int output;
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_int("123", &output) == true, "Valid integer input");
    FOSSIL_TEST_ASSUME(output == 123, "Output should be 123");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_int("-123", &output) == true, "Valid negative integer input");
    FOSSIL_TEST_ASSUME(output == -123, "Output should be -123");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_int("abc", &output) == false, "Invalid integer input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_int(NULL, &output) == false, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_int("123", NULL) == false, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_validate_float) {
    float output;
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_float("123.45", &output) == true, "Valid float input");
    FOSSIL_TEST_ASSUME(output == 123.45f, "Output should be 123.45");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_float("-123.45", &output) == true, "Valid negative float input");
    FOSSIL_TEST_ASSUME(output == -123.45f, "Output should be -123.45");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_float("abc", &output) == false, "Invalid float input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_float(NULL, &output) == false, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_float("123.45", NULL) == false, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_validate_alnum) {
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_alnum("abc123") == true, "Valid alphanumeric input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_alnum("abc 123") == false, "Invalid alphanumeric input with space");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_alnum("abc@123") == false, "Invalid alphanumeric input with special character");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_alnum(NULL) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_validate_email) {
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_email("test@example.com") == true, "Valid email input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_email("test.example.com") == false, "Invalid email input without @");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_email("test@com") == false, "Invalid email input without domain");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_email(NULL) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_validate_length) {
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_length("test", 5) == true, "Valid length input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_length("test", 4) == true, "Valid length input equal to max length");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_length("test", 3) == false, "Invalid length input exceeding max length");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_is_length(NULL, 5) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_sanitize_string) {
    char output[10];
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_sanitize_string("test", output, sizeof(output)) == FOSSIL_SANITY_IN_SUCCESS, "Valid sanitize input");
    FOSSIL_TEST_ASSUME(strcmp(output, "test") == 0, "Output should be 'test'");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_sanitize_string("test\n", output, sizeof(output)) == FOSSIL_SANITY_IN_SUCCESS, "Valid sanitize input with non-printable character");
    FOSSIL_TEST_ASSUME(strcmp(output, "test") == 0, "Output should be 'test'");

    FOSSIL_TEST_ASSUME(fossil_sanity_validate_sanitize_string("test", output, 3) == FOSSIL_SANITY_ERR_INVALID_LENGTH, "Invalid sanitize input exceeding output size");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_sanitize_string(NULL, output, sizeof(output)) == FOSSIL_SANITY_IN_ERR_NULL_INPUT, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_sanitize_string("test", NULL, sizeof(output)) == FOSSIL_SANITY_IN_ERR_NULL_INPUT, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_error_message) {
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_validate_error_message(FOSSIL_SANITY_IN_SUCCESS), "Success") == 0, "Error message for success");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_validate_error_message(FOSSIL_SANITY_IN_ERR_NULL_INPUT), "Null input provided") == 0, "Error message for null input");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_validate_error_message(FOSSIL_SANITY_ERR_INVALID_LENGTH), "Invalid input length") == 0, "Error message for invalid length");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_validate_error_message(FOSSIL_SANITY_ERR_INVALID_FORMAT), "Invalid input format") == 0, "Error message for invalid format");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_validate_error_message(FOSSIL_SANITY_ERR_MEMORY_OVERFLOW), "Memory overflow detected") == 0, "Error message for memory overflow");
} // end case

// In need of test cases for log messages, seem to be held back due to Fossil Test laking a way to mock IO.



FOSSIL_TEST_CASE(c_parser_add_option) {
    bool bool_option = false;
    int int_option = 0;
    char string_option[100] = {0};

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_OPTION_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_OPTION_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_OPTION_STRING, string_option, "Set string value");

    // Assuming we have a way to simulate command-line input
    char *argv[] = {"program", "--enable-feature", "--set-value", "42", "--set-name", "test"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_parse(argc, argv) == 0, "Parser should succeed");
    FOSSIL_TEST_ASSUME(bool_option == true, "Boolean option should be true");
    FOSSIL_TEST_ASSUME(int_option == 42, "Integer option should be 42");
    FOSSIL_TEST_ASSUME(strcmp(string_option, "test") == 0, "String option should be 'test'");
} // end case

FOSSIL_TEST_CASE(c_parser_add_subcommand) {
    bool subcommand_called = false;

    int subcommand_handler(int argc, char **argv) {
        subcommand_called = true;
        return 0;
    }

    fossil_sanity_parser_option_t options[] = {
        {"--enable-feature", 'e', FOSSIL_SANITY_PARSER_OPTION_BOOL, NULL, "Enable feature"}
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

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_OPTION_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_OPTION_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_OPTION_STRING, string_option, "Set string value");

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

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_OPTION_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_OPTION_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_OPTION_STRING, string_option, "Set string value");

    FOSSIL_TEST_ASSUME(fossil_sanity_parser_save_ini(ini_file_path) == 0, "INI file should save successfully");

    // Verify the contents of the saved INI file
    FILE *file = fopen(ini_file_path, "r");
    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), file);
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

    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_OPTION_BOOL, &bool_option, "Enable feature");
    fossil_sanity_parser_add_option("--set-value", 's', FOSSIL_SANITY_PARSER_OPTION_INT, &int_option, "Set integer value");
    fossil_sanity_parser_add_option("--set-name", 'n', FOSSIL_SANITY_PARSER_OPTION_STRING, string_option, "Set string value");

    fossil_sanity_parser_set_defaults_with_ai();

    // Assuming AI sets some default values
    FOSSIL_TEST_ASSUME(bool_option == true, "Boolean option should be set to true by AI");
    FOSSIL_TEST_ASSUME(int_option == 100, "Integer option should be set to 100 by AI");
    FOSSIL_TEST_ASSUME(strcmp(string_option, "default") == 0, "String option should be set to 'default' by AI");
} // end case



// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_sanity_test_cases) {
    FOSSIL_TEST_ADD(c_sanity_suite, c_validate_int);
    FOSSIL_TEST_ADD(c_sanity_suite, c_validate_float);
    FOSSIL_TEST_ADD(c_sanity_suite, c_validate_alnum);
    FOSSIL_TEST_ADD(c_sanity_suite, c_validate_email);
    FOSSIL_TEST_ADD(c_sanity_suite, c_validate_length);
    FOSSIL_TEST_ADD(c_sanity_suite, c_sanitize_string);
    FOSSIL_TEST_ADD(c_sanity_suite, c_error_message);

    // Add the new test cases to the test group
    FOSSIL_TEST_ADD(c_sanity_suite, c_parser_add_option);
    FOSSIL_TEST_ADD(c_sanity_suite, c_parser_add_subcommand);
    FOSSIL_TEST_ADD(c_sanity_suite, c_parser_load_ini);
    FOSSIL_TEST_ADD(c_sanity_suite, c_parser_save_ini);
    FOSSIL_TEST_ADD(c_sanity_suite, c_parser_set_defaults_with_ai);

    FOSSIL_TEST_REGISTER(c_sanity_suite);
} // end of group
