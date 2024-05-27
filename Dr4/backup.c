#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define MAX_NODES 1000
#define INF DBL_MAX

typedef struct {
    int x, y; 
    double h; 
    double v; 
} Node;

typedef struct {
    double weight;
    int dest; 
} Edge;

typedef struct {
    Node nodes[MAX_NODES];
    Edge* edges[MAX_NODES]; 
    int edgeCounts[MAX_NODES];
    int nodeCount;
} Graph;

Graph graph;
int visited[MAX_NODES];
double distance[MAX_NODES];
int previous[MAX_NODES];

void addEdge(int src, int dest, double weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->dest = dest;
    edge->weight = weight;
    graph.edges[src] = (Edge*)realloc(graph.edges[src], (graph.edgeCounts[src] + 1) * sizeof(Edge));
    graph.edges[src][graph.edgeCounts[src]++] = *edge;
}

void loadGraph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    int N, M;
    fscanf(file, "%d", &N);
    printf("Number of nodes: %d\n", N); // Print number of nodes for verification
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d %d %lf %lf", &graph.nodes[i].x, &graph.nodes[i].y, &graph.nodes[i].h, &graph.nodes[i].v);
        graph.edgeCounts[i] = 0; // Initialize edge count for each node
    }
    graph.nodeCount = N;

    fscanf(file, "%d", &M);
    printf("Number of edges: %d\n", M); // Print number of edges for verification
    for (int i = 0; i < M; i++) {
        int src, dest;
        double c;
        fscanf(file, "%d %d %lf", &src, &dest, &c);

        // Adjust the weight considering height difference
        double heightDiff = fabs(graph.nodes[src].h - graph.nodes[dest].h);
        double adjustedWeight = c;
        if (heightDiff != 0) {
            adjustedWeight += 1 - c / heightDiff;
        }

        addEdge(src, dest, adjustedWeight);
        addEdge(dest, src, adjustedWeight); // Assuming undirected graph
    }

    fclose(file);
}

double findPath(int start, int end) {
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < graph.nodeCount; i++) {
        distance[i] = INF;
    }
    distance[start] = 0; 

    for (int count = 0; count < graph.nodeCount - 1; count++) {
        int u = -1;
        for (int v = 0; v < graph.nodeCount; v++) {
            if (!visited[v] && (u == -1 || distance[v] < distance[u])) {
                u = v;
            }
        }
        if (u == -1 || distance[u] == INF) break; 

        visited[u] = 1; 

        for (int v = 0; v < graph.edgeCounts[u]; v++) {
            Edge edge = graph.edges[u][v];
            double newDistance = distance[u] + edge.weight;
            if (!visited[edge.dest] && newDistance < distance[edge.dest]) {
                distance[edge.dest] = newDistance;
                previous[edge.dest] = u;
            }
        }
    }

    double totalValue = 0;
    for (int i = 0; i < graph.nodeCount; i++) {
        totalValue += graph.nodes[i].v;
    }

    return totalValue;
}


int main() {
    loadGraph("terrain.txt");

    int start, end;
    while (1) {
        printf("input num 1: ");
        int scanResult = scanf("%d", &start);
        if (scanResult == EOF) break; 
        if (scanResult != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("input num 2: ");
        scanResult = scanf("%d", &end);
        if (scanResult == EOF) break; 
        if (scanResult != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        double totalValue = findPath(start, end);
        printf("Total value: %f\n", totalValue);

    }

    for (int i = 0; i < graph.nodeCount; i++) {
        free(graph.edges[i]);
    }

    return 0;
}
