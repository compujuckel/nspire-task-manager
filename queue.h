#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue
{
	void* queue_ptr;
	char name[10];
	void* start_address;
	unsigned queue_size;
	unsigned available;
	unsigned messages;
	unsigned char message_type;
	unsigned message_size;
	unsigned char suspend_type;
	unsigned tasks_waiting;
	void* first_task;
} queue;

typedef struct queue_list
{
	entry* entries;
	list* list;
	unsigned count;
} queue_list;

queue* queue_info(void* queue_ptr);
entry* queue_entries_create(void* pointer_list[], unsigned count);
queue_list* queue_list_create(void* pointer_list[]);
void queue_list_refresh(queue_list* t, void* pointer_list[]);

void display_queue_info_screen(unsigned int selection, void* pointer_list[]);
void display_queues_screen(void);

#endif