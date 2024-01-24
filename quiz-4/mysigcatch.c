#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler(int signum) {
    printf("SIGINT signal caught!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Register the SIGINT signal handler
    signal(SIGINT, sigint_handler);

    // Make program wait for any input
    // either from the keyboard or from the terminal
    scanf("%*s"); 

    return 0;
}
