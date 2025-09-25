#include <stdio.h>
#include <math.h>

static int my_strlen(const char *s) {
    int n = 0;
    if (!s) return 0;
    while (s[n] != '\0') n++;
    return n;
}

static int my_streq_0_or_1(const char *s) {
    /* true если s == "0" или s == "1" */
    return (s && s[0] && !s[1] && (s[0] == '0' || s[0] == '1'));
}

static int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static int to_upper_hex(char c) {
    /* Только для a..f/A..F и цифр; остальное возвращаем как есть */
    if (c >= 'a' && c <= 'f') return c - 'a' + 'A';
    return c;
}

static int is_hex_digit(char c) {
    if (c >= '0' && c <= '9') return 1;
    c = (char)to_upper_hex(c);
    return (c >= 'A' && c <= 'F');
}

/* Итератор по токенам: читает следующее слово, разделённое пробелами/табами/переводами строк.
   Возвращает 1 если токен прочитан, 0 если токенов больше нет. */
static int next_token(char **p, char *out, int out_cap) {
    char *s = *p;
    int i = 0;

    if (!s || out_cap <= 0) return 0;

    /* Пропустить разделители */
    while (*s && is_space(*s)) s++;

    if (!*s) { *p = s; return 0; }

    /* Скопировать до следующего разделителя или конца строки */
    while (*s && !is_space(*s)) {
        if (i + 1 < out_cap) out[i++] = *s;  /* оставляем место под '\0' */
        s++;
    }
    out[i] = '\0';
    *p = s;
    return 1;
}

/* ======= логика задачи ======= */

static int is_hex_pair_str(const char *s) {
    return s && my_strlen(s) == 2 && is_hex_digit(s[0]) && is_hex_digit(s[1]);
}

static int hex2val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    c = (char)to_upper_hex(c);
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

static int decode_token(const char *hex, char *out_ch) {
    if (!is_hex_pair_str(hex)) return 0;
    {
        int hi = hex2val(hex[0]);
        int lo = hex2val(hex[1]);
        if (hi < 0 || lo < 0) return 0;
        *out_ch = (char)((hi << 4) | lo);
    }
    return 1;
}

static void encode_token(char ch, char out[3]) {
    static const char digits[] = "0123456789ABCDEF";
    unsigned char u = (unsigned char)ch;
    out[0] = digits[(u >> 4) & 0xF];
    out[1] = digits[u & 0xF];
    out[2] = '\0';
}

int main(int argc, char **argv) {
    int mode = -1; /* -1 → автодетект */

    if (argc == 2) {
        if (!my_streq_0_or_1(argv[1])) {
            printf("<n/a>");
            return 0;
        }
        mode = argv[1][0] - '0';
    }

    char line[4096];
    if (!fgets(line, sizeof(line), stdin)) { printf("<n/a>"); return 0; }

    /* Разбор первого токена вручную */
    char *p = line;
    char tok[4096];
    if (!next_token(&p, tok, (int)sizeof(tok))) { printf("<n/a>"); return 0; }

    /* Автоопределение режима при отсутствии аргумента */
    if (mode == -1) {
        int len = my_strlen(tok);
        if (len == 1) {
            mode = 0; /* символы → кодирование */
        } else if (len == 2 && is_hex_digit(tok[0]) && is_hex_digit(tok[1])) {
            mode = 1; /* HEX-пары → декодирование */
        } else {
            printf("<n/a>");
            return 0;
        }
    }

    int first = 1;

    if (mode == 0) {
        /* КОДИРОВАНИЕ: каждый токен — ровно 1 символ */
        do {
            if (my_strlen(tok) != 1) { printf("<n/a>"); return 0; }
            char buf[3];
            encode_token(tok[0], buf);
            if (!first) printf(" ");
            printf("%s", buf);
            first = 0;
        } while (next_token(&p, tok, (int)sizeof(tok)));
    } else {
        /* ДЕКОДИРОВАНИЕ: каждый токен — ровно 2 шестнадцатеричных знака */
        do {
            char ch;
            if (!decode_token(tok, &ch)) { printf("<n/a>"); return 0; }
            if (!first) printf(" ");
            printf("%c", ch);
            first = 0;
        } while (next_token(&p, tok, (int)sizeof(tok)));
    }

    return 0;
}