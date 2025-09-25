#include <stdio.h>

static long long llabs_ll(long long x){ return x < 0 ? -x : x; }

// "деление" |n| на |d| вычитаниями: возвращает частное и остаток
static void divmod_abs(long long n, long long d, long long *q, long long *r){
    n = llabs_ll(n); d = llabs_ll(d);
    long long qq = 0;
    while (n >= d) { n -= d; ++qq; }
    *q = qq; *r = n;
}

// Наибольший простой делитель |a|; для 0 и 1 — ошибка
static long long largest_prime_divisor(long long a){
    a = llabs_ll(a);
    if (a <= 1) return -1;

    long long ans = -1;
    for (long long d = 2; d * d <= a; ++d) {
        long long q, r;
        divmod_abs(a, d, &q, &r);
        if (r == 0) {                 // d делит a
            ans = d;                  // кандидат на максимум
            a = q;                    // убираем множитель d
            // убрать все степени d
            while (1) {
                divmod_abs(a, d, &q, &r);
                if (r != 0) break;
                a = q;
            }
        }
    }
    if (a > 1) ans = a;               // остался простой множитель > sqrt(исходного)
    return ans;
}

int main(void){
    long long a;
    if (scanf("%lld", &a) != 1) { printf("<n/a>"); return 0; }
    long long res = largest_prime_divisor(a);
    if (res == -1) printf("<n/a>");
    else           printf("%lld", res);
    return 0;
}