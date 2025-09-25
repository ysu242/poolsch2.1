#include "s21_string.h"
#include <stdio.h>

void s21_strlen_test() {
  printf("=== Testing s21_strlen ===\n\n");

  // Тест 1: Нормальная строка
  const char *test1 = "Hello";
  s21_size_t result1 = s21_strlen(test1);
  s21_size_t expected1 = 5;
  printf("Test 1 - Normal string:\n");
  printf("Input: \"%s\"\n", test1);
  printf("Output: %lu\n", result1);
  printf("Expected: %lu\n", expected1);
  printf("Result: %s\n\n", (result1 == expected1) ? "SUCCESS" : "FAIL");

  // Тест 2: Пустая строка
  const char *test2 = "";
  s21_size_t result2 = s21_strlen(test2);
  s21_size_t expected2 = 0;
  printf("Test 2 - Empty string:\n");
  printf("Input: \"%s\"\n", test2);
  printf("Output: %lu\n", result2);
  printf("Expected: %lu\n", expected2);
  printf("Result: %s\n\n", (result2 == expected2) ? "SUCCESS" : "FAIL");

  // Тест 3: Длинная строка
  const char *test3 = "This is a very long string for testing purposes";
  s21_size_t result3 = s21_strlen(test3);
  s21_size_t expected3 = 47;
  printf("Test 3 - Long string:\n");
  printf("Input: \"%s\"\n", test3);
  printf("Output: %lu\n", result3);
  printf("Expected: %lu\n", expected3);
  printf("Result: %s\n\n", (result3 == expected3) ? "SUCCESS" : "FAIL");

  // Тест 4: Строка с пробелами
  const char *test4 = "   ";
  s21_size_t result4 = s21_strlen(test4);
  s21_size_t expected4 = 3;
  printf("Test 4 - Spaces only:\n");
  printf("Input: \"%s\"\n", test4);
  printf("Output: %lu\n", result4);
  printf("Expected: %lu\n", expected4);
  printf("Result: %s\n\n", (result4 == expected4) ? "SUCCESS" : "FAIL");

  // Тест 5: NULL указатель (краевое значение)
  const char *test5 = s21_NULL;
  s21_size_t result5 = s21_strlen(test5);
  s21_size_t expected5 = 0;
  printf("Test 5 - NULL pointer:\n");
  printf("Input: NULL\n");
  printf("Output: %lu\n", result5);
  printf("Expected: %lu\n", expected5);
  printf("Result: %s\n\n", (result5 == expected5) ? "SUCCESS" : "FAIL");

  // Тест 6: Специальные символы (ИСПРАВЛЕННЫЙ)
  const char *test6 = "Hello\nWorld\t!";
  s21_size_t result6 = s21_strlen(test6);
  s21_size_t expected6 = 13; // Исправлено с 12 на 13
  printf("Test 6 - Special characters:\n");
  printf("Input: \"Hello\\nWorld\\t!\"\n");
  printf("Output: %lu\n", result6);
  printf("Expected: %lu\n", expected6);
  printf("Result: %s\n\n", (result6 == expected6) ? "SUCCESS" : "FAIL");

  // Тест 7: Строка с числами
  const char *test7 = "1234567890";
  s21_size_t result7 = s21_strlen(test7);
  s21_size_t expected7 = 10;
  printf("Test 7 - Numbers string:\n");
  printf("Input: \"%s\"\n", test7);
  printf("Output: %lu\n", result7);
  printf("Expected: %lu\n", expected7);
  printf("Result: %s\n\n", (result7 == expected7) ? "SUCCESS" : "FAIL");

  // Тест 8: Смешанные символы
  const char *test8 = "Hello123!@#";
  s21_size_t result8 = s21_strlen(test8);
  s21_size_t expected8 = 11;
  printf("Test 8 - Mixed characters:\n");
  printf("Input: \"%s\"\n", test8);
  printf("Output: %lu\n", result8);
  printf("Expected: %lu\n", expected8);
  printf("Result: %s\n\n", (result8 == expected8) ? "SUCCESS" : "FAIL");
}

int main() {
  s21_strlen_test();
  return 0;
}