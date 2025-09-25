#include "print_module.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef QUEST2
#include "documentation_module.h"
#endif

int main() {
#ifndef QUEST2
  // Только для Quest 1: вывод времени
  print_log(print_char, Module_load_success_message);
#endif

#ifdef QUEST2
  // Только для Quest 2: вывод информации о документах
  char *documents[] = {Documents};
  int *availability = check_available_documentation_module(
      validate, Documents_count, documents[0], documents[1], documents[2],
      documents[3]);

  for (int i = 0; i < Documents_count; i++) {
    printf("%-15s: %s\n", documents[i],
           availability[i] ? "available" : "unavailable");
  }

  free(availability);
#endif

  return 0;
}