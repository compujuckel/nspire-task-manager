#include <os.h>
#include <nspireio.h>
#include "syscalls.h"
#include "list.h"
#include "misc.h"

#ifndef MAILBOX_H
#define MAILBOX_H

typedef struct mailbox
{
	void* mailbox_ptr;
	char name[10];
	unsigned char suspend_type;
	unsigned char message_present;
	unsigned tasks_waiting;
	void* first_task;
} mailbox;

mailbox* mailbox_info(void* mailbox_ptr);
entry* mailbox_entries_create(void* pointer_list[], unsigned count);
list2* mailbox_list_create(void* pointer_list[]);

void display_mailbox_info_screen(unsigned int selection, void* pointer_list[]);
void display_mailboxes_screen(void);

#endif