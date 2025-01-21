# **Fossil Sanity by Fossil Logic**

**Fossil Sanity** is a comprehensive validation, logging, and command parsing library designed to help developers maintain clarity and control over user input, application state, and debugging information. It offers a powerful suite of tools to track the correctness of inputs, monitor anomalies, and ensure software stability across diverse environments, particularly for C and C++ projects.

With a focus on seamless integration, Fossil Sanity ensures robust input validation, customizable logging features, intelligent command parsing, and real-time feedback on user actions and application errors. Additionally, it leverages cutting-edge AI techniques to enhance feature functionality and provide smarter, context-aware assistance to developers.

---

## **Key Features**

| Feature                          | Description                                                                                                     |
|----------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **Comprehensive Validation**     | Supports validation for various input types (e.g., strings, numbers), ensuring flexibility and reliability.     |
| **Custom Validation Rules**      | Allows developers to define tailored validation rules for simple checks or complex requirements.               |
| **Cross-Platform Support**       | Ensures consistent validation behavior across multiple platforms and environments.                             |
| **Performance-Friendly**         | Optimized to minimize performance overhead, even for intensive validation tasks.                               |
| **Configurable Validation Levels** | Enables fine-grained control over validation thresholds to align with project-specific needs.                 |
| **Notification Management**      | Built-in tools for automatic alerts and logging to keep you informed of validation outcomes and issues.        |
| **Log Rotation and Notifications** | Logs critical issues, rotates log files when size thresholds are reached, and sends notifications for key logs. |
| **Command Parser**               | A built-in command parser to validate, parse, and process user input efficiently.                              |
| **Smart Log Formatting**         | Automatically formats log entries based on severity levels, with options for real-time notifications and alerts. |

---

## **Prerequisites**

Before integrating **Fossil Sanity** into your project, ensure the following:

- **Meson Build System**: Fossil Sanity leverages Meson for configuration. Follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html) if you don’t already have it installed.

---

### **Adding Fossil Sanity to Your Project**

1. **Install Meson**  
   Install or upgrade Meson (version `1.3` or newer):

   ```sh
   python -m pip install meson           # Install Meson
   python -m pip install --upgrade meson # Upgrade Meson
   ```

2. **Add a `.wrap` File**  
   Create a `fossil-sanity.wrap` file in your `subprojects` directory:

   ```ini
   [wrap-git]
   url = https://github.com/fossillogic/fossil-sanity.git
   revision = v0.1.0

   [provide]
   fossil-sanity = fossil_sanity_dep
   ```

3. **Integrate the Dependency**  
   Add the following to your `meson.build` file to include Fossil Sanity:

   ```meson
   dep = dependency('fossil-sanity')
   ```

---

### Sample Usage

#### Code Snippet (C)

```c
#include <stdio.h>
#include <string.h>
#include <fossil/sanity/framework.h>


int main(int argc, char **argv) {
    // Initialize log queue
    fossil_sanity_log_queue_t log_queue;
    fossil_sanity_log_init(&log_queue);

    // Set up command-line options
    bool enable_feature = false;
    int some_option = 0;
    fossil_sanity_parser_add_option("--enable-feature", 'e', FOSSIL_SANITY_PARSER_BOOL, &enable_feature, "Enable some feature");
    fossil_sanity_parser_add_option("--some-option", 's', FOSSIL_SANITY_PARSER_INT, &some_option, "Set some option");

    // Add a subcommand
    fossil_sanity_parser_option_t subcommand_options[] = {
        {"--sub-option", 'o', FOSSIL_SANITY_PARSER_STRING, NULL, "Subcommand option"}
    };
    fossil_sanity_parser_add_subcommand("subcommand", "Subcommand description", subcommand_options, 1, NULL);

    // Parse command-line arguments
    if (fossil_sanity_parser_parse(argc, argv) != 0) {
        fossil_sanity_log_notify("Error parsing arguments.");
        return 1;
    }

    // Log a message with smart logging
    fossil_sanity_log_smart_log(&log_queue, FOSSIL_SANITY_LOG_LEVEL_INFO, FOSSIL_SANITY_LOG_SEVERITY_LOW, "Application started.");

    // AI-powered feature to set defaults
    fossil_sanity_parser_set_defaults_with_ai();

    // Process logs
    fossil_sanity_log_push(&log_queue, "This is a test log message.", 1, FOSSIL_SANITY_LOG_SEVERITY_HIGH);

    // Print logs
    fossil_sanity_log_print(&log_queue);

    // Suggest a correction for an invalid command
    fossil_sanity_parser_suggest_correction("subcomand");

    // Handle INI file
    if (fossil_sanity_parser_load_ini("config.ini") == 0) {
        fossil_sanity_log_notify("INI file loaded successfully.");
    } else {
        fossil_sanity_log_notify("Error loading INI file.");
    }

    // Save options to INI
    if (fossil_sanity_parser_save_ini("config.ini") == 0) {
        fossil_sanity_log_notify("Options saved to INI file.");
    } else {
        fossil_sanity_log_notify("Error saving options.");
    }

    // Clear the log queue at the end
    fossil_sanity_log_clear(&log_queue);

    return 0;
}

```

#### Example Log Output

```ini
[INFO] Application started.
[INFO] INI file loaded successfully.
[INFO] Options saved to INI file.
```

#### Example Command Error

```ini
Did you mean 'subcommand'?
```

---

## **Configure Build Options**

To configure the build system with testing enabled, use the following command:

```sh
meson setup builddir -Dwith_test=enabled
```

---

## **Contributing and Support**

We welcome contributions! If you have questions, encounter issues, or wish to contribute, visit the [Fossil Sanity GitHub repository](https://github.com/fossillogic/fossil-sanity) or explore our detailed documentation at the [Fossil Logic Docs](https://fossillogic.com/docs).

---

## **Conclusion**

**Fossil Sanity** is an essential library for maintaining input validation, runtime monitoring, and logging in your C and C++ projects. Whether you are debugging, optimizing performance, or ensuring stability in production, Fossil Sanity equips you with the tools needed to stay in control. When paired with other **Fossil Logic** tools, it provides a complete solution for reliable validation and logging across platforms.
