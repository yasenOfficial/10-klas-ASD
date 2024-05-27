#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int workers;
    int tanks;
    struct Edge *edges;
    struct Node *next;
} Node;

typedef struct Edge {
    int crystals;
    int gas;
    struct Node *node;
    struct Edge *next;
} Edge;

Node *createNode(int W, int T) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->workers = W;
    newNode->tanks = T;
    newNode->edges = NULL;
    newNode->next = NULL;
    return newNode;
}

Edge *createEdge(int C, int G, Node *node) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->crystals = C;
    newEdge->gas = G;
    newEdge->node = node;
    newEdge->next = NULL;
    return newEdge;
}

void addEdge(Node *node, Edge *edge) {
    if (node->edges == NULL) {
        node->edges = edge;
    } else {
        Edge *temp = node->edges;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = edge;
    }
}

void generateGraph(Node *start) {
    Node *queue = start;

    while (queue != NULL) {
        Node *node = queue;
        queue = queue->next;

        for (int i = 0; i <= node->workers; i++) {
            for (int j = 0; j <= node->workers - i; j++) {

                int cryst = 50 * i;
                int gas = 25 * j; 

                int newWorkers = cryst / 100;
                int remainingCrystals = cryst % 100;
                int newTanks = (remainingCrystals >= 250 && gas >= 75) ? 1 : 0;

                if (newWorkers > 0 || newTanks > 0) {
                    Node *newNode = createNode(node->workers + newWorkers, node->tanks + newTanks);
                    Edge *newEdge = createEdge(-100 * newWorkers - 250 * newTanks, -75 * newTanks, newNode);
                    addEdge(node, newEdge);

                    if (queue == NULL) {
                        queue = newNode;
                    } else {
                        Node *temp = queue;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newNode;
                    }
                }
            }
        }
    }
}


void findOptimalPath(Node *start) {
    Node *queue = start;
    int visited[1000] = {0};
    Node *path[1000];
    int steps = 0;

    while (queue != NULL) {
        Node *node = queue;
        queue = queue->next;

        if (node->tanks >= 10) {
            printf("Optiml Path\n");
            for (int i = 0; i < steps; i++) {
                printf("workers: %d, tanks: %d\n", path[i]->workers, path[i]->tanks);
            }
            return;
        }

        if (!visited[node->workers * 100 + node->tanks]) {
            visited[node->tanks * 100 + node->tanks] = 1;
            path[steps++] = node;

            Edge *edge = node->edges;
            int choice = 0;
            int count = 1;

            printf("Avalaable optoins:\n");
            while (edge != NULL) {
                printf("%d. Buy %d workrs and %d tanks\n", count, edge->node->workers - node->workers, edge->node->tanks - node->tanks);
                count++;
                edge = edge->next;
            }

            printf("Enter your choicee: ");
            scanf("%d", &choice);

            count = 1;
            edge = node->edges;
            while (edge != NULL && count < choice) {
                count++;
                edge = edge->next;
            }

            if (edge != NULL) {
                Node *temp = queue;
                while (temp != NULL && temp->next != NULL) {
                    temp = temp->next;
                }
                if (temp == NULL) {
                    queue = edge->node;
                } else {
                    temp->next = edge->node;
                }
            }
        }
    }

    printf("No path xD.\n");
}


void demoGraph(Node *start) {
    int choice;
    do {
        printf("=== DEMO GRPH MENU ===\n");
        printf("Current resources: Workers = %d, Tanks = %d\n", start->workers, start->tanks); // Display current resources
        printf("1. Generate Graph\n");
        printf("2. Find Optimal Path\n");    
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateGraph(start);
                printf("Graph genearted\n");
                break;
            case 2:
                findOptimalPath(start);
                break;
            case 3:
                printf("Exit.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 3);
}


int main() {
    Node *start = createNode(1, 0); // 1 worker i 0 tanka
    
    demoGraph(start);

}
