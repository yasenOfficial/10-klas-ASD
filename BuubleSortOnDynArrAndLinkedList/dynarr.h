#ifndef DYNARR_H
#define DYNARR_H

typedef struct {
  int * buffer;
  unsigned int capacity;
  unsigned int size;
} DynamicArray;

DynamicArray init(unsigned int capacity);

int getElement(DynamicArray * arr, int index);
void setElement(DynamicArray * arr, int index, int value);

void pushBack(DynamicArray * arr, int value);
int popBack(DynamicArray * arr);

void pushToIndex(DynamicArray * arr, int index, int value);
void pushFront(DynamicArray * arr, int value);

void release(DynamicArray * arr);

#endif