# **Fossil Sanity by Fossil Logic**

**Fossil Sanity** is a powerful logging library designed to help developers maintain clarity and control over their project's runtime behavior. It enables comprehensive logging, allowing developers to track the internal workings of their system, monitor runtime anomalies, and ensure software stability across different environments.

Fossil Sanity provides seamless integration with your C or C++ projects, offering tools for logging different types of messages (info, debug, error, etc.), custom log formats, and cross-platform support. It is built for developers who need a robust logging mechanism to track and troubleshoot issues during development, testing, and production stages.

---

**Key Features:**

| Feature                        | Description                                                                                             |
|--------------------------------|---------------------------------------------------------------------------------------------------------|
| **Comprehensive Logging**      | Support for various log levels (info, debug, warning, error), ensuring flexible message tracking.       |
| **Custom Log Formats**         | Define custom log formats to suit project needs, whether for concise messages or detailed outputs.      |
| **Cross-Platform Support**     | Works across multiple platforms, ensuring consistent logging behavior in different environments.         |
| **Performance-Friendly**       | Optimized to minimize performance impact, even during intensive logging operations.                      |
| **Configurable Log Levels**    | Set custom thresholds for different log levels, providing fine-grained control over logging behavior.    |
| **Log File Management**        | Includes options for managing log files, with automatic rotation and archival features.                 |
| **Command-Line Control**       | Control logging behavior, log levels, and more via simple CLI commands.                                 |

---

## ***Prerequisites***

To get started with **Fossil Sanity**, ensure you have the following:

- **Meson Build System**: Fossil Sanity uses the Meson build system for configuration. If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Fossil Sanity to Your Project

To integrate **Fossil Sanity** into your project:

1. **Install Meson**:
   Install or upgrade Meson version `1.3` or newer:
   ```sh
   python -m pip install meson           # To install Meson
   python -m pip install --upgrade meson # To upgrade Meson
   ```

2. **Create a `.wrap` File**:
   Add the `fossil-sanity.wrap` file in your `subprojects` directory:
   ```ini
   [wrap-git]
   url = https://github.com/fossillogic/fossil-sanity.git
   revision = v0.1.0

   [provide]
   fossil-sanity = fossil_sanity_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil Sanity by adding:
   ```ini
   dep = dependency('fossil-sanity')
   ```

---

## Fossil Sanity Command Palette

The **Fossil Sanity** CLI provides a range of commands to control logging behavior, set log levels, and handle log rotation. It supports both short and long commands, with and without the `=` sign.

### Commands and Options

| Command                         | Description                                                                                     | Notes                                                                                  |
|----------------------------------|-------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------|
| `--version`                      | Displays the current version of Fossil Sanity.                                                    | Use to verify the version of the tool in use.                                          |
| `--help`                         | Shows help message with all available commands.                                                  | Provides guidance for how to use the CLI and details on all options.                   |
| `log`                            | Starts logging and writes messages at specified log levels.                                       | Enables logging for runtime diagnostics.                                               |
| `rotate-logs`                    | Manages log file rotation, ensuring log files are handled properly when they reach a certain size. | Helps prevent log files from growing too large.                                        |
| `set-log-level`                  | Configures the logging level (e.g., info, debug, error).                                          | Allows for dynamic control over the verbosity of logs.                                |
| `clear-logs`                     | Clears all logs from the current session.                                                         | Useful for cleaning up logs before starting a new session.                             |
| `view-logs`                      | Displays the current log contents.                                                                | Allows you to inspect logged messages in real-time.                                    |
| `debug=enable`                   | Enables debug logging.                                                                            | Use `debug=disable` to disable.                                                        |
| `logs=enable`                    | Enables logging output.                                                                           | Use `logs=disable` to disable.                                                         |
| `colors=enable`                  | Enables color output in logs.                                                                     | Use `colors=disable` to disable.                                                       |
| `show=prod`                      | Displays logs for production level messages only.                                                 | Other options: `warn`, `error`, `critical`, `debug`.                                   |
| `show=warn`                      | Displays warning level messages and above.                                                        |                                                                                         |
| `show=error`                     | Displays error level messages and above.                                                         |                                                                                         |
| `show=critical`                  | Displays only critical error messages.                                                            |                                                                                         |
| `show=debug`                     | Displays all logs, including debug level messages.                                                |                                                                                         |

### Example Commands:

- To check the version of **Fossil Sanity**:
  ```sh
  fossil-sanity --version
  ```

- To view help information:
  ```sh
  fossil-sanity --help
  ```

- To start logging:
  ```sh
  fossil-sanity log
  ```

- To rotate logs when a file size exceeds a threshold:
  ```sh
  fossil-sanity rotate-logs
  ```

- To set the log level to 'debug':
  ```sh
  fossil-sanity set-log-level debug
  ```

- To clear all logs from the current session:
  ```sh
  fossil-sanity clear-logs
  ```

- To view the current logs:
  ```sh
  fossil-sanity view-logs
  ```

- To enable debug logging:
  ```sh
  fossil-sanity debug=enable
  ```

- To disable logs:
  ```sh
  fossil-sanity logs=disable
  ```

- To disable color output in logs:
  ```sh
  fossil-sanity colors=disable
  ```

- To show production logs only:
  ```sh
  fossil-sanity show=prod
  ```

---

## Configure Logging Levels

To customize the logging levels or other logging options, you can use the following:

```sh
meson setup builddir -Dlogging_level=debug
```

This command allows you to fine-tune your logging configuration, adjusting the verbosity and log handling to suit your project's needs.

---

## ***Contributing and Support***

For contributions, questions, or support, visit the [Fossil Sanity GitHub repository](https://github.com/fossillogic/fossil-sanity) or check out the [Fossil Logic Docs](https://fossillogic.com/docs).

---

## ***Conclusion***

**Fossil Sanity** is an essential tool for tracking and logging runtime information, ensuring you can debug and monitor your C and C++ projects effectively. Whether you're fine-tuning performance, identifying bugs, or maintaining logs in production, Fossil Sanity provides a comprehensive solution. Integrated with other Fossil Logic tools, it forms a complete toolkit for developers who need robust, cross-platform logging capabilities.
