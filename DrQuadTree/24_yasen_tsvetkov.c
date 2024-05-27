#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FIGURES 10

#define RESET_COLOR "\x1b[0m"
#define RED_COLOR "\x1b[31m"
#define GREEN_COLOR "\x1b[32m"
#define YELLOW_COLOR "\x1b[33m"
#define BLUE_COLOR "\x1b[34m"
#define MAGENTA_COLOR "\x1b[35m"
#define CYAN_COLOR "\x1b[36m"


typedef struct {
    float x, y;
} Point;

typedef struct {
    Point center;
    float sideLength;
    char* name;
} Square;

typedef struct {
    Point center;
    float radius;
    char* name;
} Circle;

typedef struct QuadTreeNode {
    float minX, maxX, minY, maxY;
    struct QuadTreeNode* children[4];
    void* figures[MAX_FIGURES];
    int numFigures;
} QuadTreeNode;

typedef struct FigureNode {
    void* figure;
    struct FigureNode* next;
} FigureNode;

typedef struct {
    FigureNode* head;
} FigureList;

Square* createSquare(float x, float y, float sideLength, char* name) {
    Square* square = (Square*)malloc(sizeof(Square));
    square->center.x = x;
    square->center.y = y;
    square->sideLength = sideLength;
    square->name = name;
    return square;
}

Circle* createCircle(float x, float y, float radius, char* name) {
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    circle->center.x = x;
    circle->center.y = y;
    circle->radius = radius;
    circle->name = name;
    return circle;
}

QuadTreeNode* createQuadTreeNode(float minX, float maxX, float minY, float maxY) {
    QuadTreeNode* node = (QuadTreeNode*)malloc(sizeof(QuadTreeNode));
    node->minX = minX;
    node->maxX = maxX;
    node->minY = minY;
    node->maxY = maxY;
    node->numFigures = 0;
    for (int i = 0; i < 4; i++) {
        node->children[i] = NULL;
    }
    return node;
}

//* 1,2 ^^^


void insertShape(QuadTreeNode* node, void* shape) {
    if (node->numFigures < MAX_FIGURES) { //* 3c
        node->figures[node->numFigures++] = shape;
    } else {

        //* 4 kvadranta, 3ci
        float midX = (node->minX + node->maxX) / 2;
        float midY = (node->minY + node->maxY) / 2;

        node->children[0] = createQuadTreeNode(node->minX, midX, node->minY, midY);
        node->children[1] = createQuadTreeNode(midX, node->maxX, node->minY, midY);
        node->children[2] = createQuadTreeNode(node->minX, midX, midY, node->maxY);
        node->children[3] = createQuadTreeNode(midX, node->maxX, midY, node->maxY);

        for (int i = 0; i < node->numFigures; i++) {
            //* 3cii
            float centerX, centerY;

            if (sizeof(*(Square*)shape) == sizeof(Square)) {
                Square* square = (Square*)node->figures[i];
                centerX = square->center.x;
                centerY = square->center.y;
            } else if (sizeof(*(Circle*)shape) == sizeof(Circle)){
                Circle* circle = (Circle*)node->figures[i];
                centerX = circle->center.x;
                centerY = circle->center.y;
            }

        
            int childIndex = 0;

            if (centerX > midX) {
                if (centerY > midY) {
                    childIndex = 3;
                } else {
                    childIndex = 1;
                }
            } else {
                if (centerY > midY) {
                    childIndex = 2;
                } else {
                    childIndex = 0;
                }
            }

            insertShape(node->children[childIndex], node->figures[i]); //* 3b
        }

        node->numFigures = 0;
    }
}

//* 4, build_tree izpozwa insertShape
QuadTreeNode* build_tree(FigureList* figures) {
    QuadTreeNode* root = createQuadTreeNode(-1000, 1000, -1000, 1000); //* 3a

    FigureNode* current = figures->head;
    while (current != NULL) {
        insertShape(root, current->figure);
        current = current->next;
    }

    return root;
}

void addFigureToList(FigureList* list, void* figure) {
    FigureNode* new_node = (FigureNode*)malloc(sizeof(FigureNode));
    new_node->figure = figure;
    new_node->next = list->head;
    list->head = new_node;
}

