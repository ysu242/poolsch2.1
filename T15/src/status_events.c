#include "status_events.h"

#include <stdio.h>
#include <stdlib.h>

DEFINE_SELECT(StatusEvent) {
    StatusEvent* event = malloc(sizeof(StatusEvent));
    fseek(db, 0, SEEK_SET);

    while (fread(event, sizeof(StatusEvent), 1, db)) {
        if (event->event_id == id) {
            return event;
        }
    }
    free(event);
    return NULL;
}

DEFINE_DELETE(StatusEvent) {
    StatusEvent* event = select_StatusEvent(db, id);
    if (!event) {
        return 0;
    }

    fseek(db, id * sizeof(StatusEvent), SEEK_SET);
    StatusEvent empty = {0};
    int result = fwrite(&empty, sizeof(StatusEvent), 1, db);
    free(event);
    return result;
}

DEFINE_INSERT(StatusEvent) {
    fseek(db, 0, SEEK_END);
    return fwrite(entity, sizeof(StatusEvent), 1, db);
}

DEFINE_UPDATE(StatusEvent) {
    StatusEvent* existing = select_StatusEvent(db, id);
    if (!existing) {
        return 0;
    }

    entity->event_id = id;
    fseek(db, id * sizeof(StatusEvent), SEEK_SET);
    int result = fwrite(entity, sizeof(StatusEvent), 1, db);
    free(existing);
    return result;
}

void print_status_event(StatusEvent* event) {
    if (event) {
        printf("Event ID: %d, Module ID: %d, Status: %d, Date: %s, Time: %s\n", event->event_id,
               event->module_id, event->new_status, event->date, event->time);
    }
}