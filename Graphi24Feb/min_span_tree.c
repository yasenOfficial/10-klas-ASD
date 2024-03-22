#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "min_span_tree.h"
#include "graph.h"

#define MAX_SIZE 100

// gcc queue.c -c
// gcc queue.c main.c -o main && ./main

struct node_t {
    int value;
    struct node_t* left;
    struct node_t* right;
};

struct node_t* add(struct node_t* root, int value) {
    if (root == NULL) {
        struct node_t* new_node = malloc(sizeof(struct node_t));
        new_node->value = value;
        new_node->left = new_node->right = NULL;

        return new_node;
    }

    if (root->value > value) {
        root->left = add(root->left, value);
    } else if (root->value < value) {
        root->right = add(root->right, value);
    } else {
        printf("New value matches existing value\n");
    }

    return root;
}

node_t* min_span_tree(graph_t* graph, char* start_node_name){
    if (*start_node_name == NULL) {
        return;
    }

    int visited[50];
    for (int i = 0; i < graph->nodes; i++) {
        visited[i] = 0;
    }

    int queue[50];
    int front = 0, rear = 0;
 
    visited[*start_node_name] = 1;
    queue[rear++] = start_node_name;
 
    while (front != rear) {
 
        *start_node_name = queue[front++];
        printf("%d ", *start_node_name);
 

       
    }

}
