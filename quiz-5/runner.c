#include <stdio.h>

void dummyLibFunction();

void runForever() {
    while(1) {
    dummyLibFunction();
        // You can perform some operations here if needed
        // For example, you can print a message:
        printf("Running...\n");

        // Optionally, you can make the program sleep for a while
        // to prevent it from consuming too much CPU time:
         sleep(3);  // sleep for 1 second
    }
}

int main() {
    runForever();
    return 0;
}
