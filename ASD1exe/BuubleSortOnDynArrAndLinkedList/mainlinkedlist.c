#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"

LinkedList* create_array(int count) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *list = init();  // Initialize the linked list

    // Fill the linked list with random values (you can customize this part)
    for (int i = 0; i < count; i++) {
        int value = (int)(rand() % 100);  // Fill with random values between 0 and 99
        pushBack(list, value);
    }

    return list;
}


int main() {
    srand(time(NULL));  // Seed the random number generator

    LinkedList list = init();

    pushBack(&list, 5.0);
    pushBack(&list, 2.0);
    pushBack(&list, 8.0);
    pushBack(&list, 1.0);
    pushBack(&list, 9.0);

    printf("Originalen List: ");
    printElements(&list);

    bubble_sort_1(&list);
    printf("Sotiran list (bubble_sort_1): ");
    printElements(&list);

    bubble_sort_2(&list);
    printf("Sortiran list (bubble_sort_2): ");
    printElements(&list);

    int count = 10;
    LinkedList* randomList = create_array(count);

    printf("Sluchaen List: ");
    printElements(randomList);

    free(&list);
    free(randomList);

    return 0;
}
