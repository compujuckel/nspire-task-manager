#include <os.h>
#include <nspireio.h>
#include "list.h"
#include "misc.h"

#ifndef SETTINGS_H
#define SETTINGS_H

entry* settings_entries_create(unsigned count);
list2* settings_list_create();
void settings_list_refresh(list2* t);

void display_settings_screen(void);

#endif