#include "event.h"

event* event_info(void* event_ptr)
{
	event* t = malloc(sizeof(event));
	memset(t->name,0,10);
	t->event_ptr = event_ptr;
	EVF_Event_Group_Information(event_ptr,t->name,&t->event_flags,&t->tasks_waiting,&t->first_task);
	
	return t;
}

entry* event_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		event* t = event_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%X",t->name,t->event_flags);
		free(t);
	}
	
	return e;
}

event_list* event_list_create(void* pointer_list[])
{
	event_list* t = malloc(sizeof(event_list));
	t->count = EVF_Event_Group_Pointers(pointer_list,100);
	t->entries = event_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void event_list_free(event_list* t)
{
	free(t->entries);
	free(t->list);
	free(t);
}

void event_list_refresh(event_list* t, void* pointer_list[])
{
	event_list_free(t);
	t = event_list_create(pointer_list);
}

void display_event_info_screen(unsigned int selection, void* pointer_list[])
{
	event* p = event_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Event group information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Event flags: %d",p->event_flags);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Tasks waiting: %d",p->tasks_waiting);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"First task: 0x%p",p->first_task);
		
		nio_grid_puts(0,0,0,6,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,7,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			EVC_Delete_Event_Group(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_events_screen(void)
{
	void* pointer_list[100];
	
	event_list* t = event_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			event_list_refresh(t,pointer_list);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_event_info_screen(selection,pointer_list);
			event_list_refresh(t,pointer_list);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage event groups (showing %d of %d)",t->count,EVF_Established_Event_Groups());
		nio_grid_puts(0,0,0,1," Name      |flags",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2,"-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Event info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	event_list_free(t);
}