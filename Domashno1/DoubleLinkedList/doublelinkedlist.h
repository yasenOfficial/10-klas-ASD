#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct ListNode {
    double value;
    struct ListNode *next;
    struct ListNode *prev; // Add a previous pointer for doubly linked list
};

typedef struct {
    int size;
    struct ListNode *head;
    struct ListNode *tail; // Add a tail pointer for doubly linked list
} LinkedList;

LinkedList init();

struct ListNode *get(LinkedList *list, int index);

void pushFront(LinkedList *list, double value);
void pushToIndex(LinkedList *list, int index, double value);
void pushBack(LinkedList *list, double value);

double popFront(LinkedList *list);
double popAtIndex(LinkedList *list, int index);
double popBack(LinkedList *list);

void set(LinkedList *list, int index, double value);

void printElements(LinkedList *list);

typedef void (*Eacher)(int, double);
void foreach(LinkedList *list, Eacher eacher);

#endif
