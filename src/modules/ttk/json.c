#include "json.h"

/*
    Converts json text into a new json object on the heap.
    The user is allowed to obtain this text in any way they wish.
    Expects UTF-8!

    @param `json`: The json text.

    @returns Pointer to a new `json_object_t`.

*/
// json_object_t* json_read(const char* json) {
//     FIXME;
//     IGNORE(json);

//     /* 
//         Read calls `json_parse_value`, which digests any value.
//         Since there's a single top-level value (typically object), 
//          this gives you the full nested (pointed) structure.
//         The private `_span` member will be useful for this.
//     */
// }