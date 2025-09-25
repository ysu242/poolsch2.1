#include <stdio.h>
#include <stdlib.h>

static int **alloc_matrix(int n, int m) {
    int **a = (int **)malloc(n * sizeof(int *));
    if (!a) return NULL;
    int *block = (int *)malloc(n * m * sizeof(int));
    if (!block) { free(a); return NULL; }
    for (int i = 0; i < n; i++) a[i] = block + i * m;
    return a;
}

static void free_matrix(int **a) {
    if (!a) return;
    free(a[0]);  // сплошной блок
    free(a);
}

static void bubbleSort(int *v, int sz) {
    for (int i = 0; i < sz - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < sz - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int t = v[j]; v[j] = v[j + 1]; v[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    // 1) сплющим, 2) отсортируем, 3) разложим "по столбцам-змейкой"
    int total = n * m;
    int *buf = (int *)malloc(total * sizeof(int));
    if (!buf) { printf("n/a"); return; }

    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            buf[k++] = matrix[i][j];

    bubbleSort(buf, total);

    k = 0;
    for (int j = 0; j < m; j++) {
        if ((j & 1) == 0) {
            for (int i = 0; i < n; i++) result_matrix[i][j] = buf[k++];
        } else {
            for (int i = n - 1; i >= 0; i--) result_matrix[i][j] = buf[k++];
        }
    }

    free(buf);
}

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    int total = n * m;
    int *buf = (int *)malloc(total * sizeof(int));
    if (!buf) { printf("n/a"); return; }

    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            buf[k++] = matrix[i][j];

    bubbleSort(buf, total);

    k = 0;
    for (int i = 0; i < n; i++) {
        if ((i & 1) == 0) {
            for (int j = 0; j < m; j++) result_matrix[i][j] = buf[k++];
        } else {
            for (int j = m - 1; j >= 0; j--) result_matrix[i][j] = buf[k++];
        }
    }

    free(buf);
}

/* возвращаем код ошибки, чтобы main мог корректно печатать "n/a" и завершаться */
int input(int ***matrix, int *n, int *m) {
    if (scanf("%d%d", n, m) != 2 || *n <= 0 || *m <= 0) {
        return 1;
    }
    int **a = alloc_matrix(*n, *m);
    if (!a) return 1;

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &a[i][j]) != 1) {
                free_matrix(a);
                return 1;
            }
        }
    }
    *matrix = a;
    return 0;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j) printf(" ");
            printf("%d", matrix[i][j]);
        }
        if (i != n - 1) printf("\n");
    }
}

/* main */

int main(void) {
    int **matrix = NULL, **result = NULL;
    int n = 0, m = 0;

    if (input(&matrix, &n, &m)) {  // читаем n, m и саму матрицу
        printf("n/a");
        return 0;
    }

    result = alloc_matrix(n, m);
    if (!result) {
        printf("n/a");
        free_matrix(matrix);
        return 0;
    }

    // 1) Вертикальная змейка
    sort_vertical(matrix, n, m, result);
    output(result, n, m);
    printf("\n");

    // 2) Горизонтальная змейка
    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    free_matrix(result);
    free_matrix(matrix);
    return 0;
}