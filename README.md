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

### **Example: Setting Up and Parsing Commands**

```c
#include <stdio.h>
#include <stdlib.h>
#include "fossil/sanity/framework.h"

int main(int argc, char **argv) {
    // Step 1: Create a parser palette
    fossil_sanity_parser_palette_t *palette = fossil_sanity_parser_create_palette(
        "MyTool Palette", 
        "A palette for parsing MyTool commands."
    );

    // Step 2: Add a command
    fossil_sanity_parser_command_t *add_command = fossil_sanity_parser_add_command(
        palette, 
        "add", 
        "Adds a new item to the list."
    );

    // Step 3: Add arguments to the 'add' command
    fossil_sanity_parser_add_argument(add_command, "name", FOSSIL_SANITY_PARSER_STRING, NULL, 0);
    fossil_sanity_parser_add_argument(add_command, "priority", FOSSIL_SANITY_PARSER_COMBO, 
        (char *[]){"high", "medium", "low"}, 3);
    fossil_sanity_parser_add_argument(add_command, "urgent", FOSSIL_SANITY_PARSER_BOOL, NULL, 0);

    // Step 4: Add another command
    fossil_sanity_parser_command_t *list_command = fossil_sanity_parser_add_command(
        palette, 
        "list", 
        "Lists all items."
    );

    // Step 5: Parse command-line arguments
    fossil_sanity_parser_parse(palette, argc, argv);

    // Step 6: Free the parser palette
    fossil_sanity_parser_free(palette);

    return 0;
}
```

---

### **Features**

- Dynamic Help: Use `--help` or `--help <command>` to get detailed information.
- Dynamic Usage: Add arguments dynamically with support for combos and booleans.
- Extendable: Easily add more commands and arguments using the provided API.

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
