#ifndef TTK_HEXDUMP_H
#define TTK_HEXDUMP_H

#include "ttk.h"

extern void hex_dump(FILE* stream, void* buffer, size_t buf_sb, char* desc);

#endif