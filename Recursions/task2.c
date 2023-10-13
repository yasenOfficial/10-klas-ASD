#include <stdio.h>

void reverseOrder(int n) {
    if (n == 0) {
        return;
    } else {
        printf("%d ", n);
        reverseOrder(n - 1);
    }
}

int main() {
    int n = 7; 
    reverseOrder(n);
    return 0;
}
