#include "levels.h"

#include <stdio.h>
#include <stdlib.h>

DEFINE_SELECT(Level) {
    Level* level = malloc(sizeof(Level));
    fseek(db, 0, SEEK_SET);

    while (fread(level, sizeof(Level), 1, db)) {
        if (level->level_num == id) {
            return level;
        }
    }
    free(level);
    return NULL;
}

DEFINE_DELETE(Level) {
    Level* level = select_Level(db, id);
    if (!level) {
        return 0;
    }

    fseek(db, (id - 1) * sizeof(Level), SEEK_SET);
    Level empty = {0};
    int result = fwrite(&empty, sizeof(Level), 1, db);
    free(level);
    return result;
}

DEFINE_INSERT(Level) {
    fseek(db, 0, SEEK_END);
    return fwrite(entity, sizeof(Level), 1, db);
}

DEFINE_UPDATE(Level) {
    Level* existing = select_Level(db, id);
    if (!existing) {
        return 0;
    }

    entity->level_num = id;
    fseek(db, (id - 1) * sizeof(Level), SEEK_SET);
    int result = fwrite(entity, sizeof(Level), 1, db);
    free(existing);
    return result;
}

void print_level(Level* level) {
    if (level) {
        printf("Level: %d, Cells: %d, Protected: %d\n", level->level_num, level->cells_count,
               level->protected);
    }
}