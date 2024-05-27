#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 4
#define HASH_TABLE_SIZE 16 

typedef struct {
    char* key;
    int visited;
    int move_number; 
} item;


unsigned int hash(const char* key) {
    return (key[0] - 'A') * BOARD_SIZE + (key[1] - '1');
}

void init_items(item* items) {
    for (char row = 'A'; row < 'A' + BOARD_SIZE; row++) {
        for (char col = '1'; col < '1' + BOARD_SIZE; col++) {
            char* key = malloc(3 * sizeof(char));
            snprintf(key, 3, "%c%c", row, col);
            int index = hash(key);
            items[index].key = key;
            items[index].visited = 0;
            items[index].move_number = 0;
        }
    }
}

void clear_items(item* items) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        free(items[i].key);
    }
}

int is_valid_move(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

int find_path(item* items, int row, int col, int move_count) {
    char key[3];
    snprintf(key, 3, "%c%c", 'A' + row, '1' + col);
    int index = hash(key);

    if (items[index].visited)
        return 0; 

    items[index].visited = 1;  
    items[index].move_number = move_count + 1;  

    if (move_count == BOARD_SIZE * BOARD_SIZE - 1)
        return 1; 

    for (int i = 0; i < BOARD_SIZE; i++) {

        if (i != col && is_valid_move(row, i)) {
            if (find_path(items, row, i, move_count + 1))
                return 1;
        }

        if (i != row && is_valid_move(i, col)) {
            if (find_path(items, i, col, move_count + 1))
                return 1;
        }
    }


    items[index].visited = 0;
    items[index].move_number = 0;
    return 0;
}


void print_path(item* items) {
    int move_matrix[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        int row = items[i].key[0] - 'A';
        int col = items[i].key[1] - '1';
        move_matrix[row][col] = items[i].move_number;
    }
    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("%2d ", move_matrix[row][col]);
        }
        printf("\n");
    }
}

int main(void) {
    item items[HASH_TABLE_SIZE];
    init_items(items);

    if (find_path(items, 0, 0, 0)) {
        printf("Path found. Mv seuqeence is:\n");
        print_path(items);
    } else {
        printf("No pth existss.\n");
    }

    clear_items(items);
    return 0;
}
