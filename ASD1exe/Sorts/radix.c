#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 10

int maxDigits(int * arr, int count) {
    int max = 0;

    for(int i = 0; i < count; i++) {
        int digits = 0;
        int num = arr[i];
        if(num < 0)
            num *= -1;

        while(num > 0) {
            num /= 10;
            digits++;
        }
        if(digits > max)
            max = digits;
    }

    return (int)pow(10, (float)max - 1);;
}

void radixSortRec(int *arr, int position, int count) {
    if (position == 0 || count == 0) {
        return;
    }

    int **buckets = (int **)malloc(sizeof(int *) * 19);
    for (int i = 0; i < 19; i++) {
        buckets[i] = (int *)malloc(sizeof(int) * count);
    }

    int bucketCounts[19] = {0};

    for (int i = 0; i < count; i++) {
        int digit = arr[i] / position % 10;
        buckets[9 + digit][bucketCounts[9 + digit]++] = arr[i];
    }

    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < bucketCounts[i]; j++) {
            printf("%d ", buckets[i][j]);
        }
        if(bucketCounts[i])
            printf("\n");
    }
    printf("\n");

    int index = 0;

    for (int i = 0; i < 19; i++) {
        radixSortRec(buckets[i], position / 10, bucketCounts[i]);

        for (int j = 0; j < bucketCounts[i]; j++) {
                arr[index++] = buckets[i][j];
            }
    }
}

void radix_sort(int* arr, unsigned int count) {
    if(count == 0) {
        return;
    }

    int max = maxDigits(arr, count);
    radixSortRec(arr, max, count);
}

int main() {

    int arr[SIZE] = {564, 453, -1218, -75, 22, 1009, -9223, 25553, -33, 0};

    radix_sort(arr, SIZE);

    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    };

    return 0;
}