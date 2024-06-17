#ifndef TTK_DLINKEDLIST_H
#define TTK_DLINKEDLIST_H

#include "ttk.h"

typedef struct dlinkedlist_entry_t dlinkedlist_entry_t;
typedef struct dlinkedlist_entry_t {
    dlinkedlist_entry_t* next;
    dlinkedlist_entry_t* prev;
    void* data;
    size_t data_sb;
} dlinkedlist_entry_t;

typedef struct dlinkedlist_t {
    dlinkedlist_entry_t* head;
    dlinkedlist_entry_t* tail;
    size_t entries_n;
} dlinkedlist_t;

extern dlinkedlist_t*   dlinkedlist_init(void);
extern void             dlinkedlist_push_head(dlinkedlist_t* dlinkedlist, void* data, size_t data_sb);
extern void             dlinkedlist_push_tail(dlinkedlist_t* dlinkedlist, void* data, size_t data_sb);
extern void*            dlinkedlist_pop_head(dlinkedlist_t* dlinkedlist);
extern void*            dlinkedlist_pop_tail(dlinkedlist_t* dlinkedlist);
extern void             dlinkedlist_free(dlinkedlist_t* dlinkedlist);
extern void*            dlinkedlist_get(dlinkedlist_t* dlinkedlist, size_t index);
extern void             dlinkedlist_set(dlinkedlist_t* dlinkedlist, size_t index, void* data, size_t data_sb);

#endif