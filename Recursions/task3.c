#include <stdio.h>

int countDigits(int num) {
    if (num == 0) {
        return 0;
    } else {
        return 1 + countDigits(num / 10);
    }
}

int main() {
    int num = 234231; // Change num to the desired integer
    int count = countDigits(num);
    printf("%d", count);
    return 0;
}
