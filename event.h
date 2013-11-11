#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef EVENT_H
#define EVENT_H

typedef struct event
{
	void* event_ptr;
	char name[10];
	unsigned event_flags;
	unsigned tasks_waiting;
	void* first_task;
} event;

event* event_info(void* event_ptr);
entry* event_entries_create(void* pointer_list[], unsigned count);
list2* event_list_create(void* pointer_list[]);

void display_event_info_screen(unsigned int selection, void* pointer_list[]);
void display_events_screen(void);

#endif