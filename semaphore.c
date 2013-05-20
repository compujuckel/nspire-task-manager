#include "semaphore.h"

semaphore* semaphore_info(void* semaphore_ptr)
{
	semaphore* t = malloc(sizeof(semaphore));
	memset(t->name,0,10);
	t->semaphore_ptr = semaphore_ptr;
	SMF_Semaphore_Information(semaphore_ptr,t->name,&t->current_count,&t->suspend_type,&t->tasks_waiting,&t->first_task);
	
	return t;
}

entry* semaphore_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		semaphore* t = semaphore_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%d",t->name,t->current_count);
		free(t);
	}
	
	return e;
}

semaphore_list* semaphore_list_create(void* pointer_list[])
{
	semaphore_list* t = malloc(sizeof(semaphore_list));
	t->count = SMF_Semaphore_Pointers(pointer_list,100);
	t->entries = semaphore_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void semaphore_list_free(semaphore_list* t)
{
	free(t->entries);
	free(t->list);
	free(t);
}

void semaphore_list_refresh(semaphore_list* t, void* pointer_list[])
{
	semaphore_list_free(t);
	t = semaphore_list_create(pointer_list);
}

void display_semaphore_info_screen(unsigned int selection, void* pointer_list[])
{
	semaphore* tsk = semaphore_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Semaphore information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",tsk->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Current count: %d",tsk->current_count);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Suspend type: %d",tsk->suspend_type);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Tasks waiting: %d",tsk->tasks_waiting);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"First task: 0x%p",tsk->first_task);
		
		nio_grid_puts(0,0,0,7,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,8,"[1] Terminate",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			SMC_Delete_Semaphore(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(tsk);
}

void display_semaphores_screen(void)
{
	void* pointer_list[100];
	
	semaphore_list* t = semaphore_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			semaphore_list_refresh(t,pointer_list);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_semaphore_info_screen(selection,pointer_list);
			semaphore_list_refresh(t,pointer_list);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage semaphores (showing %d of %d)",t->count,SMF_Established_Semaphores());
		nio_grid_puts(0,0,0,1, " Name      |Current",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+-----------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Semaphore info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);

		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	semaphore_list_free(t);
}