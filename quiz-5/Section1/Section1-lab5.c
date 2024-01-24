#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    void* data;
    int size;
    int capacity;
    int elemSize;
} Vector;

int vector_init(Vector* vec, int elemSize) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    vec->elemSize = elemSize;
    return 0;
}

void vector_destroy(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

int vector_push_back(Vector* vec, void* value) {
    // Check if reallocation is needed
    if (vec->size == vec->capacity) {
        // Double the capacity (or set initial capacity if it's 0)
        int newCapacity = (vec->capacity == 0) ? 1 : vec->capacity * 2;

        // Reallocate memory
        void* newData = realloc(vec->data, newCapacity * vec->elemSize);
        if (newData == NULL) {
            printf("Memory reallocation failed\n");
            return 1;
        }

        // Update vector members
        vec->data = newData;
        vec->capacity = newCapacity;
    }

    // Copy the value to the end of the vector
    void* destination = (char*)vec->data + vec->size * vec->elemSize;
    memcpy(destination, value, vec->elemSize);

    // Increment the size
    vec->size++;

    return 0;
}

int vector_pop(Vector* vec, void* out) {
    // Decrement the size
    vec->size--;

    // Copy the last element to the 'out' parameter
    void* source = (char*)vec->data + vec->size * vec->elemSize;
    memcpy(out, source, vec->elemSize);

    return 0; // Pop successful
}

int vector_remove(Vector* vec, int index) {
    // Shift elements after the removed index to fill the gap
    void* destination = (char*)vec->data + index * vec->elemSize;
    void* source = (char*)vec->data + (index + 1) * vec->elemSize;
    int numBytesToMove = (vec->size - index - 1) * vec->elemSize;
    memmove(destination, source, numBytesToMove);

    // Decrement the size
    vec->size--;

    return 0; // Removal successful
}

int main() {
    Vector vec;
    vector_init(&vec, sizeof(int));

    int i;
    for (i = 0; i < 10; i++) {
        vector_push_back(&vec, &i);
        printf("Pushed value: %d\n", i);
    }

    int value;
    vector_pop(&vec, &value);
    printf("Popped value: %d\n", value);
    vector_pop(&vec, &value);
    printf("Popped value: %d\n", value);

    vector_remove(&vec, 3);
    printf("Removed value at index 3 \n");

    int j=521;
    vector_push_back(&vec, &j);

    printf("Pushed value: %d\n",j);

    for (i = 0; i < vec.size; i++) {
        int* element = (int*)((char*)vec.data + i * vec.elemSize);
        printf("%d\n", *element);
    }

    vector_destroy(&vec);

    return 0;
}