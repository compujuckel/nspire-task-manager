#include <os.h>
#include <nspireio.h>

#ifndef LIST_H
#define LIST_H

typedef struct entry
{
	char text[53];
} entry;

typedef struct list
{
	unsigned x;
	unsigned y;
	unsigned length;
	entry* entries;
	unsigned entry_count;
	unsigned cursor_pos;
	unsigned offset;
} list;

list* create_list(int x, int y, int length, entry* entries, unsigned entry_count);
void draw_list(list* l);
int update_list(list* l);

#endif