#include <stdio.h>

int find_max(int* arr, unsigned int count) {
    int max = arr[0];
    for (unsigned int i = 1; i < count; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void counting_sort(int* arr, int count, int digit) {
    int output[count];
    int count_array[10] = {0};

    for (int i = 0; i < count; i++) {
        count_array[(arr[i] / digit) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count_array[i] += count_array[i - 1];
    }

    for (int i = count - 1; i >= 0; i--) {
        output[count_array[(arr[i] / digit) % 10] - 1] = arr[i];
        count_array[(arr[i] / digit) % 10]--;
    }

    for (int i = 0; i < count; i++) {
        arr[i] = output[i];
    }
}

void radix_sort_recursive(int* arr, int count, int digit, int start, int end) {
    if (digit > 100 || start >= end) {
        return;
    }
    counting_sort(&arr[start], end - start, digit);
    printf("Step (Digit %d): ", digit);
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    radix_sort_recursive(arr, count, digit * 10, start, end);
}

void radix_sort(int* arr, int count) {
    int max = find_max(arr, count);

    printf("Initial array: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    radix_sort_recursive(arr, count, 1, 0, count);

    printf("Sorted array: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {999, 777, 333, 444, 99, 33, 73, 13};
    int count = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, count);

    return 0;
}