#include <stdio.h>

#define NMAX 10

int input(int *a, int *n, int *c);
void output(const int *a, int n);
void shift_left(int *a, int n, int k);
void leftRotateByOne(int *a, int n);

int main(void) {
    int n, c, data[NMAX];
    if (input(data, &n, &c) != 0) {
        printf("n/a");
        return 0;
    }

    if (n <= 0 || n > NMAX) { // страховка
        printf("n/a");
        return 0;
    }

    // нормализуем величину сдвига: 0..n-1 (отрицательные -> сдвиг вправо)
    int k = ((c % n) + n) % n;   // всегда 0..n-1
    if (k != 0) shift_left(data, n, k);

    output(data, n);
    return 0;
}

int input(int *a, int *n, int *c) {
    char ch;
    if (scanf("%d%c", n, &ch) != 2 || ch != '\n') return 1;
    if (*n <= 0 || *n > NMAX) return 1;

    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    if (scanf("%d", c) != 1) return 1;
    return 0;
}

void shift_left(int *a, int n, int k) {
    // k раз циклически сдвигаем влево
    for (int i = 0; i < k; i++) leftRotateByOne(a, n);
}

void leftRotateByOne(int *a, int n) {
    int tmp = a[0];
    for (int i = 0; i < n - 1; i++) a[i] = a[i + 1];
    a[n - 1] = tmp;
}

void output(const int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", a[i]);
    }
}