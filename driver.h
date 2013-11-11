#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef DRIVER_H
#define DRIVER_H

typedef struct driver
{
	void* driver_ptr;
	char name[10];
	// ...
} driver;

driver* driver_info(void* driver_ptr);
entry* driver_entries_create(void* pointer_list[], unsigned count);
list2* driver_list_create(void* pointer_list[]);

void display_driver_info_screen(unsigned int selection, void* pointer_list[]);
void display_drivers_screen(void);

#endif