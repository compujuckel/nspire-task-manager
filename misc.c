#include "misc.h"

int nio_grid_printf(const int offset_x, const int offset_y, const int x, const int y, const unsigned char bgColor, const unsigned char textColor, const char* format, ...)
{
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    __builtin_va_list arglist;
    __builtin_va_start(arglist,format);
    vsprintf(buf,format,*(char **)&arglist);
    nio_grid_puts(offset_x, offset_y, x, y, buf, bgColor, textColor);
    __builtin_va_end(arglist);
    return strlen(buf);
}