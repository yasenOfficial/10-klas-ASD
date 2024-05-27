#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define MAX_NODES 1000
#define INF DBL_MAX //1.7976931348623158e+308 (max flaot val representnato ot double (max double valu))

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
        perror("Faild to open file");
        exit(1);
    }

    int N, M;
    fscanf(file, "%d", &N);
    printf("Number of nodess: %d\n", N); 
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d %d %lf %lf", &graph.nodes[i].x, &graph.nodes[i].y, &graph.nodes[i].h, &graph.nodes[i].v);
        graph.edgeCounts[i] = 0; 
    }
    graph.nodeCount = N;

    fscanf(file, "%d", &M);
    printf("Nuum of edges: %d\n", M); 
    for (int i = 0; i < M; i++) {
        int src, dest;
        double c;
        fscanf(file, "%d %d %lf", &src, &dest, &c);

        double heightDiff = fabs(graph.nodes[src].h - graph.nodes[dest].h);
        double adjustedWeight = c;
        if (heightDiff != 0) {
            adjustedWeight += 1 - c / heightDiff;
        }

        addEdge(src, dest, adjustedWeight);
        addEdge(dest, src, adjustedWeight);
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

    double totalValue = graph.nodes[end].v; 
    int current = end;
    while (current != start) {
        int prev = previous[current];
        totalValue += graph.nodes[prev].v; 
        current = prev;
    }

    return totalValue;
}

void printShortestPath(int start, int end) {
    printf("Shortst Path from nde %d to node %d:\n", start, end);
    int path[MAX_NODES]; 
    int pathLength = 0;
    int totalEdges = 0;
    double totalWeights = 0.0;
    double totalValues = 0.0;
    
    int current = end;
    path[pathLength++] = current;

    while (current != start) {
        int prev = previous[current];
        totalEdges++; 
        Edge edge = graph.edges[prev][0]; 
        totalWeights += edge.weight; 
        totalValues += graph.nodes[prev].v; 
        path[pathLength++] = prev;
        current = prev;
    }

    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0)
            printf(" -> ");
    }

    printf("\n");

    printf("C, V, S: %d %.2f %.2f\n", totalEdges, totalWeights, totalValues);
}



int main() {
    loadGraph("terrain.txt");

    int start, end;
    while (1) {
        printf("inut num 1: ");
        int scanResult = scanf("%d", &start);
        if (scanResult == EOF) break; 
        if (scanResult != 1) {
            printf("Invalid input. Pls entr a num\n");
            while (getchar() != '\n'); 
            continue;
        }

        printf("input num 2: ");
        scanResult = scanf("%d", &end);
        if (scanResult == EOF) break; 
        if (scanResult != 1) {
            printf("Invalid input. Pls enter num.\n");
            while (getchar() != '\n'); 
            continue;
        }

        double totalValue = findPath(start, end);
        printf("Totall val: %f\n", totalValue);
        printShortestPath(start, end);
    }

    for (int i = 0; i < graph.nodeCount; i++) {
        free(graph.edges[i]);
    }

    return 0;
}

/*
terrain.txt, kojto az izpolzvah

5
0 0 1.0 5.0
1 1 2.0 6.0
2 2 3.0 7.0
3 3 2.5 8.0
4 4 1.5 9.0
6
0 1 1.5
1 2 2.0
2 3 2.5
3 4 3.0
0 3 5.0
1 4 4.5
*/