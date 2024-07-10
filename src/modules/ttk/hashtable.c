#include "hashtable.h"

/*
    FNV-1a hash function.

    @param `key`: The key to hash.
    @param `key_sb`: The size of the key in bytes.

    @returns Hashed `uint64_t`.
*/
uint64_t hash_fnv1a(void* key, size_t key_sb) {
    uint64_t hash = 0xcbf29ce484222325;

    for (size_t byte = 0; byte < key_sb; byte++) {
        hash = (hash ^ ((uint8_t*)key)[byte]) * 0x100000001b3;
    }

    return hash;
}

/*
    Initializes a hash table on the heap.
    Open hashing with separate chaining.
    Values may be different sizes.
    Keys *must* be the same size.

    @param `buckets_n`: The *constant* number of buckets (for now).
    @param `key_sb`: The size of the keys in bytes.

    @returns Pointer to the new `hashtable_t`.

    @note https://en.wikipedia.org/wiki/Hash_table#Separate_chaining
*/
inline hashtable_t* hashtable_init(size_t buckets_n, size_t key_sb) {
    hashtable_t* htable = malloc(sizeof(hashtable_t));
    htable->buckets = calloc(buckets_n, sizeof(hashtable_entry_t));
    htable->buckets_n = buckets_n;
    htable->entries_n = 0;
    htable->key_sb = key_sb;

    return htable;
}

/*
    Gets an entry from a hash table.

    @param `htable`: The hash table.
    @param `key`: The key whose value to get.

    @returns Pointer to the value, or `NULL` if not found.
*/
void* hashtable_get(hashtable_t* htable, void* key) {
    RUNTIME_ASSERT(htable != NULL);
    RUNTIME_ASSERT(key != NULL);

    /* Fetch the head entry. */
    hashtable_entry_t* entry = &(
        htable->buckets[hash_fnv1a(key, htable->key_sb) % htable->buckets_n]
    );

    /* Find the specific entry and operate accordingly. */
    for (size_t i = 0; i < htable->entries_n + 1; i++) {

        /* End of the chain. */
        if (entry->key == NULL) {
            return NULL; /* done */ /* didn't find */
        }

        /* Found entry with correct key. */
        if (MEM_EQ(entry->key, key, htable->key_sb)) {
            return entry->val; /* done */ /* found */
        }

        /* Next in chain, if exists. */
        if (entry->next != NULL) {
            entry = entry->next;
        } else {
            return NULL; /* done */ /* didn't find */
        }
    }

    /* If no early exit, something's wrong! */
    ERROR("Maximum iteration depth reached in hashtable_get, htable=%p key=%p.\n", htable, key);
    hex_dump(stderr, key, htable->key_sb, "key");
    return NULL;
}

/*
    Checks if an entry exists in a hash table.

    @param `htable`: The hash table.
    @param `key`: The key whose value to check.

    @returns `true` if the entry exists, `false` otherwise.
*/
inline bool hashtable_has(hashtable_t* htable, void* key) {
    return hashtable_get(htable, key) != NULL;
}

/*
    Calculates the load factor of a hash table.
    For speed reasons you'd want this to be at
    most `0.8f`, but up to `3.0f`is technically
    acceptable.

    @param `htable`: The hash table.

    @returns The load factor as a float.

    @note https://en.wikipedia.org/wiki/Hash_table#Load_factor
*/
inline float hashtable_calc_load_factor(hashtable_t* htable) {
    return (float)htable->entries_n / (float)htable->buckets_n;
}

/*
    Calculates the bucket usage of a hash table.
    This is the number of buckets with at least
    one value over the total number of buckets.
    Compare with `hashtable_calc_load_factor`
    to analyze spread.

    @param `htable`: The hash table.

    @returns The load factor as described, as a float.
*/
inline float hashtable_calc_bucket_usage(hashtable_t* htable) {
    size_t filled_buckets = 0;
    for (size_t it = 0; it < htable->buckets_n; it++) {
        if (htable->buckets[it].key != NULL) {
            filled_buckets++;
        }
    }

    return (float)filled_buckets / (float)htable->buckets_n;
}

