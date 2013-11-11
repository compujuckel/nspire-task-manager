#include "timer.h"

timer* timer_info(void* timer_ptr)
{
	timer* t = malloc(sizeof(timer));
	memset(t->name,0,10);
	t->timer_ptr = timer_ptr;
	TMF_Timer_Information(timer_ptr,t->name,&t->enable,&t->expirations,&t->id,&t->initial_time,&t->reschedule_time);
	
	return t;
}

static const char yes[] = "Yes";
static const char no[] = "No";

const char* timer_enabled(unsigned enable)
{
	if(enable == 5)
		return yes;
	return no;
}

entry* timer_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		timer* t = timer_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%-3s|",t->name,timer_enabled(t->enable));
		free(t);
	}
	
	return e;
}

list2* timer_list_create(void* pointer_list[])
{
	list2* t = malloc(sizeof(list2));
	t->count = TMF_Timer_Pointers(pointer_list,100);
	t->entries = timer_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void display_timer_info_screen(unsigned int selection, void* pointer_list[])
{
	timer* p = timer_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Timer information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Enable: %d (%s)",p->enable,timer_enabled(p->enable));
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Expirations: %d",p->expirations);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"ID: %d",p->id);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Initial time: %d",p->initial_time);
		nio_grid_printf(0,0,0,6,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Reschedule time: %d",p->reschedule_time);
		
		nio_grid_puts(0,0,0,8,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,9,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			TMS_Delete_Timer(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_timers_screen(void)
{
	void* pointer_list[100];
	
	list2* t = timer_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			list2_refresh(t,pointer_list,&timer_list_create);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_timer_info_screen(selection,pointer_list);
			list2_refresh(t,pointer_list,&timer_list_create);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage timers (showing %d of %d)",t->count,TMF_Established_Timers());
		nio_grid_puts(0,0,0,1, " Name      |ena|",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------+---+-------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+---+-------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] timer info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}