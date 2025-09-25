#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levels.h"
#include "modules.h"
#include "status_events.h"

// Функции для загрузки начальных данных
void load_initial_data(FILE* modules_db, FILE* levels_db, FILE* status_events_db) {
    // Инициализация уровней
    Level levels[] = {{1, 4, 0}, {2, 4, 0}, {3, 4, 0}, {4, 4, 0}};

    for (int i = 0; i < 4; i++) {
        insert_Level(levels_db, &levels[i]);
    }

    // Инициализация модулей
    Module modules[] = {{0, "Main module", 4, 3, 0},
                        {1, "Text module", 2, 3, 0},
                        {2, "Audio module", 3, 4, 0},
                        {3, "Speech module", 1, 2, 0},
                        {4, "Fuzzy module", 4, 3, 0},
                        {5, "Neural module", 1, 1, 0},
                        {6, "Door management module", 1, 4, 0},
                        {7, "Simple logic module", 2, 2, 0}};

    for (int i = 0; i < 8; i++) {
        insert_Module(modules_db, &modules[i]);
    }

    // Инициализация событий статусов
    StatusEvent events[] = {{0, 0, 1, "05.11.2020", "08:43:59"}, {1, 1, 1, "08.07.2020", "02:07:10"},
                            {2, 2, 1, "28.11.2020", "06:03:02"}, {3, 3, 1, "15.01.2020", "15:36:22"},
                            {4, 4, 1, "05.01.2020", "08:14:24"}, {5, 5, 1, "11.06.2020", "17:48:49"},
                            {6, 6, 1, "25.03.2020", "16:26:42"}, {7, 7, 1, "24.09.2020", "13:16:23"}};

    for (int i = 0; i < 8; i++) {
        insert_StatusEvent(status_events_db, &events[i]);
    }
}

void print_all_modules(FILE* db, int limit) {
    printf("=== MODULES TABLE ===\n");
    Module module;
    fseek(db, 0, SEEK_SET);
    int count = 0;

    while (fread(&module, sizeof(Module), 1, db) && (limit == 0 || count < limit)) {
        if (!module.deleted) {
            printf("%d %s %d %d %d\n", module.id, module.name, module.level, module.cell, module.deleted);
            count++;
        }
    }
}

void print_all_levels(FILE* db, int limit) {
    printf("=== LEVELS TABLE ===\n");
    Level level;
    fseek(db, 0, SEEK_SET);
    int count = 0;

    while (fread(&level, sizeof(Level), 1, db) && (limit == 0 || count < limit)) {
        if (level.level_num != 0) {
            printf("%d %d %d\n", level.level_num, level.cells_count, level.protected);
            count++;
        }
    }
}

void print_all_status_events(FILE* db, int limit) {
    printf("=== STATUS EVENTS TABLE ===\n");
    StatusEvent event;
    fseek(db, 0, SEEK_SET);
    int count = 0;

    while (fread(&event, sizeof(StatusEvent), 1, db) && (limit == 0 || count < limit)) {
        if (event.event_id != 0) {
            printf("%d %d %d %s %s\n", event.event_id, event.module_id, event.new_status, event.date,
                   event.time);
            count++;
        }
    }
}

void select_operation(FILE* modules_db, FILE* levels_db, FILE* status_events_db) {
    int table_choice;
    printf("Please choose a table:\n");
    printf("1. Modules\n");
    printf("2. Levels\n");
    printf("3. Status events\n");
    printf("> ");
    scanf("%d", &table_choice);

    int limit;
    printf("Insert the number of records or leave empty to output all of them: ");
    if (scanf("%d", &limit) != 1) {
        limit = 0;                  // Все записи
        while (getchar() != '\n');  // Очистка буфера
    }

    switch (table_choice) {
        case 1:
            print_all_modules(modules_db, limit);
            break;
        case 2:
            print_all_levels(levels_db, limit);
            break;
        case 3:
            print_all_status_events(status_events_db, limit);
            break;
        default:
            printf("Invalid table choice!\n");
    }
}

