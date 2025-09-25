#include "print_module.h"
#include <stdio.h>
#include <time.h>

char print_char(char ch) { // Изменено с int на char
  putchar(ch);
  return ch; // Возвращаем переданный символ
}

void print_log(char (*print)(char), char *message) {
  time_t now = time(NULL);
  struct tm *timeinfo = localtime(&now);
  char time_str[9];
  strftime(time_str, sizeof(time_str), "%H:%M:%S", timeinfo);

  // Вывод [LOG]
  for (char *p = Log_prefix; *p; p++)
    print(*p);
  print(' ');

  // Вывод времени
  for (char *p = time_str; *p; p++)
    print(*p);
  print(' ');

  // Вывод сообщения
  for (char *p = message; *p; p++)
    print(*p);
}