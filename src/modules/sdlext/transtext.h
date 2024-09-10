#ifndef SDLEXT_TRANSTEXT_H
#define SDLEXT_TRANSTEXT_H

#include "toolkit/toolkit.h"

/* Total number of language slots `sdlext::transtext` supports. */
#define TRANSTEXT_MAX_LANGUAGES 256
#define TRANSTEXT_LANGNAME_MAXLEN 31

extern void transtext_lang_register(const char* lang);
extern bool transtext_lang_select(const char* lang);

#endif