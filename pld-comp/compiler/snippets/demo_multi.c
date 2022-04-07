#include "stdio.h"

void test() {
    int a = 5;

    return;
}

int sum(int a, int b) {
    return a + b;
}

int whois(int a) {
    return a;
}

int returnfour() {
    return 4;
}

int main()
{
    int a = 5;
    int b = 2;
    int c;

    int z = 3;
    int y;
    
    {
        int z;
        a = 4;
        z = 2;
        int y = 2;

        c = a - b + z;
    }

    z = returnfour();

    z = z + hello(1);

    return z;  
}
