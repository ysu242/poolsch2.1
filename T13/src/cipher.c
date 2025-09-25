#include <stdio.h>
#include <string.h>

#define PATH_MAX_LEN 4096
#define LINE_MAX_LEN 8192

static void trim_nl(char *s) {
  if (!s)
    return;
  size_t n = strlen(s);
  if (n && s[n - 1] == '\n')
    s[n - 1] = '\0';
}

static int print_file(const char *path) {
  FILE *f = fopen(path, "r");
  if (!f) {
    printf("<n/a>\n");
    return 0;
  }

  int c, empty = 1;
  while ((c = fgetc(f)) != EOF) {
    putchar(c);
    empty = 0;
  }
  fclose(f);

  if (empty)
    printf("<n/a>");
  putchar('\n');
  return 1;
}

int main(void) {
  int cmd;
  char current_path[PATH_MAX_LEN] = {0};
  int file_loaded_ok = 0; // успешно ли выполнен пункт 1

  // чтобы корректно читать строки после scanf("%d")
  int ch;

  while (scanf("%d", &cmd) == 1) {
    // съедаем хвост строки после числа (до конца строки)
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (cmd == -1)
      break;

    if (cmd == 1) {
      // читаем путь (без пробелов)
      if (fgets(current_path, sizeof(current_path), stdin) == NULL) {
        printf("<n/a>\n");
        file_loaded_ok = 0;
        continue;
      }
      trim_nl(current_path);

      // показать содержимое и зафиксировать флаг только при успешном открытии
      FILE *f = fopen(current_path, "r");
      if (!f) {
        printf("<n/a>\n");
        file_loaded_ok = 0;
      } else {
        int c, empty = 1;
        while ((c = fgetc(f)) != EOF) {
          putchar(c);
          empty = 0;
        }
        fclose(f);
        if (empty) {
          printf("<n/a>");
          file_loaded_ok = 1;
        } else
          file_loaded_ok = 1;
        putchar('\n');
      }

    } else if (cmd == 2) {
      if (!file_loaded_ok) {
        printf("<n/a>\n"); // пункт 2 без успешного 1 — запрещён
        continue;
      }

      char line[LINE_MAX_LEN];
      if (!fgets(line, sizeof(line), stdin)) {
        printf("<n/a>\n");
        continue;
      }
      trim_nl(line);

      FILE *f = fopen(current_path, "a+");
      if (!f) {
        printf("<n/a>\n");
        continue;
      }

      // проверяем размер файла
      if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        printf("<n/a>\n");
        continue;
      }
      long size = ftell(f);

      if (size > 0) {
        fputc('\n',
              f); // вставляем перевод только если файл уже содержит данные
      }

      fputs(line, f);
      fclose(f);

      // вывести содержимое файла после дописывания
      print_file(current_path);

    } else {
      printf("<n/a>\n"); // неизвестный пункт меню
    }
  }
  return 0;
}