void insert_operation(FILE* modules_db, FILE* levels_db, FILE* status_events_db) {
    int table_choice;
    printf("Please choose a table:\n");
    printf("1. Modules\n");
    printf("2. Levels\n");
    printf("3. Status events\n");
    printf("> ");
    scanf("%d", &table_choice);

    switch (table_choice) {
        case 1: {
            Module new_module;
            printf("Enter module ID: ");
            scanf("%d", &new_module.id);
            printf("Enter module name: ");
            scanf("%29s", new_module.name);
            printf("Enter level: ");
            scanf("%d", &new_module.level);
            printf("Enter cell: ");
            scanf("%d", &new_module.cell);
            new_module.deleted = 0;

            if (insert_Module(modules_db, &new_module)) {
                printf("Module inserted successfully!\n");
            } else {
                printf("Failed to insert module!\n");
            }
            break;
        }
        case 2: {
            Level new_level;
            printf("Enter level number: ");
            scanf("%d", &new_level.level_num);
            printf("Enter cells count: ");
            scanf("%d", &new_level.cells_count);
            printf("Enter protected flag: ");
            scanf("%d", &new_level.protected);

            if (insert_Level(levels_db, &new_level)) {
                printf("Level inserted successfully!\n");
            } else {
                printf("Failed to insert level!\n");
            }
            break;
        }
        case 3: {
            StatusEvent new_event;
            printf("Enter event ID: ");
            scanf("%d", &new_event.event_id);
            printf("Enter module ID: ");
            scanf("%d", &new_event.module_id);
            printf("Enter new status: ");
            scanf("%d", &new_event.new_status);
            printf("Enter date (dd.mm.yyyy): ");
            scanf("%10s", new_event.date);
            printf("Enter time (hh:mm:ss): ");
            scanf("%8s", new_event.time);

            if (insert_StatusEvent(status_events_db, &new_event)) {
                printf("Status event inserted successfully!\n");
            } else {
                printf("Failed to insert status event!\n");
            }
            break;
        }
        default:
            printf("Invalid table choice!\n");
    }
}

void update_operation(FILE* modules_db, FILE* levels_db, FILE* status_events_db) {
    int table_choice;
    printf("Please choose a table:\n");
    printf("1. Modules\n");
    printf("2. Levels\n");
    printf("3. Status events\n");
    printf("> ");
    scanf("%d", &table_choice);

    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    switch (table_choice) {
        case 1: {
            Module* existing = select_Module(modules_db, id);
            if (!existing) {
                printf("Module not found!\n");
                break;
            }

            Module updated = *existing;
            printf("Enter new module name (current: %s): ", existing->name);
            scanf("%29s", updated.name);
            printf("Enter new level (current: %d): ", existing->level);
            scanf("%d", &updated.level);
            printf("Enter new cell (current: %d): ", existing->cell);
            scanf("%d", &updated.cell);

            if (update_Module(modules_db, id, &updated)) {
                printf("Module updated successfully!\n");
            } else {
                printf("Failed to update module!\n");
            }
            free(existing);
            break;
        }
        case 2: {
            Level* existing = select_Level(levels_db, id);
            if (!existing) {
                printf("Level not found!\n");
                break;
            }

            Level updated = *existing;
            printf("Enter new cells count (current: %d): ", existing->cells_count);
            scanf("%d", &updated.cells_count);
            printf("Enter new protected flag (current: %d): ", existing->protected);
            scanf("%d", &updated.protected);

            if (update_Level(levels_db, id, &updated)) {
                printf("Level updated successfully!\n");
            } else {
                printf("Failed to update level!\n");
            }
            free(existing);
            break;
        }
        case 3: {
            StatusEvent* existing = select_StatusEvent(status_events_db, id);
            if (!existing) {
                printf("Status event not found!\n");
                break;
            }

            StatusEvent updated = *existing;
            printf("Enter new module ID (current: %d): ", existing->module_id);
            scanf("%d", &updated.module_id);
            printf("Enter new status (current: %d): ", existing->new_status);
            scanf("%d", &updated.new_status);
            printf("Enter new date (current: %s): ", existing->date);
            scanf("%10s", updated.date);
            printf("Enter new time (current: %s): ", existing->time);
            scanf("%8s", updated.time);

            if (update_StatusEvent(status_events_db, id, &updated)) {
                printf("Status event updated successfully!\n");
            } else {
                printf("Failed to update status event!\n");
            }
            free(existing);
            break;
        }
        default:
            printf("Invalid table choice!\n");
    }
}

