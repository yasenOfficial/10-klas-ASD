#ifndef MIN_SPAN_TREE_H
#define MIN_SPAN_TREE_H

#include "graph.h"

typedef struct{
    int value;
    struct node_t* left;
    struct node_t* right;
}node_t;

struct node_t* add(struct node_t* root, int value);

node_t* init_tree_node(graph_node_t* data);

node_t* min_span_tree(graph_t* graph, char* start_node_name);

#endif 
