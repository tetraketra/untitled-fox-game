#include "dlinkedlist.h"


/*
    Initializes a doubly linked list entry on the heap.

    @returns Pointer to the new `dlinkedlist_entry_t`.

    @internal
*/
static inline dlinkedlist_entry_t* dlinkedlist_entry_init(void* data, size_t data_sb) {
    RUNTIME_ASSERT(data != NULL);
    RUNTIME_ASSERT(data_sb > 0);

    dlinkedlist_entry_t* entry = calloc(1, sizeof(dlinkedlist_entry_t));

    entry->data = malloc(data_sb);
    memcpy(entry->data, data, data_sb);
    entry->data_sb = data_sb;

    return entry;
}


/*
    Push the first entry to a doubly linked list.
    This will be both the head and tail.

    @internal
*/
static inline void dlinkedlist_push_to_empty(dlinkedlist_t* dlinkedlist, void* data, size_t data_sb) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    RUNTIME_ASSERT(data != NULL);
    RUNTIME_ASSERT(data_sb > 0);

    dlinkedlist_entry_t* entry = dlinkedlist_entry_init(data, data_sb);

    dlinkedlist->head = entry;
    dlinkedlist->tail = entry;
    dlinkedlist->entries_n++;
}


/*
    Initializes a doubly linked list on the heap.
    Values may be different sizes.

    @returns Pointer to the new `dlinkedlist_t`.
*/
dlinkedlist_t* dlinkedlist_init(void) {
    dlinkedlist_t* dlinkedlist = malloc(sizeof(dlinkedlist_t));

    dlinkedlist->head = NULL;
    dlinkedlist->tail = NULL;
    dlinkedlist->entries_n = 0;

    return dlinkedlist;
}


/*
    Frees a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.
*/
void dlinkedlist_free(dlinkedlist_t* dlinkedlist) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    
    /* Traverse forward, freeing as you go. */
    dlinkedlist_entry_t* head = dlinkedlist->head;

    while (head) {
        dlinkedlist_entry_t* next = head->next;
        FREE(head->data);
        FREE(head);
        head = next;
    }

    /* Free the container itself. */
    FREE(dlinkedlist);
}


/*
    Pushes a new data entry to the head of a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.
    @param `data`: The data to push.
    @param `data_sb`: The size of the data in bytes.
*/
void dlinkedlist_push_head(dlinkedlist_t* dlinkedlist, void* data, size_t data_sb) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    RUNTIME_ASSERT(data != NULL);
    RUNTIME_ASSERT(data_sb > 0);

    /* Push special if list is empty, otherwise normal. */
    if (dlinkedlist->entries_n == 0) {
        dlinkedlist_push_to_empty(dlinkedlist, data, data_sb);
    } else {
        dlinkedlist_entry_t* entry = dlinkedlist_entry_init(data, data_sb);

        entry->next = dlinkedlist->head;
        dlinkedlist->head->prev = entry;
        dlinkedlist->head = entry;
        dlinkedlist->entries_n++;
    }
}


/*
    Pushes a new data entry to the tail of a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.
    @param `data`: The data to push.
    @param `data_sb`: The size of the data in bytes.
*/
void dlinkedlist_push_tail(dlinkedlist_t* dlinkedlist, void* data, size_t data_sb) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    RUNTIME_ASSERT(data != NULL);
    RUNTIME_ASSERT(data_sb > 0);

    /* Push special if list is empty, otherwise normal. */
    if (dlinkedlist->entries_n == 0) {
        dlinkedlist_push_to_empty(dlinkedlist, data, data_sb);
    } else {
        dlinkedlist_entry_t* entry = dlinkedlist_entry_init(data, data_sb);

        entry->prev = dlinkedlist->tail;
        dlinkedlist->tail->next = entry;
        dlinkedlist->tail = entry;
        dlinkedlist->entries_n++;
    }
}


