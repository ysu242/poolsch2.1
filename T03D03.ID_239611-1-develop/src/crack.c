#include <stdio.h>

int main() {
    double x, y;
    if (scanf("%lf%lf", &x, &y) != 2) {
        printf("n/a\n");
    } else {
        const double R = 5.0;
        const double R2 = R * R;
        if (x * x + y * y <= R2) {
            printf("GOTCHA\n");
        } else {
            printf("MISS\n");
        }
    }
    return 0;
}