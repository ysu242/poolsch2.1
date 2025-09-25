#include "modules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DEFINE_SELECT(Module) {
    Module* module = malloc(sizeof(Module));
    fseek(db, 0, SEEK_SET);

    while (fread(module, sizeof(Module), 1, db)) {
        if (module->id == id && !module->deleted) {
            return module;
        }
    }
    free(module);
    return NULL;
}

DEFINE_DELETE(Module) {
    Module* module = select_Module(db, id);
    if (!module) {
        return 0;
    }

    module->deleted = 1;
    fseek(db, id * sizeof(Module), SEEK_SET);
    int result = fwrite(module, sizeof(Module), 1, db);
    free(module);
    return result;
}

DEFINE_INSERT(Module) {
    fseek(db, 0, SEEK_END);
    return fwrite(entity, sizeof(Module), 1, db);
}

DEFINE_UPDATE(Module) {
    Module* existing = select_Module(db, id);
    if (!existing) {
        return 0;
    }

    entity->id = id;
    fseek(db, id * sizeof(Module), SEEK_SET);
    int result = fwrite(entity, sizeof(Module), 1, db);
    free(existing);
    return result;
}

void print_module(Module* module) {
    if (module) {
        printf("ID: %d, Name: %s, Level: %d, Cell: %d, Deleted: %d\n", module->id, module->name,
               module->level, module->cell, module->deleted);
    }
}

Module* find_module_by_location(FILE* db, int level, int cell) {
    Module* module = malloc(sizeof(Module));
    fseek(db, 0, SEEK_SET);

    while (fread(module, sizeof(Module), 1, db)) {
        if (module->level == level && module->cell == cell && !module->deleted) {
            return module;
        }
    }
    free(module);
    return NULL;
}