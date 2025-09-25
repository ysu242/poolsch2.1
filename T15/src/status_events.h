#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} StatusEvent;

// Объявления функций
DECLARE_SELECT(StatusEvent);
DECLARE_DELETE(StatusEvent);
DECLARE_INSERT(StatusEvent);
DECLARE_UPDATE(StatusEvent);

void print_status_event(StatusEvent* event);

#endif