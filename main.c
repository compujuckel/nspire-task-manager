#include <os.h>
#include <nspireio.h>
#include "misc.h"
#include "syscalls.h"
#include "list.h"
#include "task.h"
#include "pool.h"
#include "event.h"
#include "queue.h"
#include "semaphore.h"
#include "mailbox.h"
#include "driver.h"
#include "timer.h"
#include "settings.h"

#define MAINMENU_SIZE 9

entry* main_create_entries()
{
	entry* e = malloc(MAINMENU_SIZE*sizeof(entry));
	strcpy(e[0].text,"Manage tasks");
	strcpy(e[1].text,"Manage memory pools");
	strcpy(e[2].text,"Manage event groups");
	strcpy(e[3].text,"Manage queues");
	strcpy(e[4].text,"Manage semaphores");
	strcpy(e[5].text,"Manage mailboxes");
	strcpy(e[6].text,"Manage drivers");
	strcpy(e[7].text,"Manage timers");
	strcpy(e[8].text,"Settings");
	return e;
}

int main(void)
{	
	entry* entries = main_create_entries();
	list* menu = create_list(0,24,25,entries,MAINMENU_SIZE);
	nio_scrbuf_init();
	do
	{
		int selection = update_list(menu);
		if(selection != -1)
		{
			wait_no_key_pressed();
			switch(selection)
			{
				case 0:
					display_tasks_screen();
					break;
				case 1:
					display_pools_screen();
					break;
				case 2:
					display_events_screen();
					break;
				case 3:
					display_queues_screen();
					break;
				case 4:
					display_semaphores_screen();
					break;
				case 5:
					display_mailboxes_screen();
					break;
				case 6:
					display_drivers_screen();
					break;
				case 7:
					display_timers_screen();
					break;
				default:
					display_settings_screen();
			}
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"TI-Nspire Task Manager (built %s %s)",__DATE__,__TIME__);
		int i;
		for(i = 0; i < 53; i++)
		{
			nio_grid_putc(0,0,i,2,'-',NIO_COLOR_WHITE,NIO_COLOR_BLACK);
			nio_grid_putc(0,0,i,28,'-',NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		}
		draw_list(menu);
		nio_grid_puts(0,0,0,29,"Use UP/DOWN keys to navigate, ENTER to select",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	nio_scrbuf_free();
	free(entries);
	free(menu);
	return 0;
}