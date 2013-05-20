#include <os.h>
#include <nspireio.h>

#ifndef MISC_H
#define MISC_H

int nio_grid_printf(const int offset_x, const int offset_y, const int x, const int y, const unsigned char bgColor, const unsigned char textColor, const char* format, ...);

#endif