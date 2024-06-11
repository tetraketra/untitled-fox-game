#ifndef TTK_DLINKEDLIST_H
#define TTK_DLINKEDLIST_H

#include "ttk.h"

typedef struct dlinkedlist_entry_t dlinkedlist_entry_t;
typedef struct dlinkedlist_entry_t {
    void* val; /* The value in this entry. This needs to be cast to the correct type by the user. */
    size_t val_sb; /* Size of the value in bytes. */
    dlinkedlist_entry_t* next; /* Next entry in the dlinkedlist. */
    dlinkedlist_entry_t* prev; /* Previous entry in the dlinkedlist. */
} dlinkedlist_entry_t;

typedef struct dlinkedlist_t {
    dlinkedlist_entry_t* head; /* The head of the dlinkedlist. */
    dlinkedlist_entry_t* tail; /* The tail of the dlinkedlist. */
    size_t entries_n; /* Count of entries in the dlinkedlist. */
} dlinkedlist_t;

#endif