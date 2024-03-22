#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h" 
#include "priority_queue.h"

struct djikstra_info_t {
    graph_node_t* node;
    int visited;
    int weight;
    graph_node_t* prev;
};

int compare_nodes(void* left, void* right) {
    struct djikstra_info_t* l = (struct djikstra_info_t*)left;
    struct djikstra_info_t* r = (struct djikstra_info_t*)right;

    if (l->weight == -1) return 1;
    if (r->weight == -1) return -1;

    return l->weight - r->weight;
}

struct djikstra_info_t* find_info_for_node(list_t* info, graph_node_t* node) {
    while (info != NULL) {
        struct djikstra_info_t* d_info = (struct djikstra_info_t*)info->value;
        if (d_info->node == node) return d_info;
        info = info->next;
    }
    return NULL;
}

void find_dijkstra_route(graph_t* graph, char* start, char* end) {
    list_t* info = NULL; 

    queue_t* nodes = priority_queue(compare_nodes);
    for (list_t* curr = graph->nodes; curr != NULL; curr = curr->next) {
        graph_node_t* graph_node = (graph_node_t*)curr->value;

        struct djikstra_info_t* d_node = malloc(sizeof(struct djikstra_info_t));
        d_node->node = graph_node;
        d_node->visited = 0;
        d_node->weight = (strcmp(start, graph_node->name) == 0) ? 0 : -1;
        d_node->prev = NULL;

        push_queue(nodes, d_node);
        info = push_list(info, d_node);
    }

    while (nodes->size > 0) {
        struct djikstra_info_t* smallest = (struct djikstra_info_t*)pop_queue(nodes);

        if (smallest->weight == -1) break; 

        smallest->visited = 1;

        for (list_t* edge_list = smallest->node->edges; edge_list != NULL; edge_list = edge_list->next) {
            graph_edge_t* edge = (graph_edge_t*)edge_list->value;
            graph_node_t* neighbour = (edge->l_node == smallest->node) ? edge->r_node : edge->l_node;

            struct djikstra_info_t* neighbour_info = find_info_for_node(info, neighbour);

            if (neighbour_info->visited) continue;

            int new_distance = smallest->weight + edge->weight;

            if (neighbour_info->weight == -1 || new_distance < neighbour_info->weight) {
                neighbour_info->weight = new_distance;
                neighbour_info->prev = smallest->node;

                push_queue(nodes, neighbour_info);
            }
            
        }
    }
}