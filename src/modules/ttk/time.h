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

typedef struct timestamp_t {
    int64_t sec; /* Seconds. Signed so this can also be a timedelta. */
    int64_t nsec; /* Nanoseconds. Signed so this can also be a timedelta. */
} timestamp_t;

/* Number of nanoseconds in a second. Useful for conversions. */
#define NSEC_PER_SEC 1000000000

/* Difference between two `timestamp_t`s as a `timestamp_t`. */
#define TIMEDELTA(timestamp1, timestamp2) 

extern timestamp_t  timestamp_get(bool monotonic);
extern timestamp_t  timestamp_dif(timestamp_t timestamp1, timestamp_t timestamp2);
extern void         timestamp_strftime(char* buf, size_t max_size, const char* format, timestamp_t timestamp);

#endif