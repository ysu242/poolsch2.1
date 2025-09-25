#include <stdio.h>

typedef struct {
    int year, month, day, hour, minute, second, status, code;
} Rec;

int parse_date(const char* s, int* d, int* m, int* y) {
    int dd, mm, yy;
    if (sscanf(s, "%d.%d.%d", &dd, &mm, &yy) != 3) return 0;
    if (dd < 1 || dd > 31 || mm < 1 || mm > 12) return 0;
    *d = dd;
    *m = mm;
    *y = yy;
    return 1;
}

long rec_count(FILE* f) {
    if (fseek(f, 0, SEEK_END) != 0) return -1;
    long bytes = ftell(f);
    if (bytes < 0) return -1;
    if (bytes % (long)sizeof(Rec) != 0) return -1;
    return bytes / (long)sizeof(Rec);
}

int read_rec(FILE* f, long idx, Rec* r) {
    if (fseek(f, idx * (long)sizeof(Rec), SEEK_SET) != 0) return 0;
    return fread(r, sizeof(Rec), 1, f) == 1;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("n/a");
        return 0;
    }

    int d, m, y;
    if (!parse_date(argv[2], &d, &m, &y)) {
        printf("n/a");
        return 0;
    }

    FILE* f = fopen(argv[1], "rb");
    if (!f) {
        printf("n/a");
        return 0;
    }

    long n = rec_count(f);
    if (n <= 0) {
        printf("n/a");
        fclose(f);
        return 0;
    }

    Rec r;
    for (long i = 0; i < n; ++i) {
        if (!read_rec(f, i, &r)) {
            printf("n/a");
            fclose(f);
            return 0;
        }
        if (r.day == d && r.month == m && r.year == y) {
            printf("%d", r.code);
            fclose(f);
            return 0;
        }
    }

    printf("n/a");
    fclose(f);
    return 0;
}