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
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_int("123", &output) == true, "Valid integer input");
    FOSSIL_TEST_ASSUME(output == 123, "Output should be 123");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_int("-123", &output) == true, "Valid negative integer input");
    FOSSIL_TEST_ASSUME(output == -123, "Output should be -123");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_int("abc", &output) == false, "Invalid integer input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_int(NULL, &output) == false, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_int("123", NULL) == false, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_validate_float) {
    float output;
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_float("123.45", &output) == true, "Valid float input");
    FOSSIL_TEST_ASSUME(output == 123.45f, "Output should be 123.45");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_float("-123.45", &output) == true, "Valid negative float input");
    FOSSIL_TEST_ASSUME(output == -123.45f, "Output should be -123.45");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_float("abc", &output) == false, "Invalid float input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_float(NULL, &output) == false, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_float("123.45", NULL) == false, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_validate_alnum) {
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_alnum("abc123") == true, "Valid alphanumeric input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_alnum("abc 123") == false, "Invalid alphanumeric input with space");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_alnum("abc@123") == false, "Invalid alphanumeric input with special character");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_alnum(NULL) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_validate_email) {
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_email("test@example.com") == true, "Valid email input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_email("test.example.com") == false, "Invalid email input without @");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_email("test@com") == false, "Invalid email input without domain");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_email(NULL) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_validate_length) {
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_length("test", 5) == true, "Valid length input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_length("test", 4) == true, "Valid length input equal to max length");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_length("test", 3) == false, "Invalid length input exceeding max length");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_is_valid_length(NULL, 5) == false, "Null input");
} // end case

FOSSIL_TEST_CASE(c_sanitize_string) {
    char output[10];
    FOSSIL_TEST_ASSUME(fossil_sanity_in_sanitize_string("test", output, sizeof(output)) == FOSSIL_SANITY_IN_SUCCESS, "Valid sanitize input");
    FOSSIL_TEST_ASSUME(strcmp(output, "test") == 0, "Output should be 'test'");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_sanitize_string("test\n", output, sizeof(output)) == FOSSIL_SANITY_IN_SUCCESS, "Valid sanitize input with non-printable character");
    FOSSIL_TEST_ASSUME(strcmp(output, "test") == 0, "Output should be 'test'");

    FOSSIL_TEST_ASSUME(fossil_sanity_in_sanitize_string("test", output, 3) == FOSSIL_SANITY_ERR_INVALID_LENGTH, "Invalid sanitize input exceeding output size");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_sanitize_string(NULL, output, sizeof(output)) == FOSSIL_SANITY_IN_ERR_NULL_INPUT, "Null input");
    FOSSIL_TEST_ASSUME(fossil_sanity_in_sanitize_string("test", NULL, sizeof(output)) == FOSSIL_SANITY_IN_ERR_NULL_INPUT, "Null output pointer");
} // end case

FOSSIL_TEST_CASE(c_error_message) {
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(FOSSIL_SANITY_IN_SUCCESS), "Success") == 0, "Error message for success");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(FOSSIL_SANITY_IN_ERR_NULL_INPUT), "Null input provided") == 0, "Error message for null input");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(FOSSIL_SANITY_ERR_INVALID_LENGTH), "Invalid input length") == 0, "Error message for invalid length");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(FOSSIL_SANITY_ERR_INVALID_FORMAT), "Invalid input format") == 0, "Error message for invalid format");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(FOSSIL_SANITY_ERR_MEMORY_OVERFLOW), "Memory overflow detected") == 0, "Error message for memory overflow");
    FOSSIL_TEST_ASSUME(strcmp(fossil_sanity_in_error_message(-1), "Unknown error") == 0, "Error message for unknown error");
} // end case

// In need of test cases for log messages, seem to be held back due to Fossil Test laking a way to mock IO.

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

    FOSSIL_TEST_REGISTER(c_sanity_suite);
} // end of group