void delete_operation(FILE* modules_db, FILE* levels_db, FILE* status_events_db) {
    int table_choice;
    printf("Please choose a table:\n");
    printf("1. Modules\n");
    printf("2. Levels\n");
    printf("3. Status events\n");
    printf("> ");
    scanf("%d", &table_choice);

    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    switch (table_choice) {
        case 1:
            if (delete_Module(modules_db, id)) {
                printf("Module deleted successfully!\n");
            } else {
                printf("Failed to delete module!\n");
            }
            break;
        case 2:
            if (delete_Level(levels_db, id)) {
                printf("Level deleted successfully!\n");
            } else {
                printf("Failed to delete level!\n");
            }
            break;
        case 3:
            if (delete_StatusEvent(status_events_db, id)) {
                printf("Status event deleted successfully!\n");
            } else {
                printf("Failed to delete status event!\n");
            }
            break;
        default:
            printf("Invalid table choice!\n");
    }
}

void get_active_modules(FILE* modules_db, FILE* status_events_db) {
    printf("Active modules (status = 1):\n");
    Module module;
    fseek(modules_db, 0, SEEK_SET);

    while (fread(&module, sizeof(Module), 1, modules_db)) {
        if (!module.deleted) {
            // Проверяем статус модуля
            StatusEvent event;
            fseek(status_events_db, 0, SEEK_SET);
            int found = 0;

            while (fread(&event, sizeof(StatusEvent), 1, status_events_db)) {
                if (event.module_id == module.id && event.new_status == 1) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("%d %s %d %d %d\n", module.id, module.name, module.level, module.cell, module.deleted);
            }
        }
    }
}

void delete_modules_by_ids(FILE* modules_db) {
    printf("Please input the ids of the deleting modules: ");
    char input[100];
    while (getchar() != '\n');  // Очистка буфера
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " \n");
    int deleted_count = 0;
    char result[200] = "Modules ";

    while (token != NULL) {
        int id = atoi(token);
        if (delete_Module(modules_db, id)) {
            char temp[10];
            sprintf(temp, "%d, ", id);
            strcat(result, temp);
            deleted_count++;
        }
        token = strtok(NULL, " \n");
    }

    if (deleted_count > 0) {
        // Убираем последнюю запятую и пробел
        result[strlen(result) - 2] = '\0';
        printf("%s marked as deleted\n", result);
    } else {
        printf("No modules were deleted\n");
    }
}

void set_protected_mode_for_module(FILE* modules_db, FILE* levels_db) {
    int module_id;
    printf("Enter module ID: ");
    scanf("%d", &module_id);

    Module* module = select_Module(modules_db, module_id);
    if (!module) {
        printf("Module not found!\n");
        return;
    }

    Level* level = select_Level(levels_db, module->level);
    if (!level) {
        printf("Level not found!\n");
        free(module);
        return;
    }

    level->protected = 1;
    if (update_Level(levels_db, module->level, level)) {
        printf("Protected mode set for module %d (level %d)\n", module_id, module->level);
    } else {
        printf("Failed to set protected mode\n");
    }

    free(module);
    free(level);
}

