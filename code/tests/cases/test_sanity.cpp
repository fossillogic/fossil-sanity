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

    FOSSIL_TEST_ASSUME(config.debug_enabled == DISABLE, "Debug should be disabled by default");
    FOSSIL_TEST_ASSUME(config.logs_enabled == ENABLE, "Logs should be enabled by default");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_WARN, "Default log level should be WARN");
    FOSSIL_TEST_ASSUME(config.log_output == NULL, "Log output should be NULL by default");
    FOSSIL_TEST_ASSUME(config.use_colors == ENABLE, "Colors should be enabled by default");
} // end case

FOSSIL_TEST_CASE(cpp_parse_args) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    std::string args1[] = {"program", "debug=enable", "logs=disable", "colors=disable", "show=error"};
    fossil_sanity_parse_args(5, args1, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == ENABLE, "Debug should be enabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == DISABLE, "Logs should be disabled");
    FOSSIL_TEST_ASSUME(config.use_colors == DISABLE, "Colors should be disabled");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_ERROR, "Log level should be ERROR");

    std::string args2[] = {"program", "no-debug", "logs", "no-colors"};
    fossil_sanity_parse_args(4, args2, &config);
    FOSSIL_TEST_ASSUME(config.debug_enabled == DISABLE, "Debug should be disabled");
    FOSSIL_TEST_ASSUME(config.logs_enabled == ENABLE, "Logs should be enabled");
    FOSSIL_TEST_ASSUME(config.use_colors == DISABLE, "Colors should be disabled");
} // end case

FOSSIL_TEST_CASE(cpp_load_config) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    // Assuming a config file named "test_config.ini" exists with appropriate settings
    fossil_sanity_load_config("test_config.ini", &config);

    // Validate the loaded configuration (assuming known values in the config file)
    FOSSIL_TEST_ASSUME(config.debug_enabled == ENABLE, "Debug should be enabled from config file");
    FOSSIL_TEST_ASSUME(config.logs_enabled == ENABLE, "Logs should be enabled from config file");
    FOSSIL_TEST_ASSUME(config.use_colors == ENABLE, "Colors should be enabled from config file");
    FOSSIL_TEST_ASSUME(config.log_level == FOSSIL_SANITY_LOG_DEBUG, "Log level should be DEBUG from config file");
} // end case

FOSSIL_TEST_CASE(cpp_log_message) {
    fossil_sanity_config config;
    fossil_sanity_init_config(&config);

    // Redirect log output to a file for testing
    FILE *log_file = fopen("test_log.txt", "w");
    config.log_output = log_file;

    fossil_sanity_log(&config, FOSSIL_SANITY_LOG_WARN, "This is a test warning message.");
    fclose(log_file);

    // Validate the log file content
    log_file = fopen("test_log.txt", "r");
    std::string log_content;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), log_file)) {
        log_content += buffer;
    }
    fclose(log_file);

    FOSSIL_TEST_ASSUME(log_content.find("This is a test warning message.") != std::string::npos, "Log message should be present in the log file");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_sanity_test_cases) {
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_get_response);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_init_config);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_parse_args);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_load_config);
    FOSSIL_TEST_ADD(cpp_sanity_suite, cpp_log_message);

    FOSSIL_TEST_REGISTER(cpp_sanity_suite);
} // end of group
