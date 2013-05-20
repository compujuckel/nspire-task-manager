#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef POOL_H
#define POOL_H

typedef struct pool
{
	void* pool_ptr;
	char name[10];
	void* start_address;
	unsigned pool_size;
	unsigned min_allocation;
	unsigned available;
	unsigned char suspend_type;
	unsigned tasks_waiting;
	void* first_task;
} pool;

typedef struct pool_list
{
	entry* entries;
	list* list;
	unsigned count;
} pool_list;

pool* pool_info(void* pool_ptr);
entry* pool_entries_create(void* pointer_list[], unsigned count);
pool_list* pool_list_create(void* pointer_list[]);
void pool_list_refresh(pool_list* t, void* pointer_list[]);

void display_pool_info_screen(unsigned int selection, void* pointer_list[]);
void display_pools_screen(void);

#endif