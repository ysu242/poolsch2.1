#include <math.h>
#include <stdio.h>

int main() {
    double x;
    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
    } else {
        double y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3.0) - 1e3) * x + 3) / (x * x / 2.0) -
                  x * pow((10.0 + x), (2.0 / x)) - 1.01;
        printf("%.1f\n", y);
    }
    return 0;
}