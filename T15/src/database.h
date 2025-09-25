#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

// Макросы для объявления функций для конкретной сущности
#define DECLARE_SELECT(ENTITY) ENTITY* select_##ENTITY(FILE* db, int id)
#define DECLARE_DELETE(ENTITY) int delete_##ENTITY(FILE* db, int id)
#define DECLARE_INSERT(ENTITY) int insert_##ENTITY(FILE* db, ENTITY* entity)
#define DECLARE_UPDATE(ENTITY) int update_##ENTITY(FILE* db, int id, ENTITY* entity)

// Макросы для определения функций для конкретной сущности
#define DEFINE_SELECT(ENTITY) ENTITY* select_##ENTITY(FILE* db, int id)
#define DEFINE_DELETE(ENTITY) int delete_##ENTITY(FILE* db, int id)
#define DEFINE_INSERT(ENTITY) int insert_##ENTITY(FILE* db, ENTITY* entity)
#define DEFINE_UPDATE(ENTITY) int update_##ENTITY(FILE* db, int id, ENTITY* entity)

#endif