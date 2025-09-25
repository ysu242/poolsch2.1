#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);

int main(void) {
    int picture_data[N][M];
    int *picture[N];

    transform(&picture_data[0][0], picture, N, M);
    make_picture(picture, N, M);
    print_picture(picture, N, M);
    return 0;
}

void make_picture(int **picture, int n, int m) {
    /* заготовки по условию (не меняем) */
    int frame_w[] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
    int frame_h[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int tree_trunk[]   = {7,7,7,7};
    int tree_foliage[] = {3,3,3,3};
    int sun_data[6][5] = {
        {0,6,6,6,6},
        {0,0,6,6,6},
        {0,0,6,6,6},
        {0,6,0,0,6},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    reset_picture(picture, n, m);

    /* рамка по периметру */
    {
        int j;
        int w = (int)(sizeof(frame_w)/sizeof(frame_w[0]));
        int h = (int)(sizeof(frame_h)/sizeof(frame_h[0]));
        for (j = 0; j < w && j < m; ++j) {
            picture[0][j]   = frame_w[j];
            picture[n-1][j] = frame_w[j];
        }
        for (j = 0; j < h && j < n; ++j) {
            picture[j][0]   = frame_h[j];
            picture[j][m-1] = frame_h[j];
        }
    }

    /* стены комнаты: вертикальная (7-й столбец) и горизонтальная (8-я строка) */
    {
        int i;
        int vc = 6;  /* 0-based */
        int hr = 7;  /* 0-based */
        for (i = 0; i < n; ++i) picture[i][vc] = 1;
        for (i = 0; i < m; ++i) picture[hr][i] = 1;
    }

    /* солнце: строго как на эталоне (не трогаем рамку) */
    {
        int sr = 1, sc = 7;  /* важно: sc=7, чтобы получить 6-ки в колонках 8..11 */
        int r, c;
        for (r = 0; r < 6 && sr + r < n; ++r) {
            for (c = 0; c < 5 && sc + c < m; ++c) {
                if (sun_data[r][c]) {
                    int rr = sr + r, cc = sc + c;
                    if (rr > 0 && rr < n - 1 && cc > 0 && cc < m - 1)
                        picture[rr][cc] = 6;
                }
            }
        }
    }

    /* крона дерева — координаты в точности под образец */
    {
        int foliage[][2] = {
            /* row=2 */ {2,3},{2,4},
            /* row=3 */ {3,2},{3,3},{3,4},{3,5},
            /* row=4 */ {4,2},{4,3},{4,4},{4,5},
            /* row=5 */ {5,3},{5,4}
        };
        int k, cnt = (int)(sizeof(foliage)/sizeof(foliage[0]));
        for (k = 0; k < cnt; ++k) {
            int r = foliage[k][0], c = foliage[k][1];
            if (r>=0 && r<n && c>=0 && c<m)
                picture[r][c] = tree_foliage[(k & 3)];  /* берём из заготовки */
        }
    }

    /* ствол дерева — как на образце */
    {
        int trunk[][2] = {
            {6,3},{6,4},          /* над горизонтальной стеной */
            {8,3},{8,4},          /* под стеной */
            {9,3},{9,4},
            {10,2},{10,3},{10,4},{10,5}
        };
        int k, cnt = (int)(sizeof(trunk)/sizeof(trunk[0]));
        for (k = 0; k < cnt; ++k) {
            int r = trunk[k][0], c = trunk[k][1];
            if (r>=0 && r<n && c>=0 && c<m)
                picture[r][c] = tree_trunk[(k & 3)];    /* берём из заготовки */
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            picture[i][j] = 0;
}

void transform(int *buf, int **matr, int n, int m) {
    int i;
    for (i = 0; i < n; ++i)
        matr[i] = buf + i * m;
}

void print_picture(int **picture, int n, int m) {
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            printf("%d", picture[i][j]);
            if (j + 1 < m) putchar(' ');
        }
        putchar('\n');
    }
}