#ifndef TTK_HASHTABLE_H
#define TTK_HASHTABLE_H

#include "ttk.h"
#include "hexdump.h"

/*
    === INFO ===
    1. Open hashing with separate chaining.
    2. Keys *must* be the same size, but values may be different sizes.
    3. All keys and values are...
        - copied into the hash table.
        - freed when the hash table is freed (or their specific entry is freed).
        - stored as void pointers.
    4. The built-in hash function is FNV-1a.
*/

typedef struct hashtable_entry_t hashtable_entry_t;
typedef struct hashtable_entry_t {
    void* key; /* The unhashed key. */
    void* val; /* The stored value. */
    size_t val_sb; /* The size of the value in bytes. */
    hashtable_entry_t* next; /* Next entry in the chain. */
} hashtable_entry_t;

typedef struct hashtable_t {
    hashtable_entry_t* buckets; /* Array of head entries. Not true linked list heads (for speed reasons). */
    size_t buckets_n; /* Length of `buckets` head entries array. */
    size_t entries_n; /* Count of items across all buckets. */
    size_t key_sb; /* Size of all entries' unhashed key type in bytes.*/
} hashtable_t;

extern uint64_t     hash_fnv1a(void* key, size_t key_sb);
extern hashtable_t* hashtable_init(size_t buckets_n, size_t key_sb);
extern void*        hashtable_get(hashtable_t* htable, void* key);
extern void         hashtable_set(hashtable_t* htable, void* key, void* val, size_t val_sb);
extern void         hashtable_rid(hashtable_t* htable, void* key);
extern bool         hashtable_has(hashtable_t* htable, void* key);
extern void         hashtable_free(hashtable_t* htable);
extern float        hashtable_calc_load_factor(hashtable_t* htable);
extern float        hashtable_calc_bucket_usage(hashtable_t* htable);

#endif