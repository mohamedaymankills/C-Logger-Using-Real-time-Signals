#include <stdio.h>  // For input/output operations (e.g., printf)
#include <stdlib.h> // For standard library functions (e.g., system())
#include <signal.h> // For handling signals
#include <unistd.h> // For process and sleep functions

// Define log levels as constants for better readability
#define LOG_LEVEL_DISABLED 0 // Logging is disabled
#define LOG_LEVEL_ERROR    1 // Log only ERROR messages
#define LOG_LEVEL_WARNING  2 // Log WARNING and higher severity messages
#define LOG_LEVEL_INFO     3 // Log INFO and higher severity messages
#define LOG_LEVEL_DEBUG    4 // Log all messages including DEBUG

// Variable to store the current log level; initialized to DISABLED
int current_log_level = LOG_LEVEL_DISABLED;

// Signal handler function to handle log level changes
void signal_handler(int sig) {
    // Switch based on the received signal to adjust log level
    switch (sig) {
        case SIGUSR1: // Signal to set log level to ERROR
            current_log_level = LOG_LEVEL_ERROR;
            printf("Log level set to: ERROR (1)\n");
            break;
        case SIGUSR2: // Signal to set log level to WARNING
            current_log_level = LOG_LEVEL_WARNING;
            printf("Log level set to: WARNING (2)\n");
            break;
        case SIGTERM: // Signal to set log level to INFO
            current_log_level = LOG_LEVEL_INFO;
            printf("Log level set to: INFO (3)\n");
            break;
        case SIGHUP: // Signal to set log level to DEBUG
            current_log_level = LOG_LEVEL_DEBUG;
            printf("Log level set to: DEBUG (4)\n");
            break;
        case SIGINT: // Signal to disable logging
            current_log_level = LOG_LEVEL_DISABLED;
            printf("Log level set to: DISABLED (0)\n");
            break;
        default: // Handle any unexpected signals
            printf("Unknown signal received: %d\n", sig);
    }
}

// Function to log ERROR messages
void LOG_ERROR(const char *message) {
    // Log only if the current level is ERROR
    if (current_log_level == LOG_LEVEL_ERROR) {
        printf("[ERROR] %s\n", message);
    }
}

// Function to log WARNING messages
void LOG_WARNING(const char *message) {
    // Log only if the current level is WARNING
    if (current_log_level == LOG_LEVEL_WARNING) {
        printf("[WARNING] %s\n", message);
    }
}

// Function to log INFO messages
void LOG_INFO(const char *message) {
    // Log only if the current level is INFO
    if (current_log_level == LOG_LEVEL_INFO) {
        printf("[INFO] %s\n", message);

        // Example action: Launch a LinkedIn profile in the browser
        int status = system("firefox https://www.linkedin.com/in/mohamed-ayman-78361a251?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app");
    }
}

// Function to log DEBUG messages
void LOG_DEBUG(const char *message) {
    // Log only if the current level is DEBUG
    if (current_log_level == LOG_LEVEL_DEBUG) {
        printf("[DEBUG] %s\n", message);

        // Example action: Launch the GDB debugger
        int status = system("gdb");
    }
}

// Main function
int main() {
    // Register signal handlers for log level changes
    signal(SIGUSR1, signal_handler); // Handle SIGUSR1 for ERROR level
    signal(SIGUSR2, signal_handler); // Handle SIGUSR2 for WARNING level
    signal(SIGTERM, signal_handler); // Handle SIGTERM for INFO level
    signal(SIGHUP, signal_handler);  // Handle SIGHUP for DEBUG level
    signal(SIGINT, signal_handler);  // Handle SIGINT to disable logging

    // Print the logger's PID so the user can send signals to it
    printf("Logger started with PID: %d\n", getpid());
    printf("Use './set_log <PID> <level>' to change log levels.\n");

    // Infinite loop to simulate ongoing processing and logging
    while (1) {
        // Example log messages
        LOG_ERROR("This is an error message.");   // Error-level log
        LOG_WARNING("This is a warning message."); // Warning-level log
        LOG_INFO("This is an info message.");      // Info-level log
        LOG_DEBUG("This is a debug message.");     // Debug-level log

        // Sleep to simulate processing delay (adjusted to 100 seconds for testing)
        sleep(100);
    }

    return 0; // Program should never reach here
}

