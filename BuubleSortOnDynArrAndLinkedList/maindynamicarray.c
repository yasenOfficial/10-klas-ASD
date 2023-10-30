#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynarr.h"

int* create_array(int count) {
    int* arr = (int*)malloc(count * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        arr[i] = rand() % 100; 
    }

    return arr;
}


int main() {
    DynamicArray arr = init(5);

    pushBack(&arr, 5);
    pushBack(&arr, 2);
    pushBack(&arr, 8);
    pushBack(&arr, 1);
    pushBack(&arr, 9);

    printf("Original array: ");
    for (int i = 0; i < arr.size; i++) {
        printf("%d ", getElement(&arr, i));
    }
    printf("\n");

    bubble_sort_1(arr.buffer, arr.size);

    printf("Sortiran Masiv s (bubble_sort_1): ");
    for (int i = 0; i < arr.size; i++) {
        printf("%d ", getElement(&arr, i));
    }
    printf("\n");

    bubble_sort_2(arr.buffer, arr.size);

    printf("Sotiran Masiv s (bubble_sort_2): ");
    for (int i = 0; i < arr.size; i++) {
        printf("%d ", getElement(&arr, i));
    }
    printf("\n");

    int count = 10;
    int* randomArr = create_array(count);

    printf("Sluchaen Masiv: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", randomArr[i]);
    }
    printf("\n");

    release(&arr);
    free(randomArr);

    return 0;
}

