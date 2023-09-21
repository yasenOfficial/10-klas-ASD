#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList init() {
    LinkedList list;
    list.size = 0;
    list.head = NULL;
    return list;
}

struct ListNode * get(LinkedList * list, int index) {
    if (index < 0 || index >= list->size || list->head == NULL) {
        return NULL; 
    }

    struct ListNode * current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

void pushFront(LinkedList * list, double value) {
    struct ListNode * newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (newNode == NULL) {
        printf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void pushToIndex(LinkedList *list, int index, double value) {
    if (index < 0 || index > list->size) {
        printf(stderr, "Invalid index\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        pushFront(list, value);
    } else {
        struct ListNode * newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (newNode == NULL) {
            printf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        struct ListNode * prevNode = get(list, index - 1);
        newNode->value = value;
        newNode->next = prevNode->next;
        prevNode->next = newNode;
        list->size++;
    }
}

void pushBack(LinkedList *list, double value) {
    pushToIndex(list, list->size, value);
}

double popFront(LinkedList * list) {
    if (list->size == 0 || list->head == NULL) {
        fprintf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }

    struct ListNode * oldHead = list->head;
    double value = oldHead->value;
    list->head = oldHead->next;
    free(oldHead);
    list->size--;
    return value;
}

double popAtIndex(LinkedList * list, int index) {
    if (index < 0 || index >= list->size || list->head == NULL) {
        fprintf(stderr, "Invalid index or empty list\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        return popFront(list);
    }

    struct ListNode * prevNode = get(list, index - 1);
    struct ListNode * currentNode = prevNode->next;
    double value = currentNode->value;
    prevNode->next = currentNode->next;
    free(currentNode);
    list->size--;
    return value;
}

double popBack(LinkedList * list) {
    if (list->size == 0 || list->head == NULL) {
        printf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }

    if (list->size == 1) {
        return popFront(list);
    }

    struct ListNode * prevNode = get(list, list->size - 2);
    struct ListNode * lastNode = prevNode->next;
    double value = lastNode->value;
    prevNode->next = NULL;
    free(lastNode);
    list->size--;
    return value;
}

void set(LinkedList *list, int index, double value) {
    struct ListNode * node = get(list, index);
    if (node != NULL) {
        node->value = value;
    } else {
        printf(stderr, "Invalid index or empty list\n");
        exit(EXIT_FAILURE);
    }
}

void foreach(LinkedList *list, Eacher eacher) {
    struct ListNode * current = list->head;
    int index = 0;
    while (current != NULL) {
        eacher(index, current->value);
        current = current->next;
        index++;
    }
}

void printElements(LinkedList *list) {
    struct ListNode *current = list->head;

    printf("Linked List Elements: ");
    
    while (current != NULL) {
        printf("%.2lf ", current->value);
        current = current->next;
    }
    
    printf("\n");
}