#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door *doors);
void sort_doors(struct door *doors, int n);
void close_all_doors(struct door *doors, int n);
void output_doors(struct door *doors, int n);

int main() {
  struct door doors[DOORS_COUNT];

  initialize_doors(doors);

  // Сортируем двери по ID
  sort_doors(doors, DOORS_COUNT);

  // Закрываем все двери
  close_all_doors(doors, DOORS_COUNT);

  // Выводим результат
  output_doors(doors, DOORS_COUNT);

  return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
  srand(time(0));

  int seed = rand() % MAX_ID_SEED;
  for (int i = 0; i < DOORS_COUNT; i++) {
    doors[i].id = (i + seed) % DOORS_COUNT;
    doors[i].status = rand() % 2;
  }
}

// Функция сортировки дверей по возрастанию ID
void sort_doors(struct door *doors, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (doors[j].id > doors[j + 1].id) {
        struct door temp = doors[j];
        doors[j] = doors[j + 1];
        doors[j + 1] = temp;
      }
    }
  }
}

// Функция закрытия всех дверей
void close_all_doors(struct door *doors, int n) {
  for (int i = 0; i < n; i++) {
    doors[i].status = 0;
  }
}

// Функция вывода дверей в формате "id, status"
void output_doors(struct door *doors, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d, %d\n", doors[i].id, doors[i].status);
  }
}