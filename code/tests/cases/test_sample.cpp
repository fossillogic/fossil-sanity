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
#include <string>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(cpp_sample_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_sample_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_sample_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

#include <string>

FOSSIL_TEST_CASE(cpp_validate_integer) {
    std::string valid_input = "12345";
    std::string invalid_input = "12a45";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_integer(valid_input.c_str()) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_integer(invalid_input.c_str()) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

FOSSIL_TEST_CASE(cpp_validate_string) {
    std::string valid_input = "hello";
    std::string invalid_input = "hello!";
    std::string allowed_chars = "abcdefghijklmnopqrstuvwxyz";

    // Test cases
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_string(valid_input.c_str(), allowed_chars.c_str()) == FOSSIL_SANITY_TRUE, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(fossil_sanity_validate_string(invalid_input.c_str(), allowed_chars.c_str()) == FOSSIL_SANITY_FALSE, "Should have passed the test case");
} // end case

FOSSIL_TEST_CASE(cpp_check_message_clarity) {
    std::string clear_message = "This is a clear and understandable message.";
    std::string unclear_message = "Thss s unlrr messg."; // Poorly written
    std::string vague_message = "Hello."; // Too vague
    std::string long_message = "This message is excessively long and contains so many words that it is difficult to understand what it is trying to say in the first place."; // ensure limit is at 20 words per message at max
    std::string short_message = "Hi!"; // Super complex and extremely clear message with lots of information.. Sarcasm of course upon an equally vague message.

    // Test cases for message clarity
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(clear_message.c_str()) == true, 
                       "Clear message should pass clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(unclear_message.c_str()) == false, 
                       "Unclear message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(vague_message.c_str()) == false, 
                       "Vague message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(long_message.c_str()) == false, 
                       "Excessively long message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(short_message.c_str()) == false, 
                       "Too short message should fail clarity check.");
}

FOSSIL_TEST_CASE(cpp_check_grammar) {
    std::string correct_message = "This is a valid sentence.";
    std::string incorrect_message = "this is not grammatically correct"; // Missing punctuation and capitalization
    std::string fragment_message = "Running quickly."; // Lacks a subject
    std::string null_message; // Empty string case

    // Test cases for grammar check
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(correct_message.c_str()) == true, 
                       "Correct message should pass grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(incorrect_message.c_str()) == false, 
                       "Incorrect message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(fragment_message.c_str()) == false, 
                       "Fragmented sentence should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(null_message.c_str()) == false, 
                       "Empty message should fail grammar check.");
}

FOSSIL_TEST_CASE(cpp_check_rotbrain_message) {
    std::string clear_message = "This is a clear and understandable message.";
    std::string unclear_message = "Thss s unlrr messg."; // Poorly written
    std::string vague_message = "Hello."; // Too vague
    std::string long_message = "This message is excessively long and contains so many words that it is difficult to understand what it is trying to say in the first place."; // ensure limit is at 20 words per message at max
    std::string short_message = "Hi!"; // Super complex and extremely clear message with lots of information.. Sarcasm of course upon an equally vague message.
    std::string rotbrain_message = "Th1s m3ss4g3 h4s r0tb41n t3rm5."; // Contains rotbrain terms
    std::string rotbrain_message_2 = "This message is lit and full of vibe."; // Contains rotbrain terms
    std::string rotbrain_message_3 = "Yeet! This is so sus."; // Contains rotbrain terms

    // Test cases for message clarity
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(clear_message.c_str()) == true, 
                       "Clear message should pass clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(unclear_message.c_str()) == false, 
                       "Unclear message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(vague_message.c_str()) == false, 
                       "Vague message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(long_message.c_str()) == false, 
                       "Excessively long message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(short_message.c_str()) == false, 
                       "Too short message should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message.c_str()) == false, 
                       "Message with rotbrain terms should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message_2.c_str()) == false, 
                       "Message with rotbrain terms should fail clarity check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_message_clarity(rotbrain_message_3.c_str()) == false, 
                       "Message with rotbrain terms should fail clarity check.");
}

FOSSIL_TEST_CASE(cpp_check_rotbrain_grammar) {
    std::string correct_message = "This is a valid sentence.";
    std::string incorrect_message = "this is not grammatically correct"; // Missing punctuation and capitalization
    std::string fragment_message = "Running quickly."; // Lacks a subject
    std::string null_message; // Empty string case
    std::string rotbrain_message = "Th1s s3nt3nc3 h4s r0tb41n t3rm5."; // Contains rotbrain terms
    std::string rotbrain_message_2 = "This sentence is lit and full of vibe."; // Contains rotbrain terms
    std::string rotbrain_message_3 = "Yeet! This is so sus."; // Contains rotbrain terms

    // Test cases for grammar check
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(correct_message.c_str()) == true, 
                       "Correct message should pass grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(incorrect_message.c_str()) == false, 
                       "Incorrect message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(fragment_message.c_str()) == false, 
                       "Fragmented sentence should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(null_message.c_str()) == false, 
                       "Empty message should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message.c_str()) == false, 
                       "Message with rotbrain terms should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message_2.c_str()) == false, 
                       "Message with rotbrain terms should fail grammar check.");
    FOSSIL_TEST_ASSUME(fossil_sanity_check_grammar(rotbrain_message_3.c_str()) == false, 
                       "Message with rotbrain terms should fail grammar check.");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_sample_test_cases) {
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_validate_integer);
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_validate_string);
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_check_message_clarity);
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_check_grammar);
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_check_rotbrain_message);
    FOSSIL_TEST_ADD(cpp_sample_suite, cpp_check_rotbrain_grammar);

    FOSSIL_TEST_REGISTER(cpp_sample_suite);
} // end of group