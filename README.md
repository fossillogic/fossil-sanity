# **Fossil Sanity Utility Kit by Fossil Logic**

**Fossil Sanity** is a robust utility kit designed to streamline user input validation, command-line interface (CLI) management, and logging for C and C++ projects. This all-in-one solution simplifies application workflows by ensuring consistent validation, intuitive CLI interfaces, and efficient logging mechanisms, making it an essential tool for developers seeking clarity and control.

With its modular design, **Fossil Sanity** offers highly configurable validation rules, a smart and extensible command parser, and advanced logging capabilities that enhance debugging and monitoring across platforms.

---

## **Key Utilities**

| Feature                          | Description                                                                                                     |
|----------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **Input Validation**             | Provides built-in validation for strings, numbers, and more, ensuring data accuracy and reliability.             |
| **Custom Rules**                 | Define flexible, project-specific validation rules to meet any requirement.                                     |
| **Cross-Platform CLI Support**   | Ensures consistent behavior and output across different platforms.                                              |
| **Efficient Logging**            | Optimized logging system with configurable levels, smart formatting, and real-time notifications.                |
| **CLI Command Parsing**          | Simplifies handling of user commands with an intelligent parser and support for dynamic argument management.     |
| **Log Management**               | Features such as log rotation and critical alerts keep your application’s logging organized and insightful.      |
| **Dynamic CLI Features**         | Offers dynamic help commands (`--help`, `--help <command>`) and flexible argument options (e.g., combos, booleans). |

---

## **Why Use Fossil Sanity?**

- **Consistent CLI Experience:** Simplifies creating and managing command-line interfaces with a clear structure and dynamic argument handling.  
- **Error-Free Input:** Avoids runtime issues by validating inputs before processing.  
- **Enhanced Debugging:** Detailed, formatted logs with severity levels ensure issues can be identified and resolved quickly.  
- **Seamless Integration:** Built for C and C++ environments with minimal setup and performance overhead.  

---

## **Getting Started**

### **Prerequisites**

To use **Fossil Sanity**, ensure the following:  
- **Meson Build System**: Required for configuring and integrating Fossil Sanity. Install it from the [Meson website](https://mesonbuild.com/Getting-meson.html).

### **Setup Instructions**

1. **Install Meson**  
   Install or upgrade Meson to version `1.3` or newer:

   ```sh
   python -m pip install meson           # Install Meson
   python -m pip install --upgrade meson # Upgrade Meson
   ```

2. **Add the Library**  
   Create a `.wrap` file in your `subprojects` directory:

   ```ini
   [wrap-git]
   url = https://github.com/fossillogic/fossil-sanity.git
   revision = v0.1.1

   [provide]
   fossil-sanity = fossil_sanity_dep
   ```

3. **Integrate the Dependency**  
   Add the following to your `meson.build` file:

   ```meson
   dep = dependency('fossil-sanity')
   ```

---

## **Example: Building a CLI with Validation and Logging**

```c
#include <stdio.h>
#include <stdlib.h>
#include "fossil/sanity/framework.h"

int main(int argc, char **argv) {
    // Initialize a CLI parser
    fossil_sanity_parser_palette_t *palette = fossil_sanity_parser_create_palette(
        "ExampleApp", 
        "Command-line interface for ExampleApp."
    );

    // Add commands and arguments
    fossil_sanity_parser_command_t *add_command = fossil_sanity_parser_add_command(
        palette, 
        "add", 
        "Adds an item."
    );
    fossil_sanity_parser_add_argument(add_command, "name", FOSSIL_SANITY_PARSER_STRING, NULL, 0);
    fossil_sanity_parser_add_argument(add_command, "priority", FOSSIL_SANITY_PARSER_COMBO, 
        (char *[]){"high", "medium", "low"}, 3);

    // Parse user input
    fossil_sanity_parser_parse(palette, argc, argv);

    // Log actions
    fossil_sanity_log_info("Command executed successfully.");

    // Clean up
    fossil_sanity_parser_free(palette);

    return 0;
}
```

---

### **Key Features in Action**

- **Validation:** Automatically ensures the correctness of input arguments.  
- **Command Parsing:** Quickly define commands with multiple argument types (e.g., strings, enums, booleans).  
- **Logging:** Output informative logs with customizable severity levels (e.g., info, warning, error).  

---

## **Configuring Build Options**

To enable testing or additional features during setup, use the following command:  

```sh
meson setup builddir -Dwith_test=enabled
```

---

## **Contributing and Support**

We welcome contributions! For questions, issues, or contributions, visit the [Fossil Sanity GitHub repository](https://github.com/fossillogic/fossil-sanity) or check out our detailed documentation at [Fossil Logic Docs](https://fossillogic.com/docs).

---

## **Conclusion**

**Fossil Sanity** is your go-to utility kit for input validation, consistent CLI interfaces, and effective logging. Its user-friendly API and cross-platform support make it an invaluable addition to any C or C++ project. Pair it with other tools from **Fossil Logic** to build stable, efficient, and maintainable software.