/*
    Sets a key-value pair in a hash table.
    Overwrites the old value if it exists.
    Copies (dupes) both the key and value.

    @param `htable`: The hash table.
    @param `key`: The key whose value to set.
    @param `val`: The value to set.
    @param `val_sb`: The size of the value in bytes.
*/
void hashtable_set(hashtable_t* htable, void* key, void* val, size_t val_sb) {
    RUNTIME_ASSERT(htable != NULL);
    RUNTIME_ASSERT(key != NULL);
    RUNTIME_ASSERT(val != NULL);
    RUNTIME_ASSERT(val_sb > 0);

    /* Fetch the head entry. */
    hashtable_entry_t* entry = &(
        htable->buckets[hash_fnv1a(key, htable->key_sb) % htable->buckets_n]
    );

    /* Find the specific entry and operate accordingly. */
    for (size_t i = 0; i < htable->entries_n + 1; i++) {

        /* Found empty entry. */
        if (entry->key == NULL) {
            entry->key = malloc(htable->key_sb); /* key copy */
            memcpy(entry->key, key, htable->key_sb);

            entry->val = malloc(val_sb); /* val copy */
            memcpy(entry->val, val, val_sb);
            entry->val_sb = val_sb;

            htable->entries_n++;

            return; /* done */ /* written fresh */
        }

        /* Found entry with correct key. */
        if (MEM_EQ(entry->key, key, htable->key_sb)) {
            FREE(entry->val);

            entry->val = malloc(val_sb);
            memcpy(entry->val, val, val_sb);
            entry->val_sb = val_sb;

            return; /* done */ /* overwritten */
        }

        /* Next in chain, creating if not exists. */
        if (entry->next == NULL) {
            entry->next = calloc(1, sizeof(hashtable_entry_t));
        }

        entry = entry->next;

    }

    /* If no early exit, something's wrong! */
    ERROR("Maximum iteration depth reached in hashtable_set, htable=%p key=%p nentries=%zu.\n", htable, key, htable->entries_n);
    hex_dump(stderr, key, htable->key_sb, "key");
    exit(EXIT_FAILURE);
}

/*
    Removes an entry from a hash table.

    @param `htable`: The hash table.
    @param `key`: The key whose entry to remove.

    @note This does not currently have pre-free functionality.
*/
void hashtable_rid(hashtable_t* htable, void* key) {
    RUNTIME_ASSERT(htable != NULL);
    RUNTIME_ASSERT(key != NULL);

    /* Fetch the head entry. */
    hashtable_entry_t* entry = &(
        htable->buckets[hash_fnv1a(key, htable->key_sb) % htable->buckets_n]
    );

    /* Find the specific entry and operate accordingly. */
    for (size_t i = 0; i < htable->entries_n + 1; i++) {

        /* End of chain. */
        if (entry->key == NULL) {
            return; /* done */ /* didn't find */
        }

        /* Found entry with correct key. */
        if (MEM_EQ(entry->key, key, htable->key_sb)) {
            FREE(entry->key);
            FREE(entry->val);

            htable->entries_n--;

            /* If there's a `next`, shift its information into the current entry. */
            if (entry->next != NULL) {
                hashtable_entry_t* dangling = entry->next;
                *entry = *entry->next;
                FREE(dangling);
            }

            return; /* done */ /* removed */
        }

        /* Next in chain, if exists. */
        if (entry->next != NULL) {
            entry = entry->next;
        } else {
            return; /* done */ /* didn't find */
        }
    }

    /* This shouldn't happen, but I need to know if it does. */
    DEBUG("Maximum iteration depth reached in hashtable_rid, htable=%p key=%p.\n", htable, key);
    hex_dump(stderr, key, htable->key_sb, "key");
}

/*
    Removes all entries from a hash table then frees it.

    @param `htable`: The hash table.
*/
void hashtable_free(hashtable_t* htable) {
    RUNTIME_ASSERT(htable != NULL);

    /* Free all entries. */
    for (size_t i = 0; i < htable->buckets_n; i++) {
        hashtable_entry_t* next_entry = htable->buckets[i].next;

        /* Iteratively free the bucket's chain (if exists). */
        while (next_entry != NULL) {
            hashtable_entry_t* temp = next_entry;
            next_entry = next_entry->next;
            FREE(temp->key);
            FREE(temp->val);
            FREE(temp);
        }

        /* Free the head. */
        FREE(htable->buckets[i].key);
        FREE(htable->buckets[i].val);
    }

    /* Free the table. */
    FREE(htable->buckets);
    FREE(htable); /* done */ /* freed */
}