//* 5, doShapesOverlap
bool doShapesOverlap(void* shape1, void* shape2) {
    Square* square;
    Circle* circle;

    //* Check kakuv tip figura e
    
    if (sizeof(*(Square*)shape1) == sizeof(Square)) {
        square = (Square*)shape1; //* Castvame shape1 kum Square* tip
        circle = (Circle*)shape2; //* Castvame shape2 kum Circle* tip analogichno
    } else {
        square = (Square*)shape2; //* Castvame shape2 kum Square* tip
        circle = (Circle*)shape1; //* Castvame shape1 kum Circle* tip analogichno
    }

    //*Namirame min x coord value mezhdu centura na kruga i gorniq ugul na kvadrata
    float minX = fmin(circle->center.x, square->center.x + square->sideLength);
    //*Namirame min y coord value mezhdu centura na kruga i gorniq ugul na kvadrata
    float minY = fmin(circle->center.y, square->center.y + square->sideLength);

    ////printf("fmin X: %f\n", minX);
    ////printf("fmin Y: %f\n", minY);

    //*Namirame max x coord value mezhdu centura na kruga i dolniq ugul na kvadrata
    float closestX = fmax(square->center.x, minX);
    //*Namirame max y coord value mezhdu centura na kruga i dolniq ugul na kvadrata
    float closestY = fmax(square->center.y, minY);

    ////printf("fmax X: %f\n", closestX);
    ////printf("fmax Y: %f\n", closestY);

    //*Izchislqvame razstoqnieto m/u centruv na kruga i nai-blizkata tochka
    float distanceX = circle->center.x - closestX;
    float distanceY = circle->center.y - closestY;

    ////printf("distance X: %f\n", distanceX);
    ////printf("distance Y: %f\n", distanceY);

    return (distanceX * distanceX + distanceY * distanceY) < (circle->radius * circle->radius);
}

void findAndAddOverlappingPairs(QuadTreeNode* node, FigureList* overlaps) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->numFigures; i++) {
        for (int j = i + 1; j < node->numFigures; j++) {
            if (doShapesOverlap(node->figures[i], node->figures[j])) {
                addFigureToList(overlaps, node->figures[i]);
                addFigureToList(overlaps, node->figures[j]);
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        findAndAddOverlappingPairs(node->children[i], overlaps);
    }
}

FigureList* findOverlappingPairs(QuadTreeNode* root) {
    FigureList* overlaps = (FigureList*)malloc(sizeof(FigureList));
    overlaps->head = NULL;

    findAndAddOverlappingPairs(root, overlaps);

    return overlaps;
}

//* Funcii da prawqt zhivota lesen

void freeList(FigureList* list) {
    FigureNode* current = list->head;
    while (current != NULL) {
        FigureNode* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void visualizeTree(QuadTreeNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf(YELLOW_COLOR "Node: (%.2f, %.2f, %.2f, %.2f)\n" RESET_COLOR, node->minX, node->maxX, node->minY, node->maxY);

    for (int i = 0; i < node->numFigures; i++) {
        for (int j = 0; j < depth + 1; j++) {
            printf("\t");
        }
        printf(GREEN_COLOR "Figure: %s\n" RESET_COLOR, ((Square*)node->figures[i])->name);
    }

    for (int i = 0; i < 4; i++) {
        visualizeTree(node->children[i], depth + 1);
    }
}

void printFigures(FigureList* list) {
    FigureNode* current = list->head;
    while (current != NULL) {
        if (current->figure == NULL) {
            continue;
        }

        //* Check kakuv tip figura e
        if (sizeof(*(Square*)current->figure) == sizeof(Square)) {
            printf(RED_COLOR "Square: %s \n" RESET_COLOR, ((Square*)current->figure)->name);
        }
        else if (sizeof(*(Circle*)current->figure) == sizeof(Circle)) {
            printf(RED_COLOR "Circle: %s \n" RESET_COLOR, ((Circle*)current->figure)->name);
        }

        current = current->next;
    }
    printf("\n");
}

int main() {
    //* 6, main
    FigureList* figures = (FigureList*)malloc(sizeof(FigureList));
    figures->head = NULL;

    Square* square1 = createSquare(0, 0, 20, "Square1");
    Circle* circle1 = createCircle(5, 2, 15, "Circle1");

    addFigureToList(figures, square1);
    addFigureToList(figures, circle1);

    QuadTreeNode* root = build_tree(figures);

    FigureList* overlappingPairs = findOverlappingPairs(root);

    printf("Overlapping Pairs:\n");
    printFigures(overlappingPairs);

    visualizeTree(root, 0);

    free(square1);
    free(circle1);
    freeList(figures);
    freeList(overlappingPairs);
    free(root);

    return 0;
}
