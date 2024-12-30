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
    const char *clear_message = "This is a clear and understandable message.";
    const char *unclear_message = "Thss s unlrr messg."; // Poorly written
    const char *vague_message = "Hello."; // Too vague
    const char *long_message = "This message is excessively long and contains so many words that it is difficult to understand what it is trying to say in the first place."; // ensure limit is at 20 words per message at max
    const char *short_message = "Hi!"; // Super complex and extreamly clear message with lots of information.. Sarcasum of course upon an equally vague message.

    // Test cases for message clarity
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(clear_message) == true, 
                       "Clear message should pass clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(unclear_message) == false, 
                       "Unclear message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(vague_message) == false, 
                       "Vague message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(long_message) == false, 
                       "Excessively long message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(short_message) == false, 
                       "Too short message should fail clarity check.");
}

FOSSIL_TEST_CASE(c_check_grammar) {
    const char *correct_message = "This is a valid sentence.";
    const char *incorrect_message = "this is not grammatically correct"; // Missing punctuation and capitalization
    const char *fragment_message = "Running quickly."; // Lacks a subject
    const char *null_message = NULL; // Null pointer case

    // Test cases for grammar check
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(correct_message) == true, 
                       "Correct message should pass grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(incorrect_message) == false, 
                       "Incorrect message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(fragment_message) == false, 
                       "Fragmented sentence should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(null_message) == false, 
                       "Null message should fail grammar check.");
}

FOSSIL_TEST_CASE(c_check_rotbrain_message) {
    const char *clear_message = "This is a clear and understandable message.";
    const char *unclear_message = "Thss s unlrr messg."; // Poorly written
    const char *vague_message = "Hello."; // Too vague
    const char *long_message = "This message is excessively long and contains so many words that it is difficult to understand what it is trying to say in the first place."; // ensure limit is at 20 words per message at max
    const char *short_message = "Hi!"; // Super complex and extremely clear message with lots of information.. Sarcasm of course upon an equally vague message.
    const char *rotbrain_message = "Th1s m3ss4g3 h4s r0tb41n t3rm5."; // Contains rotbrain terms
    const char *rotbrain_message_2 = "This message is lit and full of vibe."; // Contains rotbrain terms
    const char *rotbrain_message_3 = "Yeet! This is so sus."; // Contains rotbrain terms

    // Test cases for message clarity
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(clear_message) == true, 
                       "Clear message should pass clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(unclear_message) == false, 
                       "Unclear message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(vague_message) == false, 
                       "Vague message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(long_message) == false, 
                       "Excessively long message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(short_message) == false, 
                       "Too short message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message) == false, 
                       "Message with rotbrain terms should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message_2) == false, 
                       "Message with rotbrain terms should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message_3) == false, 
                       "Message with rotbrain terms should fail clarity check.");
}

FOSSIL_TEST_CASE(c_check_rotbrain_grammar) {
    const char *correct_message = "This is a valid sentence.";
    const char *incorrect_message = "this is not grammatically correct"; // Missing punctuation and capitalization
    const char *fragment_message = "Running quickly."; // Lacks a subject
    const char *null_message = ""; // Empty string case
    const char *rotbrain_message = "Th1s s3nt3nc3 h4s r0tb41n t3rm5."; // Contains rotbrain terms
    const char *rotbrain_message_2 = "This sentence is lit and full of vibe."; // Contains rotbrain terms
    const char *rotbrain_message_3 = "Yeet! This is so sus."; // Contains rotbrain terms

    // Test cases for grammar check
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(correct_message) == true, 
                       "Correct message should pass grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(incorrect_message) == false, 
                       "Incorrect message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(fragment_message) == false, 
                       "Fragmented sentence should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(null_message) == false, 
                       "Empty message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message) == false, 
                       "Message with rotbrain terms should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message_2) == false, 
                       "Message with rotbrain terms should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message_3) == false, 
                       "Message with rotbrain terms should fail grammar check.");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_sample_test_cases) {
    FOSSIL_TEST_ADD(c_sample_suite, c_validate_integer);
    FOSSIL_TEST_ADD(c_sample_suite, c_validate_string);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_message_clarity);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_grammar);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_rotbrain_message);
    FOSSIL_TEST_ADD(c_sample_suite, c_check_rotbrain_grammar);

    FOSSIL_TEST_REGISTER(c_sample_suite);
} // end of group
