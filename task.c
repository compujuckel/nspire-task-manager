#include "task.h"

const char NU_STATUS[13][20] = 
{
	"READY",
	"PURE_SUSPEND",
	"SLEEP_SUSPEND",
	"MAILBOX_SUSPEND",
	"QUEUE_SUSPEND",
	"PIPE_SUSPEND",
	"SEMAPHORE_SUSPEND",
	"EVENT_SUSPEND",
	"PARTITION_SUSPEND",
	"MEMORY_SUSPEND",
	"DRIVER_SUSPEND",
	"FINISHED",
	"TERMINATED"
};

static const char yes[] = "Yes";
static const char no[] = "No";

task* task_info(void* task_ptr)
{
	task* t = malloc(sizeof(task));
	memset(t->name,0,10);
	t->task_ptr = task_ptr;
	TCF_Task_Information(task_ptr,t->name,&t->status,&t->scheduled_count,&t->priority,&t->preempt,&t->time_slice,&t->stack_base,&t->stack_size,&t->minimum_stack);
	
	return t;
}

const char* task_preempt(int preempt)
{
	if(preempt == 10)
		return yes;
	return no;
}

entry* task_entries_create(void* pointer_list[], unsigned count)
{
	entry* e = malloc(count*sizeof(entry));
	
	unsigned i;
	for(i = 0; i < count; i++)
	{
		task* t = task_info(pointer_list[i]);
		sprintf(e[i].text,"%-10s|%-2d|%-17s|%d",t->name,t->status,NU_STATUS[t->status],t->priority);
		free(t);
	}
	
	return e;
}

list2* task_list_create(void* pointer_list[])
{
	list2* t = malloc(sizeof(list2));
	t->count = TCF_Task_Pointers(pointer_list,100);
	t->entries = task_entries_create(pointer_list,t->count);
	t->list = create_list(0,24,25,t->entries,t->count);
	
	return t;
}

void display_task_info_screen(unsigned int selection, void* pointer_list[])
{
	task* tsk = task_info(pointer_list[selection]);
	do
	{
		nio_scrbuf_clear();
		
		nio_grid_puts(0,0,0,0,"Task information",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_printf(0,0,0,1,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Name: %s",tsk->name);
		nio_grid_printf(0,0,0,2,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Status: %d (%s)",tsk->status,NU_STATUS[tsk->status]);
		nio_grid_printf(0,0,0,3,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Scheduled count: %d",tsk->scheduled_count);
		nio_grid_printf(0,0,0,4,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Priority: %d",tsk->priority);
		nio_grid_printf(0,0,0,5,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Preempt: %d (%s)",tsk->preempt,task_preempt(tsk->preempt));
		nio_grid_printf(0,0,0,6,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Time slice: %d",tsk->time_slice);
		nio_grid_printf(0,0,0,7,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Stack base: 0x%p",tsk->stack_base);
		nio_grid_printf(0,0,0,8,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Stack size: 0x%X",tsk->stack_size);
		nio_grid_printf(0,0,0,9,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Minimum stack: 0x%X",tsk->minimum_stack);
		
		nio_grid_puts(0,0,0,11,"[ESC] Back",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,12,"[1] Terminate",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		
		nio_scrbuf_flip();
		wait_key_pressed();
		
		if(isKeyPressed(KEY_NSPIRE_1))
		{
			TCC_Terminate_Task(pointer_list[selection]);
			break;
		}
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	free(tsk);
}

void display_tasks_screen(void)
{
	void* pointer_list[100];
	
	list2* t = task_list_create(pointer_list);
	
	do
	{
		if(isKeyPressed(KEY_NSPIRE_1))
			list2_refresh(t,pointer_list,&task_list_create);
		
		int selection = update_list(t->list);
		if(selection != -1)
		{
			display_task_info_screen(selection,pointer_list);
			list2_refresh(t,pointer_list,&task_list_create);
		}
		
		nio_scrbuf_clear();
		
		nio_grid_printf(0,0,0,0,NIO_COLOR_WHITE,NIO_COLOR_BLACK,"Manage tasks (showing %d of %d)",t->count,TCF_Established_Tasks());
		nio_grid_puts(0,0,0,1, " Name      |S |Status           |P",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,2, "-----------+--+-----------------+--------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,28,"-----------+--+-----------------+--------------------",NIO_COLOR_WHITE,NIO_COLOR_BLACK);
		nio_grid_puts(0,0,0,29,"[1] Refresh [ENTER] Task info [ESC] Exit",NIO_COLOR_WHITE,NIO_COLOR_BLACK);

		draw_list(t->list);
		
		nio_scrbuf_flip();
		wait_key_pressed();
	} while(!isKeyPressed(KEY_NSPIRE_ESC));
	
	list2_free(t);
}