// test_example.c
#include <stdio.h>
#include <assert.h>

void dummyLibFunction();
void testFunction() {
    // Test something
    assert(1 == 1); // Example test
    // More tests
}

int main() {
    dummyLibFunction();
    testFunction();
    printf("All tests passed.\n");
    return 0;
}
