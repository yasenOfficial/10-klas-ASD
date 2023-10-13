#include <stdio.h>

int binarySearch(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1; 
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid; // NAMERENO
    } else if (arr[mid] > target) {
        return binarySearch(arr, left, mid - 1, target);  // Tursi na Lqvo
    } else {
        return binarySearch(arr, mid + 1, right, target); // Tursi na Dqsno
    }
}

int main() {
    int arr[] = {1, 9, 4, 7, 19, 61, 13};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 61;
    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1) {
        printf("%d Ne Namereno\n", target);
    } else {
        printf("%d NAmereno na index %d\n", target, result);
    }

    return 0;
}
