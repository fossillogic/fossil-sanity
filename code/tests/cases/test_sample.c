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
FOSSIL_TEST_SUITE(c_sample_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_sample_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_sample_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_validate_integer) {
    const char *valid_input = "12345";
    const char *invalid_input = "12a45";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_integer(valid_input) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_integer(invalid_input) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

FOSSIL_TEST_CASE(c_validate_string) {
    const char *valid_input = "hello";
    const char *invalid_input = "hello!";
    const char *allowed_chars = "abcdefghijklmnopqrstuvwxyz";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_string(valid_input, allowed_chars) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_string(invalid_input, allowed_chars) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

FOSSIL_TEST_CASE(c_check_message_clarity) {
    const char *clear_message = "This is a clear message.";
    const char *unclear_message = "Ths s n clr msg.";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(clear_message) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(unclear_message) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

FOSSIL_TEST_CASE(c_check_grammar) {
    const char *correct_message = "This is a correct message.";
    const char *incorrect_message = "This is a incorrect message.";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(correct_message) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(incorrect_message) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_sample_test_cases) {
    FOSSIL_TEST_ADD(c_sample_suite, c_validate_integer);
    FOSSIL_TEST_ADD(c_sample_suite, c_validate_string);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_message_clarity);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_grammar);

    FOSSIL_TEST_REGISTER(c_sample_suite);
} // end of group
