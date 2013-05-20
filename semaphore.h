#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct semaphore
{
	void* semaphore_ptr;
	char name[10];
	unsigned int current_count;
	unsigned char suspend_type;
	unsigned int tasks_waiting;
	void* first_task;
} semaphore;

typedef struct semaphore_list
{
	entry* entries;
	list* list;
	unsigned count;
} semaphore_list;

semaphore* semaphore_info(void* semaphore_ptr);
const char* semaphore_preempt(int preempt);
entry* semaphore_entries_create(void* pointer_list[], unsigned count);
semaphore_list* semaphore_list_create(void* pointer_list[]);
void semaphore_list_free(semaphore_list* t);
void semaphore_list_refresh(semaphore_list* t, void* pointer_list[]);

void display_semaphores_screen(void);
void display_semaphore_info_screen(unsigned int selection, void* pointer_list[]);

#endif