void move_module(FILE* modules_db, FILE* levels_db) {
    int module_id, new_level, new_cell;
    printf("Enter module ID: ");
    scanf("%d", &module_id);
    printf("Enter new level: ");
    scanf("%d", &new_level);
    printf("Enter new cell: ");
    scanf("%d", &new_cell);

    Module* module = select_Module(modules_db, module_id);
    if (!module) {
        printf("Module not found!\n");
        return;
    }

    Level* level = select_Level(levels_db, new_level);
    if (!level) {
        printf("Level not found!\n");
        free(module);
        return;
    }

    if (new_cell < 1 || new_cell > level->cells_count) {
        printf("Invalid cell number! Level %d has only %d cells\n", new_level, level->cells_count);
        free(module);
        free(level);
        return;
    }

    module->level = new_level;
    module->cell = new_cell;

    if (update_Module(modules_db, module_id, module)) {
        printf("Module %d moved to level %d, cell %d\n", module_id, new_level, new_cell);
    } else {
        printf("Failed to move module\n");
    }

    free(module);
    free(level);
}

void set_protection_for_level(FILE* levels_db) {
    int level_num, protected;
    printf("Enter level number: ");
    scanf("%d", &level_num);
    printf("Enter protection flag (0 or 1): ");
    scanf("%d", &protected);

    Level* level = select_Level(levels_db, level_num);
    if (!level) {
        printf("Level not found!\n");
        return;
    }

    level->protected = protected;

    if (update_Level(levels_db, level_num, level)) {
        printf("Protection flag set to %d for level %d\n", protected, level_num);
    } else {
        printf("Failed to set protection flag\n");
    }

    free(level);
}

int main() {
    FILE* modules_db = fopen("../materials/modules.db", "rb+");
    FILE* levels_db = fopen("../materials/levels.db", "rb+");
    FILE* status_events_db = fopen("../materials/status_events.db", "rb+");

    // Если файлы не существуют, создаем их и загружаем начальные данные
    int need_init = 0;
    if (!modules_db) {
        modules_db = fopen("../materials/modules.db", "wb+");
        need_init = 1;
    }
    if (!levels_db) {
        levels_db = fopen("../materials/levels.db", "wb+");
        need_init = 1;
    }
    if (!status_events_db) {
        status_events_db = fopen("../materials/status_events.db", "wb+");
        need_init = 1;
    }

    if (!modules_db || !levels_db || !status_events_db) {
        printf("Error opening database files!\n");
        return 1;
    }

    if (need_init) {
        printf("Initializing database with sample data...\n");
        load_initial_data(modules_db, levels_db, status_events_db);
    }

    int choice;
    do {
        printf("\nPlease choose one operation:\n");
        printf("1. SELECT\n");
        printf("2. INSERT\n");
        printf("3. UPDATE\n");
        printf("4. DELETE\n");
        printf("5. Get all active additional modules (last module status is 1)\n");
        printf("6. Delete modules by ids\n");
        printf("7. Set protected mode for module by id\n");
        printf("8. Move module by id to specified memory level and cell\n");
        printf("9. Set protection flag of the specified memory level\n");
        printf("0. Exit\n");
        printf("> ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Очистка буфера при ошибке ввода
            choice = -1;
        }

        switch (choice) {
            case 1:
                select_operation(modules_db, levels_db, status_events_db);
                break;
            case 2:
                insert_operation(modules_db, levels_db, status_events_db);
                break;
            case 3:
                update_operation(modules_db, levels_db, status_events_db);
                break;
            case 4:
                delete_operation(modules_db, levels_db, status_events_db);
                break;
            case 5:
                get_active_modules(modules_db, status_events_db);
                break;
            case 6:
                delete_modules_by_ids(modules_db);
                break;
            case 7:
                set_protected_mode_for_module(modules_db, levels_db);
                break;
            case 8:
                move_module(modules_db, levels_db);
                break;
            case 9:
                set_protection_for_level(levels_db);
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    fclose(modules_db);
    fclose(levels_db);
    fclose(status_events_db);

    return 0;
}