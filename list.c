#include "list.h"

list* create_list(int x, int y, int length, entry* entries, unsigned entry_count)
{
	list* l = malloc(sizeof(list));
	l->x = x;
	l->y = y;
	l->length = length;
	l->entries = entries;
	l->entry_count = entry_count;
	l->offset = 0;
	l->cursor_pos = 0;
	
	return l;
}

void draw_list(list* l)
{
	nio_grid_putc(l->x,l->y,0,l->cursor_pos,'>',NIO_COLOR_WHITE,NIO_COLOR_BLACK);
	
	unsigned i, j = 0;
	for(i = l->offset; i < l->offset+l->length && i < l->entry_count; i++)
	{	
		nio_grid_puts(l->x,l->y,1,j++,l->entries[i].text,NIO_COLOR_WHITE,NIO_COLOR_BLACK);
	}
}

int update_list(list* l)
{
	if(isKeyPressed(KEY_NSPIRE_UP))
	{
		if(l->cursor_pos > 0)
			l->cursor_pos--;
		else if(l->offset > 0)
			l->offset--;
	}

	if(isKeyPressed(KEY_NSPIRE_DOWN))
	{
		if(l->cursor_pos < l->length-1 && l->offset+l->cursor_pos < l->entry_count-1)
			l->cursor_pos++;
		else if(l->offset < l->entry_count && l->offset+l->cursor_pos < l->entry_count-1)
			l->offset++;
	}
	
	if(isKeyPressed(KEY_NSPIRE_ENTER))
		return l->offset+l->cursor_pos;
	
	return -1;
}
