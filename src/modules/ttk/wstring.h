#ifndef TTK_WSTRING_H
#define TTK_WSTRING_H

#include "ttk.h"

typedef struct wstring_t {
    wchar_t* string;
    size_t wchars_n;
} wstring_t;

extern wstring_t*   wstring_init(void);
/*                  wstring_init_from() generic below */
extern wstring_t*   wstring_init_from_char(char* src, size_t begin, size_t end);
extern wstring_t*   wstring_init_from_wstring(wstring_t* src, size_t begin, size_t end);
extern void         wstring_free(wstring_t* wstr);
extern wchar_t      wstring_wchar_at(wstring_t* wstr, size_t i);
extern wstring_t*   wstring_cat(wstring_t* wstr1, wstring_t* wstr2);
extern wstring_t*   wstring_cat_arbitrary(wstring_t* wstr1, size_t begin1, size_t end1, wstring_t* wstr2, size_t begin2, size_t end2);
extern bool         wstring_compare(wstring_t* wstr1, wstring_t* wstr2);
/*                  wstring_cat_to() generic below */
extern void         wstring_cat_to_from_char(wstring_t* dest, char* src);
extern void         wstring_cat_to_from_wstring(wstring_t* dest, wstring_t* src);

#define             wstring_cat_to(dest, src) _Generic((str), char*: wstring_cat_to_from_char(dest, src), wstring_t*: wstring_cat_to_from_wstring(dest, src))
#define             wstring_init_from(src, begin, end) _Generic((str), char*: wstring_init_from_char(src, begin, end), wstring_t*: wstring_init_from_wstring(src, begin, end))

#endif