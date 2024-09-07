#include "toolkit/json.h"



/*
    Converts json string into a new json object on the heap.
    Expects UTF-8!

    @param `json_str`: The json string. Doesn't care if zero-terminated if `len` specified.
    @param `len`: The length of the json string. `0` to assume zero-terminated.

    @returns Pointer to a new `json_object_t`.
*/
json_object_t* json_read(const char* json_str, size_t len) {
    IGNORE(json_str);
    IGNORE(len);
    

    /* 
        Read calls `json_parse_value`, which digests any value.
        Since there's a single top-level value (typically object), 
         this gives you the full nested (pointed) structure.
        The private `_span` member will be useful for this.
    */

   return &(json_object_t){0}; /* FIXME */
}