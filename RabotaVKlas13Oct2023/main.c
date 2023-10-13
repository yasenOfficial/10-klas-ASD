#include <stdio.h>

void merge(int arr[], int left[], int right[], int leftSize, int rightSize) {
    int i, j, arrCount;
    
    for (i = 0, j = 0, arrCount = 0; i < leftSize && j < rightSize;) {
        if (left[i] < right[j]) {
            arr[arrCount] = left[i];
            i++;
        } else {
            arr[arrCount] = right[j];
            j++;
        }
        arrCount++;
    }

    for (; i < leftSize; i++, arrCount++) {
        arr[arrCount] = left[i];
    }

    for (; j < rightSize; j++, arrCount++) {
        arr[arrCount] = right[j];
    }
}


void mergeSort(int arr[], int size) {
    if (size < 2) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, right, mid, size - mid);
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergeSort(arr, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
