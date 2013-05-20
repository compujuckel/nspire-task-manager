#include "mailbox.h"

mailbox* mailbox_info(void* mailbox_ptr)
{
	mailbox* t = malloc(sizeof(mailbox));
	memset(t->name,0,10);
	t->mailbox_ptr = mailbox_ptr;
	MBF_Mailbox_Information(mailbox_ptr,t->name,&t->suspend_type,&t->message_present,&t->tasks_waiting,&t->first_task);
	
	return t;
}

entry* mailbox_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		mailbox* t = mailbox_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%d",t->name,t->message_present);
		free(t);
	}
	
	return e;
}

mailbox_list* mailbox_list_create(void* pointer_list[])
{
	mailbox_list* t = malloc(sizeof(mailbox_list));
	t->count = MBF_Mailbox_Pointers(pointer_list,100);
	t->entries = mailbox_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void mailbox_list_free(mailbox_list* t)
{
	free(t->entries);
	free(t->list);
	free(t);
}

void mailbox_list_refresh(mailbox_list* t, void* pointer_list[])
{
	mailbox_list_free(t);
	t = mailbox_list_create(pointer_list);
}

void display_mailbox_info_screen(unsigned int selection, void* pointer_list[])
{
	mailbox* p = mailbox_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Memory mailbox information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Suspend type: %d",p->suspend_type);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Message present: %d",p->message_present);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Tasks waiting: %d",p->tasks_waiting);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"First task: 0x%p",p->first_task);
		
		nio_grid_puts(0,0,0,7,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,8,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			MBC_Delete_Mailbox(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_mailboxes_screen(void)
{
	void* pointer_list[100];
	
	mailbox_list* t = mailbox_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			mailbox_list_refresh(t,pointer_list);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_mailbox_info_screen(selection,pointer_list);
			mailbox_list_refresh(t,pointer_list);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage memory mailboxs (showing %d of %d)",t->count,MBF_Established_Mailboxes());
		nio_grid_puts(0,0,0,1, " Name      |Message",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Mailbox info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	mailbox_list_free(t);
}