#include <stdlib.h>

typedef struct {
    int* arr;
    size_t count;
    size_t capacity;
} vector_t;

vector_t* init_vector(size_t initial_capacity) {
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));

    vec->count = 0;
    vec->capacity = initial_capacity;
    vec->arr = (int*)malloc(sizeof(int) * initial_capacity);

    return vec;
}

void push_vector(vector_t* vec, int value) {
    if (vec->count == vec->capacity) {
        // Double the capacity when it runs out of space
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr, sizeof(int) * vec->capacity);
    }

    vec->arr[vec->count++] = value;
}

int vector_get_at(vector_t* vec, unsigned int index) {
    if (index >= vec->count) {
        return -1;
    }

    return vec->arr[index];
}

void pop_vector(vector_t* vec) {
    if (vec->count > 0) {
        vec->count--;
        if (vec->count <= vec->capacity / 4) {
            // Halve the capacity when count is 25% or less of capacity
            vec->capacity /= 2;
            vec->arr = realloc(vec->arr, sizeof(int) * vec->capacity);
        }
    }
}

void free_vector(vector_t* vec) {
    free(vec->arr);
    free(vec);
}
