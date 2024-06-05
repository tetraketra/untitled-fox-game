#include "memtools.h"

/* 
    Dump memory as formatted hex.

    @param `stream`: The stream to write the hex dump to. Recommended stderr.
    @param `buffer`: The buffer whose bites to write to the stream.
    @param `buf_sb`: The size of the buffer in bytes.
    @param `desc`: An optional description of the buffer.
*/
void hex_dump(FILE* stream, void* buffer, size_t buf_sb, char* desc) {
    /* Guard, don't execute if no buffer. */
    if (buffer == NULL) {
        DEBUG("Hex dump requested but not executed. NULL buffer %p.\n", buffer);
        return; /* done */ /* no buffer */
    }

    /* Header. */
    DEBUG("Beginning hex dump of buffer %p of size %lu.\n", buffer, buf_sb);
    if (desc != NULL) {
        fprintf(stream, "%s: \n", desc);
    }

    /* Hex dump. */
    uint8_t* bytes = (uint8_t*)buffer;
    for (size_t i = 0; i < buf_sb; i++) {

        /* Separate by 16 bytes for readability. */
        if (i%16 == 0) {
            fprintf(stream, "  %04lu: ", i);
        }

        /* Print byte */
        fprintf(stream, "%02x ", bytes[i]);

        /* Separate by 16 bytes for readability. */
        if (i%16 == 15 || i == buf_sb - 1) {
            fprintf(stream, "\n");
        }
    }
}