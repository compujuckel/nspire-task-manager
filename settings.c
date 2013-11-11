#include "settings.h"

BOOL interrupts = FALSE;

entry* settings_entries_create(unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	if(interrupts)
		sprintf(e[0].text,"%-20s|%s","Interrupts","on");
	else
		sprintf(e[0].text,"%-20s|%s","Interrupts","off");
	return e;
}

list2* settings_list_create()
{
	list2* t = malloc(sizeof(list2));
	t->count = 1;
	t->entries = settings_entries_create(t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void settings_list_refresh(list2* t)
{
        list2_free(t);
        t = settings_list_create();
}

void display_settings_screen(void)
{
	list2* t = settings_list_create();
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			settings_list_refresh(t);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			switch(selection)
			{
				case 0:
					if(interrupts)
					{
						TCT_Local_Control_Interrupts(-1);
						interrupts = FALSE;
					}
					else
					{
						TCT_Local_Control_Interrupts(0);
						interrupts = TRUE;
					}
					break;
			}
			settings_list_refresh(t);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Settings");
		nio_grid_puts(0,0,0,1, " Name                |Value",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "---------------------+-------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------------------------------------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Change [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}