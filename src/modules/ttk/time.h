#ifndef TTK_TIME_H
#define TTK_TIME_H

#include "ttk.h"

/*
    === INFO ===
    1. Time structs for use pretty much everywhere.
    2. This library exists because time.h is nonportable, so I need a wrapper for fallbacks.
    3. The first version of this library is Linux-only. Improve when necessary.
    4. Eventually `timestamp_get()` will be a macro that dispatches based on built-for-OS tag.
*/

typedef struct timestamp_epoch_t {
    i64_t sec; /* Seconds. */
    i64_t nsec; /* Nanoseconds. */
} timestamp_t;

#endif