/*
    Gets the value at a specific index in a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.
    @param `index`: The index of the value to get.

    @returns The value at the index as a void pointer, 
             or `NULL` if the index is out of bounds.
*/
void* dlinkedlist_get(dlinkedlist_t* dlinkedlist, size_t index) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    RUNTIME_ASSERT(index < dlinkedlist->entries_n);

    /* Empty list guard. */
    if (!dlinkedlist->entries_n) {
        return NULL; /* done */ /* didn't find (empty list) */
    }

    /* Traverse (backwards if faster). */
    dlinkedlist_entry_t* entry;
    if (index*2 < dlinkedlist->entries_n) {
        entry = dlinkedlist->head;

        for (size_t i = 0; i < index; i++) {
            entry = entry->next;
        }
    } else {
        entry = dlinkedlist->tail;

        for (size_t i = dlinkedlist->entries_n-1; i > index; i--) {
            entry = entry->prev;
        }
    }

    /* Return the data. */
    return entry->data; /* done */ /* found */
}


/*
    Sets the value at a specific index in a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.
    @param `index`: The index of the value to set.
*/
void dlinkedlist_set(dlinkedlist_t* dlinkedlist, size_t index, void* data, size_t data_sb) {
    RUNTIME_ASSERT(dlinkedlist != NULL);
    RUNTIME_ASSERT(index < dlinkedlist->entries_n);
    RUNTIME_ASSERT(data != NULL);
    RUNTIME_ASSERT(data_sb > 0);

    /* Empty list guard. */
    if (!dlinkedlist->entries_n) {
        return; /* done */ /* didn't find (empty list) */
    }

    /* Traverse (backwards if faster). */
    dlinkedlist_entry_t* entry;
    if (index*2 < dlinkedlist->entries_n) {
        entry = dlinkedlist->head;

        for (size_t i = 0; i < index; i++) {
            entry = entry->next;
        }
    } else {
        entry = dlinkedlist->tail;

        for (size_t i = dlinkedlist->entries_n-1; i > index; i--) {
            entry = entry->prev;
        }
    }


    /* Overwrite. */
    FREE(entry->data);
    entry->data = malloc(data_sb);
    memcpy(entry->data, data, data_sb);
    entry->data_sb = data_sb;

    /* Return. */
    return; /* done */ /* found and set */
}


/*
    Pops a value from the head of a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.

    @returns The popped value as a void pointer, or `NULL` if empty.
*/
void* dlinkedlist_pop_head(dlinkedlist_t* dlinkedlist) {
    RUNTIME_ASSERT(dlinkedlist != NULL);

    /* Empty list guard. */
    if (!dlinkedlist->entries_n) {
        return NULL; /* done */ /* didn't find (empty list) */
    }

    /* Extract the dlinkedlist's current head. */
    dlinkedlist_entry_t* old_head = dlinkedlist->head;
    dlinkedlist->entries_n--;

    /* Remove the current head from the dlinkedlist. */
    dlinkedlist->head = dlinkedlist->head->next;
    dlinkedlist->head->prev = NULL;
    if (!dlinkedlist->entries_n) { /* If this was the only entry, the tail is affected too. */
        dlinkedlist->tail = NULL;
    }

    /* Exctract the data from the old head. */
    void* data = old_head->data;
    FREE(old_head);

    /* Return the data. */
    return data; /* done */ /* found */
}


/*
    Pops a value from the tail of a doubly linked list.

    @param `dlinkedlist`: The doubly linked list.

    @returns The popped value as a void pointer, or `NULL` if empty.
*/
void* dlinkedlist_pop_tail(dlinkedlist_t* dlinkedlist) {
    RUNTIME_ASSERT(dlinkedlist != NULL);

    /* Empty list guard. */
    if (!dlinkedlist->entries_n) {
        return NULL; /* done */ /* didn't find (empty list) */
    }

    /* Extract the dlinkedlist's current head. */
    dlinkedlist_entry_t* old_tail = dlinkedlist->tail;
    dlinkedlist->entries_n--;

    /* Remove the current head from the dlinkedlist. */
    dlinkedlist->tail = dlinkedlist->tail->prev;
    dlinkedlist->tail->next = NULL;
    if (!dlinkedlist->entries_n) { /* If this was the only entry, the head is affected too. */
        dlinkedlist->head = NULL;
    }

    /* Exctract the data from the old head. */
    void* data = old_tail->data;
    FREE(old_tail);

    /* Return the data. */
    return data; /* done */ /* found */
}