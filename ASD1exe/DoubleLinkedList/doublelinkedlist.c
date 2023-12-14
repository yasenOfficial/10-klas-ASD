#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

// Helper function to create a new ListNode
struct ListNode *createNode(double value) {
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (node) {
        node->value = value;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

LinkedList init() {
    LinkedList list;
    list.size = 0;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

struct ListNode *get(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL; // Index out of bounds
    }

    struct ListNode *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

void pushFront(LinkedList *list, double value) {
    struct ListNode *node = createNode(value);
    if (node) {
        node->next = list->head;
        if (list->head) {
            list->head->prev = node;
        } else {
            // If the list was empty, update the tail pointer
            list->tail = node;
        }
        list->head = node;
        list->size++;
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
}

void pushToIndex(LinkedList *list, int index, double value) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }

    if (index == 0) {
        pushFront(list, value);
        return;
    }

    if (index == list->size) {
        pushBack(list, value);
        return;
    }

    struct ListNode *current = get(list, index - 1);
    if (current) {
        struct ListNode *node = createNode(value);
        if (node) {
            node->next = current->next;
            node->prev = current;
            current->next = node;
            node->next->prev = node;
            list->size++;
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    } else {
        fprintf(stderr, "Invalid index\n");
    }
}

void pushBack(LinkedList *list, double value) {
    struct ListNode *node = createNode(value);
    if (node) {
        if (list->tail) {
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        } else {
            // If the list was empty, update both head and tail pointers
            list->head = node;
            list->tail = node;
        }
        list->size++;
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
}

double popFront(LinkedList *list) {
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return 0.0; // Return a default value (you can change this behavior)
    }

    struct ListNode *nodeToRemove = list->head;
    double value = nodeToRemove->value;

    list->head = nodeToRemove->next;
    if (list->head) {
        list->head->prev = NULL;
    } else {
        // If the list became empty, update the tail pointer as well
        list->tail = NULL;
    }

    free(nodeToRemove);
    list->size--;

    return value;
}

double popAtIndex(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Invalid index\n");
        return 0.0; // Return a default value (you can change this behavior)
    }

    if (index == 0) {
        return popFront(list);
    }

    if (index == list->size - 1) {
        return popBack(list);
    }

    struct ListNode *nodeToRemove = get(list, index);
    double value = nodeToRemove->value;

    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;

    free(nodeToRemove);
    list->size--;

    return value;
}

double popBack(LinkedList *list) {
    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
        return 0.0; // Return a default value (you can change this behavior)
    }

    struct ListNode *nodeToRemove = list->tail;
    double value = nodeToRemove->value;

    list->tail = nodeToRemove->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        // If the list became empty, update the head pointer as well
        list->head = NULL;
    }

    free(nodeToRemove);
    list->size--;

    return value;
}

void set(LinkedList *list, int index, double value) {
    struct ListNode *node = get(list, index);
    if (node) {
        node->value = value;
    } else {
        fprintf(stderr, "Invalid index\n");
    }
}

void printElements(LinkedList *list) {
    struct ListNode *current = list->head;
    while (current) {
        printf("%.2lf ", current->value);
        current = current->next;
    }
    printf("\n");
}

void foreach(LinkedList *list, Eacher eacher) {
    struct ListNode *current = list->head;
    int index = 0;
    while (current) {
        eacher(index, current->value);
        current = current->next;
        index++;
    }
}
