#include <stdio.h>
#include <stdlib.h>

void bubbleSort1(int *arr, int size) {
    int temp;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubbleSort2(int *arr, int size) {
    int temp;
    int swapped = 1;

    while (swapped) {
        swapped = 0;  
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;  
            }
        }
    }
}

int *createArray(int size) {
    int *arr = malloc(size * sizeof(int));
    return arr;
}

int main() {
    int size = 5;
    int *arr = createArray(size);


    arr[0] = 2;
    arr[1] = 1;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 3;

    printf("Before sorting with method 1:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    bubbleSort1(arr, size);

    printf("After sorting with method 1:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }


    arr[0] = 2;
    arr[1] = 1;
    arr[2] = 5;
    arr[3] = 4;
    arr[4] = 3;

    printf("Before sorting with method 2:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    bubbleSort2(arr, size);

    printf("After sorting with method 2:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}