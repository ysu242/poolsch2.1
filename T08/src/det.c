#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double det(double **a, int n, int m);
void input(double **a, int *n, int *m);
void output(double d);

static void free_matrix(double **a, int n) {
    if (!a) return;
    for (int i = 0; i < n; ++i) free(a[i]);
    free(a);
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    // должна быть квадратной
    if (n != m) {
        printf("n/a");
        return 0;
    }

    // выделяем память
    double **a = (double **)malloc(n * sizeof(double *));
    if (!a) { printf("n/a"); return 0; }
    for (int i = 0; i < n; ++i) {
        a[i] = (double *)malloc(m * sizeof(double));
        if (!a[i]) { printf("n/a"); free_matrix(a, i); return 0; }
    }

    // читаем элементы матрицы
    input(a, &n, &m);                 // здесь *n и *m уже содержат размеры

    // проверка корректности ввода происходила в input; если ввода не хватило, там уже напечатан "n/a"
    // считаем определитель матрицы
    double d = det(a, n, m);
    output(d);

    free_matrix(a, n);
    return 0;
}

/*
 * input: предполагает, что *n и *m уже заполнены размерами.
 * Считывает ровно (*n * *m) вещественных чисел в матрицу a.
 * При ошибке ввода печатает "n/a" и завершает программу.
 */
void input(double **a, int *n, int *m) {
    for (int i = 0; i < *n; ++i) {
        for (int j = 0; j < *m; ++j) {
            if (scanf("%lf", &a[i][j]) != 1) {
                printf("n/a");
                exit(0);
            }
        }
    }
}

void output(double d) {
    printf("%.6f", d);
}

/*
 * det: вычисляет определитель квадратной матрицы n×n методом Гаусса
 * с частичным выбором главного элемента.
 */
double det(double **a, int n, int m) {
    (void)m; // m == n по проверке в main
    double det_sign = 1.0;
    double result = 1.0;

    // создаём копию, чтобы не портить исходную матрицу
    double **b = (double **)malloc(n * sizeof(double *));
    if (!b) return NAN;
    for (int i = 0; i < n; ++i) {
        b[i] = (double *)malloc(n * sizeof(double));
        if (!b[i]) { for (int k = 0; k < i; ++k) free(b[k]); free(b); return NAN; }
        for (int j = 0; j < n; ++j) b[i][j] = a[i][j];
    }

    for (int col = 0; col < n; ++col) {
        // ищем максимальный по модулю элемент в текущем столбце ниже/включая диагональ
        int pivot = col;
        double best = fabs(b[col][col]);
        for (int i = col + 1; i < n; ++i) {
            double v = fabs(b[i][col]);
            if (v > best) { best = v; pivot = i; }
        }

        // если опорный элемент ~ 0 — определитель 0
        if (best == 0.0) {
            result = 0.0;
            goto done;
        }

        // перестановка строк, если нужно
        if (pivot != col) {
            det_sign = -det_sign;
            for (int j = col; j < n; ++j) {
                double tmp = b[col][j];
                b[col][j] = b[pivot][j];
                b[pivot][j] = tmp;
            }
        }

        // исключение вниз
        double piv = b[col][col];
        for (int i = col + 1; i < n; ++i) {
            double factor = b[i][col] / piv;
            if (factor == 0.0) continue;
            b[i][col] = 0.0;
            for (int j = col + 1; j < n; ++j)
                b[i][j] -= factor * b[col][j];
        }
    }

    // произведение диагонали
    for (int i = 0; i < n; ++i) result *= b[i][i];
    result *= det_sign;

done:
    for (int i = 0; i < n; ++i) free(b[i]);
    free(b);
    return result;
}