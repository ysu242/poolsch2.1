#include <stdio.h>

unsigned long long fib(unsigned int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    long long n;
    if (scanf("%lld", &n) != 1 || n < 0) {
        printf("n/a");
        return 0;
    }
    printf("%llu", fib((unsigned int)n));
    return 0;
}