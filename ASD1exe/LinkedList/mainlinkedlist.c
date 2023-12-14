#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void menu(LinkedList *list);

int main() {
    LinkedList list = init();

    menu(&list);

    return 0;
}

void menu(LinkedList *list) {
    int choice;
    double value;

    while (choice != 6) {
        printf("Linked List Menu:\n");
        printf("1. Push to Stack (Front)\n");
        printf("2. Pop from Stack\n");
        printf("3. Push to Queue (Back)\n");
        printf("4. Pop from Queue\n");
        printf("5. Print Elements\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push to stack: ");
                scanf("%lf", &value);
                pushFront(list, value);
                break;
            case 2:
                if (list->size > 0) {
                    value = popFront(list);
                    printf("Popped value from stack: %.2lf\n", value);
                } else {
                    printf("Stack is empty.\n");
                }
                break;
                
            case 3:
                printf("Enter value to push to queue: ");
                scanf("%lf", &value);
                pushBack(list, value);
                break;
               
            case 4:
                if (list->size > 0) {
                    value = popFront(list);
                    printf("Popped value from queue: %.2lf\n", value);
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            case 5:
                printElements(list);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
