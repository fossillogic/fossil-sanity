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

FOSSIL_TEST_CASE(c_get_response) {
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

FOSSIL_TEST_CASE(c_init_config) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled by default");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled by default");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_WARN, "Default log level should be WARN");
    FOSSIL_TEST_ASSUME(config.log_output == NULL, "Log output should be NULL by default");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled by default");
} // end case

FOSSIL_TEST_CASE(c_parse_args) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    char *args1[] = {"sanity", "--debug", "--no-logs", "--no-colors", "--show-error"};
    fossil_sanity_parse_args(5, args1, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == false, "Logs should be disabled");
    FOSSIL_TEST_ASSUME(config.use_colors == false, "Colors should be disabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_ERROR, "Log level should be ERROR");

    char *args2[] = {"sanity", "--no-debug", "--logs", "--no-colors"};
    fossil_sanity_parse_args(4, args2, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == false, "Colors should be disabled");

    char *args3[] = {"sanity", "--no-debug", "--logs", "--colors", "--show-warn"};
    fossil_sanity_parse_args(5, args3, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == false, "Debug should be disabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_WARN, "Log level should be WARN");

    char *args4[] = {"sanity", "--debug", "--logs", "--colors", "--show-critical"};
    fossil_sanity_parse_args(5, args4, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_CRITICAL, "Log level should be CRITICAL");

    char *args5[] = {"sanity", "--debug", "--logs", "--colors", "--show-debug"};
    fossil_sanity_parse_args(5, args5, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_DEBUG, "Log level should be DEBUG");

    char *args6[] = {"sanity", "--debug", "--logs", "--colors", "--show-prod"};
    fossil_sanity_parse_args(5, args6, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == true, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == true, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == true, "Colors should be enabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_PROD, "Log level should be PROD");
} // end case

// In need of test cases for log messages, seem to be held back due to Fossil Test laking a way to mock IO.

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_sanity_test_cases) {
    FOSSIL_TEST_ADD(c_sanity_suite, c_get_response);
    FOSSIL_TEST_ADD(c_sanity_suite, c_init_config);
    FOSSIL_TEST_ADD(c_sanity_suite, c_parse_args);

    FOSSIL_TEST_REGISTER(c_sanity_suite);
} // end of group
