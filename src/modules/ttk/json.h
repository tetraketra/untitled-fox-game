#ifndef TTK_JSON_H
#define TTK_JSON_H

#include "ttk.h"
#include "ttk/hashtable.h"

/*
    === INFO ===
    1. JSON read/write as single transactions (entire structure at once).
    3. Only allows a single top-level object.
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
    json_object_t object;  /* Exists if TTK_JSON_OBJECT. */
    json_array_t  array;   /* Exists if TTK_JSON_ARRAY. */
    const char*   string;  /* Exists if TTK_JSON_STRING, cstring style. */
    int64_t       integer; /* Exists if TTK_JSON_INTEGER. */
    double        decimal; /* Exists if TTK_JSON_DECIMAL. */
    bool          boolean; /* Exists if TTK_JSON_BOOL. */
} json_value_u;

typedef enum json_value_types_e {
    TTK_JSON_OBJECT,  /* For a {}-bracketed object. */
    TTK_JSON_ARRAY,   /* For a []-bracketed array. May include any of these types. */
    TTK_JSON_STRING,  /* For a ""-wrapped string. Converted to a cstring during parsing. */
    TTK_JSON_INTEGER, /* For whole number as `int64_t`. */
    TTK_JSON_DECIMAL, /* For decimal number as `double`. */
    TTK_JSON_BOOL,    /* For Yes/No/True/False (any capitalization) as `bool`. */
    TTK_JSON_NULL,    /* For null as (json_value_u){0}. */
} json_value_types_e;

typedef struct json_value_t {
    json_value_u*      data; /* Value. */
    json_value_types_e tag; /* Type of value, see `json_value_types_e`. */
    json_span_t        _span; /* Location and width in the original JSON string. */
} json_value_t;

typedef struct json_key_t {
    const char*     data; /* Key. */
    size_t          len; /* Length of key. */
    json_span_t     _span; /* Location and width in the original JSON string. */
} json_key_t;

typedef struct json_entry_t {
    json_key_t          name;
    json_value_t*       value;
} json_entry_t;

extern json_object_t* json_read(const char* json);

#endif
