#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }

        swap(&arr[i + 1], &arr[right]);

        quickSort(arr, left, i); // Sotiraj lqvata strana
        quickSort(arr, i + 1, right); // Sotiraj dqsna strana

    }
}

int main()
{
    int arr[] = {2, 5, 1, 3, 4};
    int arrSize = 5;

    quickSort(arr, 0, arrSize - 1);

    printf("Sotiran Masiv: ");
    for (int i = 0; i < arrSize; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
    
}
