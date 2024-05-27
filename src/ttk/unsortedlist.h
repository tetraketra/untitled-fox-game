#ifndef TTK_UNSORTEDLIST_H
#define TTK_UNSORTEDLIST_H

#include <string.h>
#include <stddef.h>
#include "macroutils.h"

/* 
    Unsorted list. 
    Uses array doubling when it runs out of space. 
*/
typedef struct ulist_t {
    void* items; /* Pointer to an array of items. */
    void (*item_pre_delete)(void*); /* Optional pre-delete function for each item. Should free allocated members. */
    size_t bytes; /* Byte size of an item. */
    size_t count; /* Total number of items in the array. */
    size_t capacity; /* Current maximum capacity of the array. */
    void* _next_insert_loc;
    byte* _ref_block;
} ulist_t;

ulist_t*    ulist_init(size_t bytes, void (*item_pre_delete)(void*));
void*       ulist_get(ulist_t* ulist, size_t index);
void        ulist_insert(ulist_t* ulist, void* item);
void        ulist_delete(ulist_t* ulist, size_t index);
void        ulist_free(ulist_t* ulist);

#endif