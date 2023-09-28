#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main() {
    vector_t* myVector = init_vector(10); // Initialize with an initial capacity of 10

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push element\n");
        printf("2. Get element at index\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                int value;
                scanf("%d", &value);
                push_vector(myVector, value);
                printf("Element %d pushed into the vector.\n", value);
                break;
            case 2:
                printf("Enter the index: ");
                unsigned int index;
                scanf("%u", &index);
                int element = vector_get_at(myVector, index);
                if (element == -1) {
                    printf("Invalid index.\n");
                } else {
                    printf("Element at index %u: %d\n", index, element);
                }
                break;
            case 3:
                free_vector(myVector); // Free the vector when done
                printf("Vector freed. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
