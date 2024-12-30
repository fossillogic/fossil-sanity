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
FOSSIL_TEST_SUITE(cpp_sanity_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_sanity_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_sanity_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_get_response) {
    fossil_sanity_log_level levels[] = {
        FOSSIL_SANITY_LOG_PROD,
        FOSSIL_SANITY_LOG_WARN,
        FOSSIL_SANITY_LOG_ERROR,
        FOSSIL_SANITY_LOG_CRITICAL,
        FOSSIL_SANITY_LOG_DEBUG
    };

    for (size_t i = 0; i < sizeof(levels) / sizeof(levels[0]); i++) {
        const char *response = fossil_sanity_get_response(levels[i]);
        FOSSIL_TEST_ASSUME(response != NULL, "Response should not be NULL");
    }
} // end case

FOSSIL_TEST_CASE(cpp_init_config) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled by default");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled by default");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_WARN, "Default log level should be WARN");
    FOSSIL_TEST_ASSUME(config.log_output == NULL, "Log output should be NULL by default");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled by default");
} // end case

FOSSIL_TEST_CASE(cpp_parse_args) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    const char *args1[] = {"sanity", "--debug", "--no-logs", "--no-colors", "--show-error"};
    fossil_sanity_parse_args(5, const_cast<char **>(args1), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == false, "Logs should be disabled");
    FOSSIL_TEST_ASSUME(config.use_colors == false, "Colors should be disabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_ERROR, "Log level should be ERROR");

    const char *args2[] = {"sanity", "--no-debug", "--logs", "--no-colors"};
    fossil_sanity_parse_args(4, const_cast<char **>(args2), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == false, "Colors should be disabled");

    const char *args3[] = {"sanity", "--no-debug", "--logs", "--colors", "--show-warn"};
    fossil_sanity_parse_args(5, const_cast<char **>(args3), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_WARN, "Log level should be WARN");

    const char *args4[] = {"sanity", "--debug", "--logs", "--colors", "--show-critical"};
    fossil_sanity_parse_args(5, const_cast<char **>(args4), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_CRITICAL, "Log level should be CRITICAL");

    const char *args5[] = {"sanity", "--debug", "--logs", "--colors", "--show-debug"};
    fossil_sanity_parse_args(5, const_cast<char **>(args5), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_DEBUG, "Log level should be DEBUG");

    const char *args6[] = {"sanity", "--debug", "--logs", "--colors", "--show-prod"};
    fossil_sanity_parse_args(5, const_cast<char **>(args6), &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_PROD, "Log level should be PROD");
} // end case

// In need of test cases for log messages, seem to be held back due to Fossil Test laking a way to mock IO.

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_sanity_test_cases) {
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_get_response);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_init_config);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_parse_args);

    FOSSIL_TEST_REGISTER(cpp_sanity_suite);
} // end of group
