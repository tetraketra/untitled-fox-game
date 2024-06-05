#ifndef TTK_HEX_DUMP_H
#define TTK_HEX_DUMP_H

#include "macroutils.h"

extern void hex_dump(FILE* stream, void* buffer, size_t buf_sb, char* desc);

#endif