#include <stdio.h>
#include "dynarr.h"

int main() {
    int choice, value;
    DynamicArray arr;
    arr = init(5);

    while (1) {
        printf("\nLinked List Menu:\n");
        printf("1. Push to Stack\n");
        printf("2. Pop from Stack\n");
        printf("----------------------\n");
        printf("3. Enqueue to Queue\n");
        printf("4. Dequeue from Queue\n");
        printf("----------------------\n");
        printf("5. Print Elements\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // Case 1 and 2 are for the stack
            // Case 3 and 4 are for the queue
            // Case 5 is for printing the elements
            // Case 6 is for exiting the program

            case 1:
                printf("Enter a value to push to the stack: ");
                scanf("%d", &value);
                pushBack(&arr, value);
                break;
            case 2:
                if (arr.size > 0) {
                    printf("Popped element from the stack: %d\n", popBack(&arr));
                } else {
                    printf("Stack is empty.\n");
                }
                break;
            case 3:
                printf("Enter a value to enqueue to the queue: ");
                scanf("%d", &value);
                pushBack(&arr, value);
                break;
            case 4:
                if (arr.size > 0) {
                    // shift al the elemnts in the dynarr one position to the left to "remove" the front element.
                    printf("Dequeued element from the queue: %d\n", getElement(&arr, 0));
                    for (int i = 0; i < arr.size - 1; i++) {
                        arr.buffer[i] = arr.buffer[i + 1];
                    }
                    arr.size--;
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            case 5:
                printf("Elements in the array:\n");
                for (int i = 0; i < arr.size; i++) {
                    printf("%d ", getElement(&arr, i));
                }
                printf("\n");
                break;
            case 6:
                release(&arr);
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
