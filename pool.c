#include "pool.h"

pool* pool_info(void* pool_ptr)
{
	pool* t = malloc(sizeof(pool));
	memset(t->name,0,10);
	t->pool_ptr = pool_ptr;
	DMF_Memory_Pool_Information(pool_ptr,t->name,&t->start_address,&t->pool_size,&t->min_allocation,&t->available,&t->suspend_type,&t->tasks_waiting,&t->first_task);
	
	return t;
}

entry* pool_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		pool* t = pool_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%6dK/%-6dK| %2d%% free",t->name,t->available/1024,t->pool_size/1024,(int)(((float)t->available/(float)t->pool_size)*100.f));
		free(t);
	}
	
	return e;
}

list2* pool_list_create(void* pointer_list[])
{
	list2* t = malloc(sizeof(list2));
	t->count = DMF_Memory_Pool_Pointers(pointer_list,100);
	t->entries = pool_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void display_pool_info_screen(unsigned int selection, void* pointer_list[])
{
	pool* p = pool_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Memory pool information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Start address: 0x%p",p->start_address);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Pool size: %d",p->pool_size);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Min. allocation: %d",p->min_allocation);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Available: %d",p->available);
		nio_grid_printf(0,0,0,6,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Suspend type: %d",p->suspend_type);
		nio_grid_printf(0,0,0,7,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Tasks waiting: %d",p->tasks_waiting);
		nio_grid_printf(0,0,0,8,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"First task: 0x%p",p->first_task);
		
		nio_grid_puts(0,0,0,10,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,11,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			DMC_Delete_Memory_Pool(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_pools_screen(void)
{
	void* pointer_list[100];
	
	list2* t = pool_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			list2_refresh(t,pointer_list,&pool_list_create);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_pool_info_screen(selection,pointer_list);
			list2_refresh(t,pointer_list,&pool_list_create);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage memory pools (showing %d of %d)",t->count,DMF_Established_Memory_Pools());
		nio_grid_puts(0,0,0,1," Name      |   free/total  |",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2,"-----------+---------------+-------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+---------------+-------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Pool info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}