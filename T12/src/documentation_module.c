#include "documentation_module.h"
#include <stdarg.h>
#include <stdlib.h>

int validate(char *data) {
  int validation_result = !strcmp(data, Available_document);
  return validation_result;
}

int *check_available_documentation_module(int (*validate)(char *),
                                          int document_count, ...) {
  int *availability = malloc(document_count * sizeof(int));
  va_list args; // Исправлено: было valist
  va_start(args, document_count);

  for (int i = 0; i < document_count; i++) {
    char *doc_name = va_arg(args, char *);
    availability[i] = validate(doc_name);
  }

  va_end(args);
  return availability;
}