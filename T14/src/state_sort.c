#include <stdio.h>

typedef struct {
    int year, month, day, hour, minute, second, status, code;
} Rec;

int read_rec(FILE* f, long idx, Rec* r) {
    if (fseek(f, idx * (long)sizeof(Rec), SEEK_SET) != 0) return 0;
    return fread(r, sizeof(Rec), 1, f) == 1;
}

int write_rec(FILE* f, long idx, const Rec* r) {
    if (fseek(f, idx * (long)sizeof(Rec), SEEK_SET) != 0) return 0;
    return fwrite(r, sizeof(Rec), 1, f) == 1;
}

int swap_rec(FILE* f, long i, long j) {
    if (i == j) return 1;
    Rec a, b;
    if (!read_rec(f, i, &a) || !read_rec(f, j, &b)) return 0;
    if (!write_rec(f, i, &b) || !write_rec(f, j, &a)) return 0;
    return 1;
}

int cmp_dt(const Rec* a, const Rec* b) {
    if (a->year != b->year) return (a->year < b->year) ? -1 : 1;
    if (a->month != b->month) return (a->month < b->month) ? -1 : 1;
    if (a->day != b->day) return (a->day < b->day) ? -1 : 1;
    if (a->hour != b->hour) return (a->hour < b->hour) ? -1 : 1;
    if (a->minute != b->minute) return (a->minute < b->minute) ? -1 : 1;
    if (a->second != b->second) return (a->second < b->second) ? -1 : 1;
    if (a->status != b->status) return (a->status < b->status) ? -1 : 1;
    if (a->code != b->code) return (a->code < b->code) ? -1 : 1;
    return 0;
}

long rec_count(FILE* f) {
    if (fseek(f, 0, SEEK_END) != 0) return -1;
    long bytes = ftell(f);
    if (bytes < 0) return -1;
    if (bytes % (long)sizeof(Rec) != 0) return -1;
    return bytes / (long)sizeof(Rec);
}

// selection-sort «на диске»: минимум на отрезке [i..n)
int sort_file(FILE* f, long n) {
    for (long i = 0; i < n; ++i) {
        long min_i = i;
        Rec minrec, cur;
        if (!read_rec(f, i, &minrec)) return 0;
        for (long j = i + 1; j < n; ++j) {
            if (!read_rec(f, j, &cur)) return 0;
            if (cmp_dt(&cur, &minrec) < 0) {
                minrec = cur;
                min_i = j;
            }
        }
        if (!swap_rec(f, i, min_i)) return 0;
    }
    return 1;
}

int print_file(FILE* f, long n) {
    Rec r;
    for (long i = 0; i < n; ++i) {
        if (!read_rec(f, i, &r)) return 0;
        printf("%d %d %d %d %d %d %d %d\n", r.year, r.month, r.day, r.hour, r.minute, r.second, r.status,
               r.code);
    }
    return 1;
}

int append_one(FILE* f, const Rec* r) {
    if (fseek(f, 0, SEEK_END) != 0) return 0;
    return fwrite(r, sizeof(Rec), 1, f) == 1;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }

    FILE* f = fopen(argv[1], "r+b");
    if (!f) f = fopen(argv[1], "w+b");
    if (!f) {
        printf("n/a");
        return 0;
    }

    int op;
    if (scanf("%d", &op) != 1) {
        printf("n/a");
        fclose(f);
        return 0;
    }

    long n = rec_count(f);
    if (n < 0) {
        printf("n/a");
        fclose(f);
        return 0;
    }

    if (op == 0) {
        if (n == 0)
            printf("n/a");
        else if (!print_file(f, n))
            printf("n/a");
    } else if (op == 1) {
        if (n == 0)
            printf("n/a");
        else {
            if (!sort_file(f, n) || !print_file(f, n)) printf("n/a");
        }
    } else if (op == 2) {
        Rec r;
        if (scanf("%d %d %d %d %d %d %d %d", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.second,
                  &r.status, &r.code) != 8) {
            printf("n/a");
        } else {
            if (!append_one(f, &r)) {
                printf("n/a");
                fclose(f);
                return 0;
            }
            n = rec_count(f);
            if (n <= 0 || !sort_file(f, n) || !print_file(f, n)) printf("n/a");
        }
    } else {
        printf("n/a");
    }

    fclose(f);
    return 0;
}