#include "driver.h"

driver* driver_info(void* driver_ptr)
{
	driver* t = malloc(sizeof(driver));
	memset(t->name,0,10);
	// we have to get the name manually because there is no IOF_Driver_Information function.
	strncpy(t->name,driver_ptr+20,8);
	t->driver_ptr = driver_ptr;
	
	return t;
}

entry* driver_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		driver* t = driver_info(pointer_list[i]);
		sprintf(e[i].text,"%s",t->name);
		free(t);
	}

	return e;
}

list2* driver_list_create(void* pointer_list[])
{
	list2* t = malloc(sizeof(list2));
	t->count = IOF_Driver_Pointers(pointer_list,100);
	t->entries = driver_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);

	return t;
}

void display_driver_info_screen(unsigned int selection, void* pointer_list[])
{
	driver* p = driver_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Driver information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",p->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Address: 0x%x",p->driver_ptr);
		
		nio_grid_puts(0,0,0,4,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,5,"[1] Delete",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			IOC_Delete_Driver(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(p);
}

void display_drivers_screen(void)
{
	void* pointer_list[100];
	
	list2* t = driver_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			list2_refresh(t,pointer_list,&driver_list_create);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_driver_info_screen(selection,pointer_list);
			list2_refresh(t,pointer_list,&driver_list_create);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage drivers (showing %d of %d)",t->count,IOF_Established_Drivers());
		nio_grid_puts(0,0,0,1, " Name",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------------------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------------------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Driver info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}