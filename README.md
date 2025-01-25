# Dynamic C-Logger-Using-Real-time-Signals

# Dynamically Configured Logger Module

## Overview

This project implements a dynamically configured logger module in C that provides four levels of logging:

- **LOG\_ERROR**: Logs critical error messages.
- **LOG\_WARNING**: Logs warnings, including all error messages.
- **LOG\_INFO**: Logs informational messages, warnings, and errors.
- **LOG\_DEBUG**: Logs detailed debug messages, along with all other levels.

The logging level can be controlled in real-time using Unix signals. A separate application, `set_log_level`, is used to change the logging level dynamically by sending the appropriate signal to the logger process.

## Features

- Real-time control of logging levels via signals.
- Four predefined logging levels: `ERROR`, `WARNING`, `INFO`, and `DEBUG`.
- Ability to disable logging entirely.
- Example actions integrated with specific log levels (e.g., launching a LinkedIn profile or starting GDB debugger).
- Minimal and clean signal-handling mechanism.

---

## Components

The implementation consists of two files:

1. `logger.c`: Contains the main logger functionality, including signal handling and logging functions.
2. `set_log_level.c`: A utility application to dynamically set the logging level by sending signals to the logger process.

### File: `logger.c`

This file implements:

- Signal handling to set the current log level.
- Functions for each log level (e.g., `LOG_ERROR`, `LOG_WARNING`, `LOG_INFO`, `LOG_DEBUG`).
- A simulation of ongoing logging activity in an infinite loop.

### File: `set_log_level.c`

This file implements:

- A utility to send signals to the logger process to change the log level.
- Input validation for the process ID and log level.

---

## Compilation and Execution

### Step 1: Compile the Programs

Compile both `logger.c` and `set_log_level.c` using the following commands:

```bash
gcc -o logger logger.c
gcc -o set_log_level set_log_level.c
```

### Step 2: Run the Logger Program

Run the logger program to start the logging process:

```bash
./logger
```

The program will output its PID, which will be required to change the log levels:

```plaintext
Logger started with PID: <PID>
Use './set_log_level <PID> <level>' to change log levels.
```

### Step 3: Change the Log Level

Use the `set_log_level` utility to send the desired signal to the logger process. The command syntax is:

```bash
./set_log_level <PID> <level>
```

#### Example:

To set the log level to `DEBUG` for a logger process with PID `12345`:

```bash
./set_log_level 12345 debug
```

---

## Supported Log Levels and Signals

| Log Level | Description                    | Signal Code  |
| --------- | ------------------------------ | ------------ |
| `disable` | Disable logging                | `SIGRTMIN+4` |
| `error`   | Log only error messages        | `SIGRTMIN`   |
| `warning` | Log warnings and errors        | `SIGRTMIN+1` |
| `info`    | Log info, warnings, and errors | `SIGRTMIN+2` |
| `debug`   | Log all messages               | `SIGRTMIN+3` |

---

## Code Explanation

### Logger Program (`logger.c`)

#### Key Components:

1. **Signal Handling**:

   - Signals `SIGRTMIN` to `SIGRTMIN+4` are used to set the log level.
   - The `signal_handler` function updates the global `current_log_level` variable based on the received signal.

2. **Logging Functions**:

   - Functions `LOG_ERROR`, `LOG_WARNING`, `LOG_INFO`, and `LOG_DEBUG` print messages based on the current log level.
   - Additional actions, such as launching a LinkedIn profile or starting GDB, are included for demonstration purposes.

3. **Main Loop**:

   - An infinite loop simulates periodic logging of messages at different levels.

#### Example Code Snippet:

```c
void LOG_ERROR(const char *message) {
    if (current_log_level >= LOG_LEVEL_ERROR) {
        printf("[ERROR] %s\n", message);
    }
}
```

### Log Level Setter (`set_log_level.c`)

#### Key Components:

1. **Command-Line Arguments**:

   - The program takes two arguments: the target PID and the desired log level.
   - It validates these arguments and maps the log level to the corresponding signal.

2. **Signal Sending**:

   - The `kill` function is used to send the signal to the target process.

#### Example Code Snippet:

```c
if (strcmp(level, "debug") == 0 || strcmp(level, "4") == 0) {
    signal = SIGRTMIN+3; // Signal for DEBUG log level
}
if (kill(pid, signal) == -1) {
    perror("Failed to send signal");
    return 1;
}
```

---

## Example Usage

1. Start the logger program:

```bash
./logger
```

2. Note the PID displayed by the program (e.g., `12345`).

3. Change the log level to `INFO`:

```bash
./set_log_level 12345 info
```

4. Observe the logger output:

```plaintext
[INFO] This is an info message.
```

5. Disable logging:

```bash
./set_log_level 12345 disable
```

6. Re-enable logging at `DEBUG` level:

```bash
./set_log_level 12345 debug
```

---

## Notes and Limitations

- Signal numbers are based on `SIGRTMIN` for portability. Adjust as needed for your system.
- The example actions (e.g., opening a LinkedIn profile) can be replaced with other actions or removed entirely.
- Ensure that the `logger` program is running and accessible when using `set_log_level`.
- Running `logger` with elevated privileges may be necessary if restricted signals or system actions are used.

---

## Future Enhancements

- Add support for logging to files.
- Implement timestamping for log messages.
- Introduce configuration files for signal-to-level mapping.
- Extend to support multiple concurrent logger processes.

---

## Conclusion

This dynamically configured logger module demonstrates the power and flexibility of signal-based communication in Unix-based systems. The design allows real-time control of logging levels, making it suitable for debugging and monitoring applications.
