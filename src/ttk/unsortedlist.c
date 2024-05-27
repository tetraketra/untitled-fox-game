#include "unsortedlist.h"

/* 
    Initialize an unsorted list with one capacity and zero elements. 

    @param `bytes`: The byte size of each element.
    @param `item_pre_delete`: An optional function to call on an item before it is deleted.

    @returns A pointer to an unsorted list.
*/
ulist_t* ulist_init(size_t bytes, void (*item_pre_delete)(void*)) {
    ulist_t* ulist = malloc(sizeof(ulist_t));
    ulist->item_pre_delete = item_pre_delete;
    ulist->items = calloc(1, bytes);
    ulist->bytes = bytes;
    ulist->capacity = 1;
    ulist->count = 0;
    
    ulist->_next_insert_loc = ulist->items;
    ulist->_ref_block = calloc(bytes, sizeof(byte));

    return ulist;
}

/* 
    Get a pointer to an item at `index` in an unsorted list. 
    This exists at all because `ulist_t` uses void pointers.

    @param `ulist`: Take a guess.
    @param `index`: The index you would like to fetch.

    @returns A pointer to the item at `index`.
    @returns NULL if `index` is out of bounds or the `ulist` doesn't exist.

    @note During defragmentation (on deletion), data can move; references, invalidated.
*/
inline void* ulist_get(ulist_t* ulist, size_t index) {
    if (ulist == NULL || index >= ulist->capacity) {
        return NULL;
    }

    return ulist->items + index*ulist->bytes;
}

/* 
    Copies the data at `item` into an unsorted list at the next available index. 
    Doubles the capacity if necessary. 

    @param `ulist`: Take a guess.
    @param `item`: The item whose data to copy into the unsorted list
*/
void ulist_insert(ulist_t* ulist, void* item) {
    if (ulist == NULL) {
        return;
    }

    memcpy(ulist->_next_insert_loc, item, ulist->bytes);

    if (++(ulist->count) == ulist->capacity) { /* Double the capacity if necessary. */
        ptrdiff_t _nil_offset =  ulist->_next_insert_loc - ulist->items;

        ulist->items = realloc(ulist->items, ulist->bytes*ulist->capacity*2);
        memset(ulist->items + ulist->bytes*ulist->capacity, 0, ulist->bytes*(ulist->capacity));

        ulist->capacity *= 2;
        ulist->_next_insert_loc = ulist->items + _nil_offset;
    }

    while (memcmp(ulist->_next_insert_loc, ulist->_ref_block, ulist->bytes)) { /* Advance the next open insert location. */
        ulist->_next_insert_loc += ulist->bytes;
    }
}

/*
    Deletes an item at `index` in an unsorted list.
    Frees the item using `item_pre_delete` if it exists!
    Defragments and shrinks the list if necessary.

    @param `ulist`: Take a guess.
    @param `index`: The index you would like to delete.

    @note FIXME: Might need a bool flag arg to indicate if `item_pre_delete` should be called?
*/

typedef struct ulist_testitem_t {
    int value;
    int* alloced_value;
} ulist_testitem_t;
void ulist_delete(ulist_t* ulist, size_t index) {
    if (ulist == NULL || index >= ulist->capacity) {
        return;
    }

    void* item = ulist_get(ulist, index);

    if (item == NULL || !memcmp(item, ulist->_ref_block, ulist->bytes)) {
        return;
    }

    if (ulist->item_pre_delete != NULL) {
        ulist->item_pre_delete(item);
    }

    memset(item, 0, ulist->bytes);
    
    if (item < ulist->_next_insert_loc) { 
        ulist->_next_insert_loc = item;
    }
    
    ulist->count--;
    
    if (ulist->count < ulist->capacity/4) { 
        void* last_item = ulist->items + ulist->bytes*(ulist->capacity-1);
        while (!memcmp(last_item, ulist->_ref_block, ulist->bytes)) { /* move the last_item ptr to the last item */
            last_item -= ulist->bytes;
        } 

        while (ulist->_next_insert_loc < last_item) { /* while there are gaps in the list, */
            memcpy(ulist->_next_insert_loc, last_item, ulist->bytes); /* move the item */
            memset(last_item, 0, ulist->bytes);

            while (memcmp(ulist->_next_insert_loc, ulist->_ref_block, ulist->bytes)) { /* advance the next insert location. */
                ulist->_next_insert_loc += ulist->bytes;
            }

            while (!memcmp(last_item, ulist->_ref_block, ulist->bytes)) { /* move the last_item ptr to the next last item (from right to left), */
                last_item -= ulist->bytes;
            } 
        }

        ptrdiff_t _nil_offset =  ulist->_next_insert_loc - ulist->items;

        ulist->items = realloc(ulist->items, ulist->bytes*ulist->capacity/4);

        ulist->capacity /= 4;
        ulist->_next_insert_loc = ulist->items + _nil_offset;
    }
}

/* 
    Frees an unsorted list and all its items.

    @param `ulist`: Take a guess.
*/
void ulist_free(ulist_t* ulist) {
    if (ulist == NULL) {
        return;
    }

    if (ulist->item_pre_delete != NULL) {
        size_t items_pre_deleted = 0;
        void* loc = ulist->items;
        void* endloc = ulist->items + ulist->bytes*(ulist->capacity-1);

        while (items_pre_deleted < ulist->count && loc < endloc) {
            if (memcmp(loc, ulist->_ref_block, ulist->bytes)) {
                ulist->item_pre_delete(loc);
                items_pre_deleted++;
            }

            loc += ulist->bytes;
        }
    }

    FREE(ulist->_ref_block);
    FREE(ulist->items);
    FREE(ulist);
}

