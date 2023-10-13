#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void printListReverse(struct Node* head) {
    if (head == NULL) {
        return;
    }
    printListReverse(head->next);
    printf("%d ", head->data);
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 112;
    head->next = second;
    second->data = 214;
    second->next = third;
    third->data = 353;
    third->next = NULL;

    printf("Obraten Red: ");
    printListReverse(head);
    return 0;
}
