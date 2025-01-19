# **Fossil Sanity by Fossil Logic**

**Fossil Sanity** is a powerful validation library designed to help developers maintain clarity and control over user input in their projects. With its robust validation tools, developers can track the correctness of inputs, monitor anomalies, and ensure software stability across diverse environments.

This library provides seamless integration with C and C++ projects, offering capabilities to validate various types of inputs (e.g., strings, numbers), define custom validation rules, and work efficiently across platforms. It is specifically built for developers who require a reliable validation mechanism for debugging, testing, and ensuring smooth production operations. Additionally, it features notification and logging tools to keep developers informed about validation status and potential issues.

---

## **Key Features**

| Feature                        | Description                                                                                             |
|--------------------------------|---------------------------------------------------------------------------------------------------------|
| **Comprehensive Validation**   | Supports validation for various input types (e.g., strings, numbers) to ensure flexibility and reliability. |
| **Custom Validation Rules**    | Allows developers to define tailored validation rules for simple checks or complex requirements.        |
| **Cross-Platform Support**     | Ensures consistent validation behavior across multiple platforms and environments.                      |
| **Performance-Friendly**       | Optimized to minimize performance overhead, even for intensive validation tasks.                        |
| **Configurable Validation Levels** | Enables fine-grained control over validation thresholds to align with project-specific needs.         |
| **Notification Management**    | Provides built-in tools for automatic alerts and logging to keep you informed of validation outcomes.    |

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
#include <fossil/sanity/framework.h>  // Include the fossil_sanity header


int main(void) {
    char username[100];
    char password[100];
    
    // Step 1: Get username input with validation
    fossil_sanity_in_error_t input_result = fossil_sanity_in_get_username(username, sizeof(username));
    if (input_result != FOSSIL_SANITY_IN_SUCCESS) {
        fossil_sanity_out_log("error.log", FOSSIL_SANITY_OUT_ERROR, "Failed to read username.");
        return 1;
    }

    // Step 2: Get password input securely
    input_result = fossil_sanity_in_get_password(password, sizeof(password));
    if (input_result != FOSSIL_SANITY_IN_SUCCESS) {
        fossil_sanity_out_log("error.log", FOSSIL_SANITY_OUT_ERROR, "Failed to read password.");
        return 1;
    }

    // Step 3: Log successful input
    fossil_sanity_out_log("app.log", FOSSIL_SANITY_OUT_INFO, "User input successfully captured.");
    
    // Step 4: Perform some action, like authentication or processing

    return 0;
}
```

#### Example Log Output (app.log)

```ini
[INFO] User input successfully captured.
```

#### Example Log Output (error.log)

```ini
[ERROR] Failed to read username.
[ERROR] Failed to read password.
```

---

### Explanation

1. **Input Handling**:
    - `fossil_sanity_in_get_username` and `fossil_sanity_in_get_password` are used to capture user input, with built-in validation for correctness and security.
    - If any input function fails, an error is logged using `fossil_sanity_out_log` to track the issue.

2. **Output Handling**:
    - The program logs a successful input capture in the `app.log` file and any errors (e.g., failure to read username or password) in the `error.log` file.

3. **Logging Severity**:
    - Logs are written with different severity levels (e.g., INFO, ERROR) to help categorize messages. Logs are written to different files for better organization.

---

This example shows how to integrate input validation and logging with `fossil_sanity` in a typical C application. The functions `fossil_sanity_in_get_*` handle user input securely, while `fossil_sanity_out_log` ensures proper output and error tracking.

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

**Fossil Sanity** is an essential library for maintaining input validation and runtime monitoring in your C and C++ projects. Whether you are debugging, optimizing performance, or maintaining stability in production, Fossil Sanity equips you with the tools you need to stay in control. Paired with other Fossil Logic tools, it provides a complete solution for developers seeking reliable and cross-platform validation capabilities.
