#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int signalCount = 0;

void customHandler(int signalNumber) {
    printf("\nSignal %d caught.\n", signalNumber);
    signalCount++;

    if (signalCount == 1) {
        printf("If SIGINT is received again reverting to normal behaviour.\n");
    }

    if (signalCount == 2) {
        printf("Restored default behavior for SIGINT.\n");
    }

    if (signalCount >= 3) {
        printf("Exiting.\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, customHandler);

    scanf("%*s");

    return 0;
}
