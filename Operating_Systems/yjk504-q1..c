#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Flag to indicate if SIGUSR2 has been received
volatile sig_atomic_t sigusr2_received = 0;
// Counter for the number of SIGINT signals received
volatile sig_atomic_t sigint_count = 0;

// Signal handler for SIGINT (Ctrl+C)
void sigint_handler(int signo) {
    printf("\nReceived SIGINT. Total count: %d\n", ++sigint_count);
}

// Signal handler for SIGUSR2
void sigusr2_handler(int signo) {
    printf("\nReceived SIGUSR2. Terminating the program.\n");
    sigusr2_received = 1;
}

int main() {
    // Print process id (PID)
    printf("PID: %d\n", getpid());   // (1pt)

    // Block the SIGUSR1 signal
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL); // (1pt)

    // Set up the SIGINT (Ctrl+C) signal handler
    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);   // (3pt)

    printf("Program starts waiting for SIGUSR2...\n");

    // Set up the SIGUSR2 signal handler and
    // Check flag in a while loop using sigsuspend
    // Block SIGUSR2 before the while loop
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    struct sigaction sa_usr2;
    sa_usr2.sa_handler = sigusr2_handler;
    sa_usr2.sa_flags = 0;
    sigaction(SIGUSR2, &sa_usr2, NULL);

    while (!sigusr2_received) {
        sigsuspend(&mask);
    }

    printf("Got SIGUSR2, terminating the program.\n");

    // Restore the oldmask which was obtained when blocking SIGUSR2
    sigprocmask(SIG_UNBLOCK, &mask, NULL);   // (5pt)

    return 0;
}
