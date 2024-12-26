# ***Fossil Sanity by Fossil Logic***

**Fossil Sanity** is a comprehensive suite of sanity checks, designed to ensure the robustness and stability of your C and C++ projects. It offers an integrated framework for validating your code's integrity, identifying errors early, and maintaining overall sanity in development environments. Fossil Sanity ensures that your software meets the necessary quality standards, making it a crucial part of your testing workflow.

Fossil Sanity is built with flexibility in mind and integrates seamlessly with other Fossil Logic tools like **Fossil Test**, **Fossil Mock**, and **Fossil Mark**. This combination makes it an all-in-one toolkit for testing, mocking, benchmarking, and maintaining sanity throughout your development lifecycle.

---

**Key Features:**

| Feature                      | Description                                                                                                                                     |
|------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| **Automated Sanity Checks**   | Automatically validate your project’s integrity by checking for common coding issues, misconfigurations, and basic runtime errors.              |
| **Comprehensive Integration** | Works in tandem with other Fossil tools such as Fossil Test and Fossil Mock, making it an essential part of the entire testing and validation process. |
| **Customizable Thresholds**   | Set thresholds for errors and warnings, allowing teams to tailor the level of sensitivity and the types of errors flagged during development.     |
| **Cross-Platform Support**    | Fossil Sanity is designed to run on multiple platforms, ensuring that your code remains consistent across different environments.                 |
| **Lightweight Performance**   | Lightweight in nature, Fossil Sanity adds minimal overhead to the build process, keeping your workflow efficient without sacrificing checks.       |
| **Clear Error Reporting**     | Provides clear, actionable error reports with a focus on improving code quality by highlighting critical issues that need attention.               |

---

## ***Prerequisites***

To get started with Fossil Sanity, ensure the following are in place:

- **Meson Build System**: Fossil Sanity uses the Meson build system for configuration. If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Fossil Sanity Dependency

To integrate Fossil Sanity into your project, follow these steps:

1. **Install Meson Build System**:
   Install Meson version `1.3` or newer:
   ```sh
   python -m pip install meson           # To install Meson
   python -m pip install --upgrade meson # To upgrade Meson
   ```

2. **Create a `.wrap` File**:
   Add the `fossil-sanity.wrap` file in your `subprojects` directory and include the following content:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-sanity.git
   revision = v0.1.0

   [provide]
   fossil-sanity = fossil_sanity_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil Sanity by adding the following line:
   ```ini
   dep = dependency('fossil-sanity')
   ```

   **Note**: Always use the latest release of Fossil Sanity for the best experience. Visit the [Fossil Sanity Releases](https://github.com/fossillogic/fossil-sanity/releases) page for the latest versions.

---

## Fossil Sanity CLI Usage

The **Fossil Sanity** CLI provides a robust set of commands designed to perform sanity checks, introspect the current system, and provide detailed insights into your project’s health and configuration. Below are the available commands and options to facilitate sanity verification and troubleshooting.

### Commands and Options

| Command                         | Description                                                                                   | Notes                                                                                          |
|----------------------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`                      | Displays the current version of Fossil Sanity.                                                  | Useful for verifying the version of the tool in use.                                          |
| `--help`                         | Shows help message with usage instructions.                                                   | Provides a quick reference for all available commands.                                        |
| `--info`                         | Displays detailed information about the sanity checks performed.                               | Includes information such as the number of checks, status, and configuration.                |
| `sanity`                         | Performs a series of predefined sanity checks to verify the integrity of your project setup.    | Ensures that all essential components are working as expected.                               |
| `introspect`                     | Provides detailed introspection of the current project environment.                            | Allows developers to inspect configuration, dependencies, and other vital project details.    |
| `summary`                        | Generates a concise summary report of the results from the last sanity check.                  | Summarizes key findings, helping to quickly identify potential issues.                        |
| `logs`                           | Displays detailed logs of the last sanity check execution.                                     | Useful for troubleshooting and gaining insights into specific failures or errors.             |

### Key Commands Overview:

- **Version**: Quickly check the installed version of Fossil Sanity.
- **Help**: Access usage instructions and command references.
- **Info**: Provides insights into the performed checks and overall project health.
- **Sanity**: Perform core sanity checks to validate system and project configuration.
- **Introspect**: Analyze the project setup in detail, such as configuration files, dependencies, and environment variables.
- **Summary**: Generate a high-level report summarizing the results of the most recent sanity checks.
- **Logs**: View detailed logs for deeper diagnostics or troubleshooting of issues.

### Usage

To use the **Fossil Sanity** CLI, navigate to your project directory and run the desired command. Here are examples of the most commonly used commands:

- To check the version of **Fossil Sanity**, run:
  
  ```sh
  fossil-sanity --version
  ```

- To display help information for all available commands:
  
  ```sh
  fossil-sanity --help
  ```

- To view detailed information about the most recent sanity check:

  ```sh
  fossil-sanity --info
  ```

- To perform a series of sanity checks on your project:

  ```sh
  fossil-sanity sanity
  ```

- To introspect your project environment, view configuration, and dependency details:

  ```sh
  fossil-sanity introspect
  ```

- To generate a concise summary of the results from the most recent sanity check:

  ```sh
  fossil-sanity summary
  ```

- To view the detailed logs of the last sanity check execution:

  ```sh
  fossil-sanity logs
  ```

---

## Configure Sanity Checks

To configure which sanity checks to enable or disable, use the following command:

```sh
meson setup builddir -Dwith_sanity_checks=enabled
```

This command allows you to enable additional checks or modify the scope of the sanity tests to suit your project's needs.

---

## ***Contributing and Support***

If you would like to contribute, have questions, or need help, feel free to open an issue on the [Fossil Sanity GitHub repository](https://github.com/fossillogic/fossil-sanity) or consult the [Fossil Logic Docs](https://fossillogic.com/docs).

---

## ***Conclusion***

**Fossil Sanity** provides an essential suite of sanity checks and introspection tools that ensure your project is set up correctly and functioning as expected. Whether you're debugging issues, validating configurations, or simply ensuring a clean environment, Fossil Sanity helps you maintain the integrity of your project. Combined with Fossil Test, Fossil Mock, and Fossil Mark, Fossil Sanity is part of an integrated toolkit that ensures quality, reliability, and performance across the development lifecycle.
