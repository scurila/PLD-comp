#include "stdio.h"
int fibo(int n) {
    if (n <= 1) {
        return n;
    }
    return fibo(n-1) + fibo(n-2);
}

int main() {
    int i = 1;
    while (i < 7) {
        putchar(48+fibo(i));
        putchar(13);
        putchar(10);
        i = i + 1;
    }
    return 0;
}
