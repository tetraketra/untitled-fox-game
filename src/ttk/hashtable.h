#ifndef TTK_HASHTABLE_H
#define TTK_HASHTABLE_H

#include "macroutils.h"

typedef struct hashtable_entry_t hashtable_entry_t;
typedef struct hashtable_entry_t {
    void* key; /* Unhashed key. Treated as array of bytes of `key_sb` length. */
    void* val; /* The value. This needs to be cast to the correct type by the user. */
    size_t val_sb; /* Size of the value in bytes. */
    // hashtable_entry_t* prev;
    hashtable_entry_t* next; 
} hashtable_entry_t;

typedef struct hashtable_t {
    hashtable_entry_t* buckets; /* Array of head linked-list entries, one for each bucket. */
    size_t buckets_n; /* Count of buckets, empty or full. Length of `buckets` array. */
    size_t entries_n; /* Count of items across all buckets. */
    size_t key_sb; /* Size of each entry's unhashed key in bytes. */
} hashtable_t;

#endif 