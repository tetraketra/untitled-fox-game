#ifndef TTK_JSON_H
#define TTK_JSON_H

#include "ttk.h"

/*
    === INFO ===
    1. JSON read/write as single transactions (entire structure at once).
    2. Keys ("names") must be <=128 characters.
    3. Only allows a single top-level object.
    4. This could use hash tables, but:
        - my hash table library isn't smart enough for this right now.
        - premature optimization is evil.
        - you shouldn't be doing JSON lookups *that* frequently.
*/

typedef struct json_span_t {
    size_t begin; /* Inclusive! */
    size_t end; /* Exclusive! */
} json_span_t;

typedef struct json_entry_t json_entry_t;
typedef struct json_object_t {
    json_entry_t* members;
    size_t        members_n;
} json_object_t;

typedef struct json_value_t json_value_t; 
typedef struct json_array_t {
    json_value_t* values;
    size_t        values_n;
} json_array_t;

typedef union json_value_u {
    json_object_t object;
    json_array_t  array;
    const char*   string;
    int           integer;
    double        decimal;
    bool          boolean;
} json_value_u;

typedef enum json_value_types_e {
    TTKJVT_UNDEFINED,
    TTKJVT_OBJECT,
    TTKJVT_ARRAY,
    TTKJVT_STRING,
    TTKJVT_INTEGER,
    TTKJVT_DECIMAL,
    TTKJVT_BOOL,
    TTKJVT_NULL,
} json_value_types_e;

typedef struct json_value_t {
    json_value_u*      data;
    json_value_types_e data_tag;
    json_span_t        _span;
} json_value_t;

typedef struct json_entry_t {
    const char          name[128];
    json_value_t*       value;
} json_entry_t;

extern json_object_t* json_read(const char* json);

#endif