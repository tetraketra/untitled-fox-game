#ifndef TTK_WSTRING_H
#define TTK_WSTRING_H

#include "ttk.h"

typedef struct wstring_t {
    wchar_t* string;
    size_t wchars_n;
} wstring_t;

extern wstring_t*   wstring_init(void);
extern void         wstring_free(wstring_t* wstr);
extern wstring_t*   wstring_concatenate(wstring_t* wstr1, wstring_t* wstr2);
extern wstring_t*   wstring_combine(wstring_t* wstr1, size_t start1, size_t end1, wstring_t* wstr2, size_t start2, size_t end2);
extern bool         wstring_compare(wstring_t* wstr1, wstring_t* wstr2);
extern wchar_t      wstring_wchar_at(wstring_t* wstr, size_t i);

#define ONE(src)               _Generic((src), char*: wstring_from_cstring(src), wstring_t*: wstring_from_wstring(src), default: GENERIC_DEFAULT)
#define THREE(src, start, end) _Generic((src), char*: wstring_from_cstring_slice(src, start, end), wstring_t*: wstring_from_wstring_slice(src, start, end), default: GENERIC_DEFAULT)
#define WSTRING_FROM_IMPL_CHOOSER(src, arg1, arg2, func, ...) func
#define WSTRING_FROM_IMPL(src, ...) WSTRING_FROM_IMPL_CHOOSER(src, ##__VA_ARGS__, THREE, COMPILE_FAIL, ONE)(src, ##__VA_ARGS__)
/* Generic selection from `wstring_from_[cstring|wstring][_slice]`. See individual documentation. */
#define             wstring_from(src, ...) WSTRING_FROM_IMPL(src, ##__VA_ARGS__)
extern wstring_t*   wstring_from_cstring(char* src);
extern wstring_t*   wstring_from_cstring_slice(char* src, size_t start, size_t end);
extern wstring_t*   wstring_from_wstring(wstring_t* src);
extern wstring_t*   wstring_from_wstring_slice(wstring_t* src, size_t start, size_t end);

#define TWO(dest, src)              _Generic((src), char*: wstring_append_cstring, wstring_t*: wstring_append_wstring, char: wstring_append_char, wchar_t: wstring_append_wchar, default: GENERIC_DEFAULT)(dest, src)
#define FOUR(dest, src, start, end) _Generic((src), char*: wstring_append_cstring_slice, wstring_t*: wstring_append_wstring_slice, default: GENERIC_DEFAULT)(dest, src, start, end)
#define WSTRING_APPEND_IMPL_CHOOSER(dest, src, arg1, arg2, func, ...) func
#define WSTRING_APPEND_IMPL(dest, src, ...) WSTRING_APPEND_IMPL_CHOOSER(dest, src, ##__VA_ARGS__, FOUR, COMPILE_FAIL, TWO)(dest, src, ##__VA_ARGS__)
/* Generic selection from `wstring_from_[cstring|wstring|char|wchar][_slice]`. See individual documentation. */
#define             wstring_append(dest, src, ...) WSTRING_APPEND_IMPL(dest, src, ##__VA_ARGS__)
extern void         wstring_append_cstring(wstring_t* dest, char* src);
extern void         wstring_append_cstring_slice(wstring_t* dest, char* src, size_t start, size_t end);
extern void         wstring_append_wstring(wstring_t* dest, wstring_t* src);
extern void         wstring_append_wstring_slice(wstring_t* dest, wstring_t* src, size_t start, size_t end);
extern void         wstring_append_char(wstring_t* dest, char src);
extern void         wstring_append_wchar(wstring_t* dest, wchar_t src);

#endif