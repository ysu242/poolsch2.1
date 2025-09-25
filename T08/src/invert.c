#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void free_matrix(double **a, int n) {
    if (!a) return;
    for (int i = 0; i < n; ++i) free(a[i]);
    free(a);
}

int input(double ***pmatrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0) return 1;
    int N = *n, M = *m;
    *pmatrix = NULL;

    double **a = (double **)malloc(N * sizeof(double *));
    if (!a) return 1;
    for (int i = 0; i < N; ++i) {
        a[i] = (double *)malloc(M * sizeof(double));
        if (!a[i]) { free_matrix(a, i); return 1; }
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            if (scanf("%lf", &a[i][j]) != 1) { free_matrix(a, N); return 1; }

    *pmatrix = a;
    return 0;
}

static int invert(double **a, int n, int m, double ***pout) {
    if (n != m) return 1;               // не квадратная
    int N = n;

    // создаём расширенную матрицу [A | I]
    double **aug = (double **)malloc(N * sizeof(double *));
    if (!aug) return 1;
    for (int i = 0; i < N; ++i) {
        aug[i] = (double *)malloc(2 * N * sizeof(double));
        if (!aug[i]) { free_matrix(aug, i); return 1; }
        for (int j = 0; j < N; ++j) aug[i][j] = a[i][j];
        for (int j = 0; j < N; ++j) aug[i][N + j] = (i == j) ? 1.0 : 0.0;
    }

    // Гаусс–Жордан с частичным выбором
    for (int col = 0; col < N; ++col) {
        // поиск строки с максимальным по модулю элементом в столбце col
        int pivot = col;
        double best = fabs(aug[col][col]);
        for (int r = col + 1; r < N; ++r) {
            double v = fabs(aug[r][col]);
            if (v > best) { best = v; pivot = r; }
        }
        if (best == 0.0) {              // сингулярная матрица
            free_matrix(aug, N);
            return 1;
        }
        // обмен строк
        if (pivot != col) {
            for (int j = 0; j < 2 * N; ++j) {
                double tmp = aug[col][j];
                aug[col][j] = aug[pivot][j];
                aug[pivot][j] = tmp;
            }
        }
        // нормируем ведущую строку
        double lead = aug[col][col];
        for (int j = 0; j < 2 * N; ++j) aug[col][j] /= lead;

        // зануляем остальные строки
        for (int r = 0; r < N; ++r) {
            if (r == col) continue;
            double factor = aug[r][col];
            if (factor == 0.0) continue;
            for (int j = 0; j < 2 * N; ++j)
                aug[r][j] -= factor * aug[col][j];
        }
    }

    // извлекаем правую половину как A^{-1}
    double **inv = (double **)malloc(N * sizeof(double *));
    if (!inv) { free_matrix(aug, N); return 1; }
    for (int i = 0; i < N; ++i) {
        inv[i] = (double *)malloc(N * sizeof(double));
        if (!inv[i]) { free_matrix(inv, i); free_matrix(aug, N); return 1; }
        for (int j = 0; j < N; ++j) inv[i][j] = aug[i][N + j];
    }

    free_matrix(aug, N);
    *pout = inv;
    return 0;
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) printf(" ");
            printf("%.6f", matrix[i][j]);
        }
        if (i != n - 1) printf("\n");   // без обязательного \n после последней строки
    }
}

int main(void) {
    double **A = NULL, **Ainv = NULL;
    int n = 0, m = 0;

    if (input(&A, &n, &m) != 0) { printf("n/a"); return 0; }
    if (invert(A, n, m, &Ainv) != 0) { free_matrix(A, n); printf("n/a"); return 0; }

    output(Ainv, n, m);

    free_matrix(Ainv, n);
    free_matrix(A, n);
    return 0;
}