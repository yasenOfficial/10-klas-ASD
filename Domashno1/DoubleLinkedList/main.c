#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

int main() {
    LinkedList list = init();
    int choice;
    double value;

    while (1) {
        printf("Double Linked List Menu:\n");
        printf("1. Push to Stack\n");
        printf("2. Pop from Stack\n");
        printf("3. Push to Queue\n");
        printf("4. Pop from Queue\n");
        printf("5. Print Elements\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push to stack: ");
                scanf("%lf", &value);
                pushFront(&list, value);
                break;
            case 2:
                if (list.size > 0) {
                    value = popFront(&list);
                    printf("Popped value from stack: %.2lf\n", value);
                } else {
                    printf("Stack is empty.\n");
                }
                break;
            case 3:
                printf("Enter value to push to queue: ");
                scanf("%lf", &value);
                pushBack(&list, value);
                break;
            case 4:
                if (list.size > 0) {
                    value = popFront(&list);
                    printf("Popped value from queue: %.2lf\n", value);
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            case 5:
                printf("Elements in the list: ");
                printElements(&list);
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
