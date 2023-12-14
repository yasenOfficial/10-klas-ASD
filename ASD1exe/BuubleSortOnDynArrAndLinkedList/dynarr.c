#include <stdio.h>
#include <stdlib.h>
#include "dynarr.h"

DynamicArray init(unsigned int capacity) {
    DynamicArray arr;
    arr.buffer = (int *)malloc(capacity * sizeof(int));
    if (arr.buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    arr.capacity = capacity;
    arr.size = 0;
    return arr;
}

int getElement(DynamicArray * arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return arr->buffer[index];
}

void setElement(DynamicArray * arr, int index, int value) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    arr->buffer[index] = value;
}

void pushBack(DynamicArray * arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->buffer = (int *)realloc(arr->buffer, arr->capacity * sizeof(int));
        if (arr->buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    arr->buffer[arr->size] = value;
    arr->size++;
}

int popBack(DynamicArray * arr) {
    if (arr->size == 0) {
        fprintf(stderr, "Array is empty\n");
        exit(EXIT_FAILURE);
    }
    int value = arr->buffer[arr->size - 1];
    arr->size--;
    return value;
}

void release(DynamicArray * arr) {
    free(arr->buffer);
    arr->buffer = NULL;
    arr->capacity = 0;
    arr->size = 0;
}

void pushToIndex(DynamicArray * arr, int index, int value) {
    if (index < 0 || index > arr->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->buffer = (int *)realloc(arr->buffer, arr->capacity * sizeof(int));
        if (arr->buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = arr->size; i > index; i--) {
        arr->buffer[i] = arr->buffer[i - 1];
    }

    arr->buffer[index] = value;
    arr->size++;
}

void pushFront(DynamicArray * arr, int value) {
    pushToIndex(arr, 0, value);
}


void bubble_sort_1(int* arr, int count) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 1; i < count; i++) {
            if (arr[i - 1] > arr[i]) {
                int temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

void bubble_sort_2(int* arr, int count) {
    int swapped;
    for (int i = 0; i < count - 1; i++) {
        swapped = 0;
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

