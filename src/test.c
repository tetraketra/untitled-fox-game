/* === UNSORTED LIST === */
#include "ttk/unsortedlist.h"

typedef struct ulist_testitem_t {
    int value;
    int* alloced_value;
} ulist_testitem_t;

static void ulist_testitem_pre_delete(void* item) {
    if (((ulist_testitem_t*)item)->alloced_value != NULL) {
        FREE(((ulist_testitem_t*)item)->alloced_value);
    }
}

void __attribute__((constructor)) test_unsortedlist(void) {
    ulist_testitem_t* item1 = malloc(sizeof(ulist_testitem_t));
    item1->value = 5;
    item1->alloced_value = malloc(sizeof(int));
    *(item1->alloced_value) = 500;

    ulist_testitem_t* item2 = malloc(sizeof(ulist_testitem_t));
    item2->value = 6;
    item2->alloced_value = malloc(sizeof(int)); 
    *(item2->alloced_value) = 600;

    /* Initialize an unsorted list with defaults (one capacity and zero elements). */
    ulist_t* ulist = ulist_init(sizeof(ulist_testitem_t), &ulist_testitem_pre_delete);
    RUNTIME_ASSERT(ulist->bytes == sizeof(ulist_testitem_t)); // Byte size copied.
    RUNTIME_ASSERT(ulist->capacity == 1); // Capacity initialized to 1.
    RUNTIME_ASSERT(ulist->count == 0); // Count initialized to 0.
    RUNTIME_ASSERT(ulist->item_pre_delete == &ulist_testitem_pre_delete); // Pre-delete function copied.
    RUNTIME_ASSERT(ulist->_next_insert_loc == ulist->items); // _next_insert_loc initialized to beginning of items array.

    /* Insert an item, which should go to position #0. */
    ulist_insert(ulist, item1);
    RUNTIME_ASSERT(ulist->count == 1); // Count increased by 1.
    RUNTIME_ASSERT(ulist->capacity == 2); // Capacity doubled.
    RUNTIME_ASSERT(ulist->_next_insert_loc == ulist_get(ulist, 1)); // _next_insert_loc moved to position #1.

    /* Get the item at position #0 and verify position #1 now exists (because of doubling) and is empty. */
    RUNTIME_ASSERT(((ulist_testitem_t*)ulist_get(ulist, 0))->value == 5); // Item at position #0 has value 5.
    RUNTIME_ASSERT(*((ulist_testitem_t*)ulist_get(ulist, 0))->alloced_value == 500); // Item at position #0 has value 500.
    RUNTIME_ASSERT(!memcmp(ulist_get(ulist, 1), ulist->_ref_block, ulist->bytes)); // Item at position #1 is empty.

    /* Insert another item, now to position #1. */
    ulist_insert(ulist, item2);
    RUNTIME_ASSERT(ulist->count == 2); // Count increased by 1.
    RUNTIME_ASSERT(ulist->capacity == 4); // Capacity doubled.
    RUNTIME_ASSERT(ulist->_next_insert_loc == ulist_get(ulist, 2)); // _next_insert_loc moved to position #2.
    RUNTIME_ASSERT(memcmp(ulist_get(ulist, 0), ulist_get(ulist, 1), ulist->bytes)); // Item at position #0 is not equal to item at position #1.

    /* Delete an item. */
    ulist_delete(ulist, 0);
    RUNTIME_ASSERT(ulist->count == 1); // Count decreased by 1.
    RUNTIME_ASSERT(ulist->capacity == 4); // Capacity remained the same.
    RUNTIME_ASSERT(ulist->_next_insert_loc == ulist_get(ulist, 0)); // _next_insert_loc moved to position #0.
    RUNTIME_ASSERT(((ulist_testitem_t*)ulist_get(ulist, 0))->value == 0); // Item at position #0 has no value.
    RUNTIME_ASSERT(((ulist_testitem_t*)ulist_get(ulist, 0))->alloced_value == NULL); // Item at position #0 has no value.
    RUNTIME_ASSERT(!memcmp(ulist_get(ulist, 0), ulist->_ref_block, ulist->bytes)); // Item at position #1 is empty.

    /* Insert 128 items as a stress test. */
    for(size_t i = 0; i < 128; i++) {
        ulist_testitem_t* item = malloc(sizeof(ulist_testitem_t));
        item->value = i+7;
        item->alloced_value = malloc(sizeof(int));
        *(item->alloced_value) = (i+7)*100;

        ulist_insert(ulist, item);

        FREE(item);
    }
    RUNTIME_ASSERT(ulist->count == 129); // Count increased to 128.
    RUNTIME_ASSERT(ulist->capacity == 256); // Capacity increased to 256.
    RUNTIME_ASSERT(ulist->_next_insert_loc == ulist_get(ulist, 129)); // _next_insert_loc moved to position #129.

    /* Delete items from the middle to trigger defragmentation. */
    for(size_t i = 30; i < 100; i++) {
        ulist_delete(ulist, i); // The last 5 attempts fail for being out of bounds.
    }
    RUNTIME_ASSERT(ulist->count == 63); // Count decreased to 64.
    RUNTIME_ASSERT(ulist->capacity == 64); // Capacity decreased to 64.

    /* Free the list. */ 
    ulist_free(ulist); // This test passes if no memory is leaked according to fsanitizer.

    /* Testing object cleanup. */
    FREE(item1);
    FREE(item2);
}