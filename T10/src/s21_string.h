#ifndef S21_STRING_H
#define S21_STRING_H

// Сначала определяем тип
typedef unsigned long s21_size_t;

// Определяем NULL
#define s21_NULL ((void *)0)

// Потом объявляем функцию
s21_size_t s21_strlen(const char *str);

#endif // S21_STRING_H