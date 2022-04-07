

int sum(int a, int b) {
    return a + b;
}

int square(int a) {
    return a * a;
}

void print_msg() {
    int cpt = 0;
    while(cpt < 10) {
        putchar('a' + cpt);
        cpt++;
    }
    putchar(10);
    putchar(13);
}

int main() {

    int a, b;
    a = 2;
    b = 3;

    int c = 10, d = a + b;

    print_msg();

    return square(sum(c, d)); 
}