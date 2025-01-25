#include <stdio.h>  // For input/output operations (e.g., printf, fprintf)
#include <stdlib.h> // For standard library functions (e.g., atoi)
#include <signal.h> // For signal handling (e.g., kill)
#include <string.h> // For string comparison (e.g., strcmp)
#include <unistd.h> // For process functions (e.g., getpid)

// Function to display usage instructions for the program
void print_usage(const char *prog_name) {
    // Print usage format and valid log levels
    printf("Usage: %s <PID> <level>\n", prog_name);
    printf("Levels:\n");
    printf("  0 - Disable logging (SIGINT)\n");
    printf("  1 - Error (SIGUSR1)\n");
    printf("  2 - Warning (SIGUSR2)\n");
    printf("  3 - Info (SIGTERM)\n");
    printf("  4 - Debug (SIGHUP)\n");
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        // If not, print usage instructions and exit with error code
        print_usage(argv[0]);
        return 1;
    }

    // Parse the first argument as the PID of the target process
    pid_t pid = atoi(argv[1]);
    // Store the second argument as the desired log level
    char *level = argv[2];
    int signal; // Variable to hold the signal corresponding to the log level

    // Map the provided log level string or number to the corresponding signal
    if (strcmp(level, "disable") == 0 || strcmp(level, "0") == 0) {
        signal = 44; // Signal to disable logging
    } else if (strcmp(level, "error") == 0 || strcmp(level, "1") == 0) {
        signal = 40 ; // Signal for ERROR log level
    } else if (strcmp(level, "warning") == 0 || strcmp(level, "2") == 0) {
        signal = 41; // Signal for WARNING log level
    } else if (strcmp(level, "info") == 0 || strcmp(level, "3") == 0) {
        signal = 42; // Signal for INFO log level
    } else if (strcmp(level, "debug") == 0 || strcmp(level, "4") == 0) {
        signal = 43; // Signal for DEBUG log level
    } else {
        // If an invalid log level is provided, print an error and usage instructions
        fprintf(stderr, "Invalid log level: %s\n", level);
        print_usage(argv[0]);
        return 1;
    }

    // Attempt to send the signal to the specified process
    if (kill(pid, signal) == -1) {
        // If sending the signal fails, print an error message with details
        perror("Failed to send signal");
        return 1;
    }

    // Confirm that the signal was successfully sent
    printf("Signal %d sent to PID %d for level '%s'\n", signal, pid, level);

    return 0; // Exit successfully
}
