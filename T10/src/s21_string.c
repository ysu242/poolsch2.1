#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;

  // Проверяем, что указатель не NULL
  if (str == s21_NULL) {
    return 0;
  }

  // Подсчитываем символы до нулевого терминатора
  while (str[length] != '\0') {
    length++;
  }

  return length;
}