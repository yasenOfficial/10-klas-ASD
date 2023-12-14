#include <stdio.h>
#include <stdlib.h>

// Избрах да сортирам по последната цифра на числото, защото е по-лесно за имплементиране
void radixSortRecursion(int arr[], unsigned int n, int up, int max) {
    int output[n];
    int kofa[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / up) % 10;
        kofa[digit]++; // Увеличаваме броя на елементите в кофата за съответната последна цифра
    }

    //Принт Кофи
    for (int i = 0; i < 10; i++) {
        printf("Kofa[%d] = %d\n", i, kofa[i]);
    }

    // Изчисляваме позицията от която трябва да започне групата елементи със сегашната цифра в масива output
    for (int i = 1; i < 10; i++) {
        kofa[i] += kofa[i - 1];
        printf("Pozitsiq na zapochvane na elementi v (kofa [%d]): %d\n", i, kofa[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        int digitAtCurrentPlace = (arr[i] / up) % 10;

        output[kofa[digitAtCurrentPlace] - 1] = arr[i];

        kofa[digitAtCurrentPlace]--;

        printf("DigitAtCurrentPlace = %d\n", digitAtCurrentPlace);
        printf("kofa[%d] = %d\n", digitAtCurrentPlace, kofa[digitAtCurrentPlace]);
        printf("output[%d] = %d\n", kofa[digitAtCurrentPlace], arr[i]);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    if (up < max) {
        radixSortRecursion(arr, n, up * 10, max);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    // ------------------------------

    int arr1[] = {170, 45, 75, 90, 802, 24, 2, 66, 42, 12}; // Голям Масив (Разбъркан)
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Originalen Masiv 1: ");
    printArray(arr1, n1);

    radixSortRecursion(arr1, n1, 1, arr1[0]);

    printf("Sortiran Masiv 1: ");
    printArray(arr1, n1);

    // ------------------------------

    int arr2[] = {5, 4, 3, 2, 1}; // Обратен Масив
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("\nOriginalen Masiv 2: ");
    printArray(arr2, n2);

    radixSortRecursion(arr2, n2, 1, arr2[0]);

    printf("Sortiran Masiv 2: ");
    printArray(arr2, n2);

    // ------------------------------


    int arr3[] = {55, 40, 40, 660, 55}; // Масив с повтарящи се елементи
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("\nOriginalen Masiv 3: ");
    printArray(arr3, n3);

    radixSortRecursion(arr3, n3, 1, arr3[0]);

    printf("Sortiran Masiv 3: ");
    printArray(arr3, n3);

    // ------------------------------

    int arr4[] = {1, 4, 2}; // Масив с 3 елемента (малък)
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("\nOriginalen Masiv 4: ");
    printArray(arr4, n4);

    radixSortRecursion(arr4, n4, 1, arr4[0]);

    printf("Sortiran Masiv 4: ");
    printArray(arr4, n4);

    // ------------------------------


    int arr5[] = {1, 2, 3, 4, 5}; // Масив с 5 елемента (Сортиран)
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("\nOriginalen Masiv 5: ");
    printArray(arr5, n5);

    radixSortRecursion(arr5, n5, 1, arr5[0]);

    printf("Sortiran Masiv 5: ");
    printArray(arr5, n5);

    // ------------------------------


    int arr6[] = {}; // Празен Масив
    int n6 = 0;

    printf("\nOriginalen Masiv 6: ");
    printArray(arr6, n6);

    radixSortRecursion(arr6, n6, 1, arr6[0]);

    printf("Sortiran Masiv 6: ");
    printArray(arr6, n6);

    // ------------------------------

    return 0;
}

