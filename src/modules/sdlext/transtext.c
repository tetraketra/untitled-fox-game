#include "transtext.h"

static char languages[TRANSTEXT_MAX_LANGUAGES][TRANSTEXT_LANGNAME_MAXLEN + 1]; /* Language names, zero-terminated. */
static uint64_t n_langs_registered;
static uint64_t cur_lang_i;

/* 
    Registers a language with `sdlext::transtext` 
    for use with translated text.

    @param lang zero-terminated langauge to register, 
    e.g. "English" literal or "English\0" non-literal.
*/
void transtext_lang_register(const char* lang) {
    strncpy(languages[n_langs_registered], lang, TRANSTEXT_LANGNAME_MAXLEN);
    languages[n_langs_registered++][TRANSTEXT_LANGNAME_MAXLEN] = '\0';
}

/*
    Selects a language for `sdlext::transtext` to use.

    @param lang zero-terminated language to select.
    
    @returns `true` if language selected, `false` if not able to.
*/
bool transtext_lang_select(const char* lang) {
    /* Check if we're already on that language. */
    if (strncmp(lang, languages[cur_lang_i], TRANSTEXT_LANGNAME_MAXLEN) == 0) {
        return true; /* done */ /* already selected */
    }

    /* Simple linear search to find the chosen language. */
    for (size_t i; i < n_langs_registered; i++) {
        if (strncmp(lang, languages[i], TRANSTEXT_LANGNAME_MAXLEN) == 0) {
            cur_lang_i = i;
            return true; /* done */ /* found and selected*/
        }
    }

    /* No language found. */
    return false; /* done */ /* not found */
}