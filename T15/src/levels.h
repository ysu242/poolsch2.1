#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int level_num;
    int cells_count;
    int protected;
} Level;

// Объявления функций
DECLARE_SELECT(Level);
DECLARE_DELETE(Level);
DECLARE_INSERT(Level);
DECLARE_UPDATE(Level);

void print_level(Level* level);

#endif