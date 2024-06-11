#ifndef TTK_HASHTABLE_H
#define TTK_HASHTABLE_H

#include "ttk.h"
#include "hexdump.h"

typedef struct hashtable_entry_t hashtable_entry_t;
typedef struct hashtable_entry_t {
    void* key; /* Unhashed key. Treated as array of bytes of `key_sb` length. */
    void* val; /* The value. This needs to be cast to the correct type by the user. */
    size_t val_sb; /* Size of the value in bytes. */
    hashtable_entry_t* next; /* Next entry in the linked list (separate chaining). */
} hashtable_entry_t;

typedef struct hashtable_t {
    hashtable_entry_t* buckets; /* Array of head linked-list entries, one for each bucket. */
    size_t buckets_n; /* Count of buckets, empty or full. Length of `buckets` array. */
    size_t entries_n; /* Count of items across all buckets. */
    size_t key_sb; /* Size of each entry's unhashed key in bytes. */
} hashtable_t;

extern uint64_t     hash_fnv1a(void* key, size_t key_sb);
extern hashtable_t* hashtable_init(size_t buckets_n, size_t key_sb);
extern void*        hashtable_get(hashtable_t* htable, void* key);
extern void         hashtable_set(hashtable_t* htable, void* key, void* val, size_t val_sb);
extern void         hashtable_rid(hashtable_t* htable, void* key);
extern bool         hashtable_has(hashtable_t* htable, void* key);
extern void         hashtable_free(hashtable_t* htable);
extern float        hashtable_calc_load_factor_all(hashtable_t* htable);
extern float        hashtable_calc_load_factor_buckets(hashtable_t* htable);

#endif 