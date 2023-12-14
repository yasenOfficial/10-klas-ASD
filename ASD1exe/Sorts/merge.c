#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void merge_sort(int* arr, int count) {
    if(count <= 1) {
        return;
    }

    int mid = count / 2;
    int* left = arr;
    int* right = arr + mid;
    printf("mid=%d, left=%p, right=%p\n", mid, left, right);

    merge_sort(left, mid);
    merge_sort(right, count - mid);
    printf("merge_sort(%p, %d) end\n", arr, count);

    int* tmp = malloc(sizeof(int) * count);
    int lIndex = 0;
    int rIndex = 0;

    for(int i = 0; i < count; i++) {
        printf("i=%d lIndex=%d(%d) rIndex=%d(%d)\n", i, lIndex, mid, rIndex, count - mid);

        if (
            lIndex >= mid ||
            (
                rIndex < (count - mid) && 
                left[lIndex] > right[rIndex]
            )
        )
            tmp[i] = right[rIndex++];
        else
            tmp[i] = left[lIndex++];
    }

    memcpy(arr, tmp, sizeof(int) * count);
    free(tmp);
    tmp = NULL;
    
    puts("After merge: ");
    print_arr(arr, count);
}

