#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void print_tree(struct node_t* root) {
    if (root == NULL) return;

    print_tree(root->left);

    printf("%d\n", root->value);

    print_tree(root->right);
}

int height(struct node_t* root) {
    if (root == NULL) return 0;

    int left_height = height(root->left);
    int right_height = height(root->right);

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

void print_row(struct node_t* root, int level) {
    if (root == NULL) return;

    if (level == 1) {
        printf("%d\n", root->value);
    } else if (level > 1) {
        print_row(root->left, level - 1);
        print_row(root->right, level - 1);
    }
}

void print_reverse_order(struct node_t* root) {
    int h = height(root);

    for (int i = h; i >= 1; i--){
        print_row(root, i);
    }
}

int is_balanced(struct node_t* root) {
    if (root == NULL) {
        return 1; 
    }

    int left_height = height(root->left);
    int right_height = height(root->right);

    if(abs(left_height - right_height) < 2){
        if (is_balanced(root->left) && is_balanced(root->right)) {
            return 1;
        }

    }

    return 0;
}

int count_elements(struct node_t* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + count_elements(root->left) + count_elements(root->right);
    }
}

int sum_powers_of_2(int n) {
    int sum = 0;
    
    for (int i = 0; i <= n; i++) {
        sum += pow(2, i);
    }

    return sum;
}

int minimal_height(struct node_t* root) {
    if (root == NULL) return 0;

    int num_elements = count_elements(root);
    // printf("num_elements: %d\n", num_elements);
    int height;

    for (int i = 0; num_elements > sum_powers_of_2(i); i++) {
        // printf("sum_powers_of_2(%d): %d\n", i, sum_powers_of_2(i));
        height = i+1;
    }

    return height+1;
    // Make more optimal at home
}

int balance(struct node_t* root) {
    if (root == NULL) return 0;

    // balance(root->left); AT HOME
}

void visualizeTree(struct node_t *root, int level)
{
        if (root == NULL)
                return;
        for (int i = 0; i < level; i++)
                printf(i == level - 1 ? "|->" : "   ");
        printf("%d\n", root->value);
        visualizeTree(root->left, level + 1);
        visualizeTree(root->right, level + 1);
}



int main() {
    struct node_t* root = add(NULL, 4);
    add(root, 2);
    add(root, 6);
    add(root, 1);
    add(root, 3);
    add(root, 5);
    add(root, 7);

    visualizeTree(root, 0);

    return 0;
}
