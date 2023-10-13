#include <stdio.h>

int sumOfFirstNIntegers(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n + sumOfFirstNIntegers(n - 1);
    }
}

int main() {
    int n = 21; 
    int result = sumOfFirstNIntegers(n);
    printf("%d", result);
    return 0;
}
