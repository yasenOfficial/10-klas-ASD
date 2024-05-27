#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

#include "graph.h"
#include "list.h"

int node_degree(graph_node_t* node) {
    int degree = 0;
    list_t* curr = node->edges;
    while(curr != NULL && curr->value != NULL) {
        degree++;
        curr = curr->next;
    }
    return degree;
}

bool has_euler_loop(graph_t* graph) {
    if(graph->size == 0) return false; 

    list_t* curr_node = graph->nodes;
    while(curr_node != NULL && curr_node->value != NULL) {
        graph_node_t* node = (graph_node_t*)curr_node->value;
        if(node_degree(node) % 2 != 0) {
            return false;
        }
        curr_node = curr_node->next;
    }
    return true;
}



int main() {
    // list_t* list = init_list();
    // push_list(list, 1);
    // push_list(list, 2);

    // for(int i = 0; i < 3; i++) 
    //     printf("%d\n", list_get_at(list, i));

    // graph_node_t* node1 = init_graph_node("Pencho");
    // printf("%s\n", node1->name);

    // graph_t* graph = init_graph();

    // add_graph_node(graph, "Pencho");
    // add_graph_node(graph, "Gencho");
    // add_graph_node(graph, "Penka");

    // connect_nodes(
    //     find_node_by_name(graph, "Pencho"),
    //     find_node_by_name(graph, "Gencho")
    // );
    // connect_nodes(
    //     find_node_by_name(graph, "Gencho"),
    //     find_node_by_name(graph, "Penka")
    // );
    // connect_nodes(
    //     find_node_by_name(graph, "Pencho"),
    //     find_node_by_name(graph, "Penka")
    // );

    // print_graph(graph);

    // char* input_data[] = {
    //     "3",
    //     "Pencho Gencho Penka",
    //     "0 1 1",
    //     "1 0 1",
    //     "1 1 0"
    // };

    // graph_t* graph = init_graph_from_strings(input_data);
    graph_t* graph = init_graph();

    add_graph_node(graph, "1");
    add_graph_node(graph, "2");
    add_graph_node(graph, "3");
    add_graph_node(graph, "4");
    add_graph_node(graph, "5");

    connect_nodes(
        find_node_by_name(graph, "1"),
        find_node_by_name(graph, "2")
    );
    connect_nodes(
        find_node_by_name(graph, "1"),
        find_node_by_name(graph, "3")
    );
    connect_nodes(
        find_node_by_name(graph, "2"),
        find_node_by_name(graph, "4")
    );
    connect_nodes(
        find_node_by_name(graph, "2"),
        find_node_by_name(graph, "5")
    );
    connect_nodes(
        find_node_by_name(graph, "3"),
        find_node_by_name(graph, "5")
    );

    print_graph(graph);

    // graph_span_tree(graph, "1"); 

    printf("Euler Loop: %B", has_euler_loop(graph));

    return 0;
}