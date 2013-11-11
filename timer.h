#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef TIMER_H
#define TIMER_H

typedef struct timer
{
	void* timer_ptr;
	char name[10];
	unsigned char enable;
	unsigned expirations;
	unsigned id;
	unsigned initial_time;
	unsigned reschedule_time;
} timer;

timer* timer_info(void* timer_ptr);
entry* timer_entries_create(void* pointer_list[], unsigned count);
list2* timer_list_create(void* pointer_list[]);

void display_timer_info_screen(unsigned int selection, void* pointer_list[]);
void display_timers_screen(void);

#endif