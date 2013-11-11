#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef TASK_H
#define TASK_H

extern const char NU_STATUS[13][20];

typedef struct task
{
	void* task_ptr;
	char name[10];
	unsigned char status;
	unsigned int scheduled_count;
	unsigned char priority;
	unsigned char preempt;
	unsigned int time_slice;
	void* stack_base;
	unsigned int stack_size;
	unsigned int minimum_stack;
} task;

task* task_info(void* task_ptr);
const char* task_preempt(int preempt);
entry* task_entries_create(void* pointer_list[], unsigned count);
list2* task_list_create(void* pointer_list[]);

void display_tasks_screen(void);
void display_task_info_screen(unsigned int selection, void* pointer_list[]);

#endif