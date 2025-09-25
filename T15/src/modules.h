#ifndef MODULES_H
#define MODULES_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int id;
    char name[30];
    int level;
    int cell;
    int deleted;
} Module;

// Объявления функций
DECLARE_SELECT(Module);
DECLARE_DELETE(Module);
DECLARE_INSERT(Module);
DECLARE_UPDATE(Module);

void print_module(Module* module);
Module* find_module_by_location(FILE* db, int level, int cell);

#endif