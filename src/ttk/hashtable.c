#include "hashtable.h"
#include "hexdump.h"

/* 
    FNV-1a hash function.

    @param `key`: The key to hash.
    @param `key_sb`: The size of the key in bytes.

    @returns Hashed `uint64_t`.

    @note https://en.wikipedia.org/wiki/Hash_table#Separate_chaining
*/
uint64_t hash_fnv1a(void* key, size_t key_sb) {
    uint64_t hash = 0xcbf29ce484222325;
    
    for (size_t byte = 0; byte < key_sb; byte++) {
        hash = (hash ^ ((uint8_t*)key)[byte]) * 0x100000001b3;
    }

    return hash;
}

/* 
    Initializes a hash table with `buckets_n` buckets on the heap.
    Open hashing with separate chaining.
    Technically values can be different sizes.
    Keys *must* be the same size. 
    
    @param `buckets_n`: The number of buckets.
    @param `key_sb`: The size of the keys in bytes. 

    @returns Pointer to the new `hashtable_t`.

    @note https://en.wikipedia.org/wiki/Hash_table#Separate_chaining
*/
hashtable_t* hashtable_init(size_t buckets_n, size_t key_sb) {
    hashtable_t* htable = malloc(sizeof(hashtable_t));
    htable->buckets = calloc(buckets_n, sizeof(hashtable_entry_t));
    htable->buckets_n = buckets_n;
    htable->entries_n = 0;
    htable->key_sb = key_sb;

    return htable;
}

void* hashtable_get(hashtable_t* htable, void* key) {
    hashtable_entry_t* entry = &(
        htable->buckets[hash_fnv1a(key, htable->key_sb) % htable->buckets_n]
    );

    for (size_t it = -1; it < htable->entries_n; it++) {

        /* If you've found the correct entry, return its value. */
        if (MEM_EQ(entry->key, key, htable->key_sb)) {
            return entry->val; /* done */ /* found */
        }

        /* Move to the next entry, or return NULL if there isn't one. */
        if (entry->next != NULL) {
            entry = entry->next;
        } else {
            return NULL; /* done */ /* didn't find */
        }
    }    

    DEBUG("Maximum iteration depth reached in hash table %p search of key %p.\n", htable, key);
    hex_dump(stderr, key, htable->key_sb, "key");
    return NULL;
}

/*
    Sets an entry in the hash table. 
    If the key already exists in the table, its value will be overwritten.
    
    @param `htable`: The hash table.
    @param `key`: The key to set the value of.
    @param `val`: The value to set.
    @param `val_sb`: The size of the value to set in bytes.

    @note The keys *must* be the same size in bytes across the entire table.
*/
void hashtable_set(hashtable_t* htable, void* key, void* val, size_t val_sb) {
    hashtable_entry_t* entry = &(
        htable->buckets[hash_fnv1a(key, htable->key_sb) % htable->buckets_n]
    );

    for (size_t it = -1; it < htable->entries_n; it++) {

        /* If the entry is empty, copy everything over. */
        if (entry->key == NULL) {
            entry->key = malloc(htable->key_sb);
            memcpy(entry->key, key, htable->key_sb);

            FREE(entry->val);
            entry->val = malloc(val_sb);
            memcpy(entry->val, val, val_sb);

            entry->val_sb = val_sb;

            htable->entries_n++;

            return; /* done */ /* written fresh */
        }

        /* If entry exists for this key, overwrite the value. */
        if (MEM_EQ(entry->key, key, htable->key_sb)) {
            FREE(entry->val);
            entry->val = malloc(val_sb);
            memcpy(entry->val, val, val_sb);
            
            entry->val_sb = val_sb;

            return; /* done */ /* overwritten */
        } 

        /* Move to the next entry, creating one (zeroed) if needed. */
        if (entry->next == NULL) {
            entry->next = calloc(1, sizeof(hashtable_entry_t));
        }   entry = entry->next;
    }

    DEBUG("Maximum iteration depth reached in hash table %p search of key %p.\n", htable, key);
    hex_dump(stderr, key, htable->key_sb, "key");
    return;
}