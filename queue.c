#include "queue.h"

queue* queue_info(void* queue_ptr)
{
	queue* t = malloc(sizeof(queue));
	memset(t->name,0,10);
	t->queue_ptr = queue_ptr;
	QUF_Queue_Information(queue_ptr,t->name,&t->start_address,&t->queue_size,&t->available,&t->messages,&t->message_type,&t->message_size,&t->suspend_type,&t->tasks_waiting,&t->first_task);
	
	return t;
}

entry* queue_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		queue* t = queue_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%6d/%-6d|%d",t->name,t->available,t->queue_size,t->messages);
		free(t);
	}
	
	return e;
}

list2* queue_list_create(void* pointer_list[])
{
	list2* t = malloc(sizeof(list2));
	t->count = QUF_Queue_Pointers(pointer_list,100);
	t->entries = queue_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void display_queue_info_screen(unsigned int selection, void* pointer_list[])
{
	queue* p = queue_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Queue information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Start address: 0x%p",p->start_address);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Queue size: %d",p->queue_size);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Available: %d",p->available);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Messages: %d",p->messages);
		nio_grid_printf(0,0,0,6,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Message type: %d",p->message_type);
		nio_grid_printf(0,0,0,7,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Message size: %d",p->message_size);
		nio_grid_printf(0,0,0,8,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Suspend type: %d",p->suspend_type);
		nio_grid_printf(0,0,0,9,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Tasks waiting: %d",p->tasks_waiting);
		nio_grid_printf(0,0,0,10,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"First task: 0x%p",p->first_task);
		
		nio_grid_puts(0,0,0,12,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,13,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			QUC_Delete_Queue(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_queues_screen(void)
{
	void* pointer_list[100];
	
	list2* t = queue_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			list2_refresh(t,pointer_list,&queue_list_create);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_queue_info_screen(selection,pointer_list);
			list2_refresh(t,pointer_list,&queue_list_create);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage queues (showing %d of %d)",t->count,QUF_Established_Queues());
		nio_grid_puts(0,0,0,1, " Name      |  free/total |Messages",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------+-------------+---------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+-------------+---------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Queue info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}