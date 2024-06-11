/* === HASH TABLE === */
#if __has_include("ttk/hashtable.h") 
#include "ttk/hashtable.h"
#include "ttk/hexdump.h"

static void __attribute__((constructor)) test_hashtable(void) {
    NOCODE // TODO
}


/* TODO
    - test hashtable.c/hashtable.h
    - write `dynamicarray.c`/`dybamicarray.h`
        - implemented as dynmatically sized c-style array
        - should expose var-arg creation syntax
            - e.g. `dyn_array_init(int, 1, 2, 3, 4, 5)` -> {1,2,3,4,5,0,0,0}
        - should expose set/get index which resizes to power of 2 which fits
            - e.g. `{1,2,3,0}`, set(1, 5) -> `{1,5,3,0}`, set(5, 4) -> {1,5,3,0,0,4,0,0,0}
    - write `doublylinkedlist.c`/`doublylinkedlist.h`
        - tracks head and tail
        - should implement get element by index (with a note to just use an array if this is your goal)
        - should expose `get`/`push`/`pop` to or from either the head or tail
            - this makes it either a stack or a queue!
    - write bit_array? mayble
        - https://en.wikipedia.org/wiki/Bit_array
        - you can bit shift by casting a series of bits to an int, shifting, 
          then comparing to original size's max (e.g. https://stackoverflow.com/questions/8534107/detecting-multiplication-of-uint64-t-integers-overflow-with-c)
        - bit arrays are useful for properties, compression algs, and bloom filters
*/

#endif