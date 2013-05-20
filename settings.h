#include <os.h>
#include <nspireio.h>
#include "list.h"
#include "misc.h"

#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct settings_list
{
	entry* entries;
	list* list;
	unsigned count;
} settings_list;

entry* settings_entries_create(unsigned count);
settings_list* settings_list_create();
void settings_list_refresh(settings_list* t);

void display_settings_screen(void);

#endif