#ifndef UFG_CHUNK_H
#define UFG_CHUNK_H

#include "toolkit/toolkit.h"
#include "toolkit/rle.h"
#include "mesh.h"

/* Side length of a cubic chunk in UFG. */
#define UFG_CHUNK_SIZE 64

/* Converts [x, y, z] array access into flattened access. X-Y horizontals, Z up.*/
#define CHUNK_FLAT(x, y, z) \
    (x + UFG_CHUNK_SIZE * (z + UFG_CHUNK_SIZE * y))

/* LoD levels from 0 (full resolution) to 3 (1x1 resolution). */
typedef enum lod_et {
    LOD_0,
    LOD_1,
    LOD_2,
    LOD_3
} lod_et;

/* One 64x64 (see: UFG_CHUNK_SIZE) chunk of marching cubes terrain with LoDs. */
typedef struct chunk_t {
    int64_t coordinates[3]; /* [x, y, z] of the chunk. X-Y horizontals, Z up. Chunk origin is -y, -x, -z. */
    uint64_t is_solid[UFG_CHUNK_SIZE * UFG_CHUNK_SIZE]; /* Compressed info on if each vertex owned by the chunk is solid (inside terrain). Coordinates are relative to chunk origin! */
    mesh_t lod0; /* 64x64 sampling. */
    mesh_t lod1; /* 16x16 sampling. */
    mesh_t lod2; /* 4x4 sampling. */
    mesh_t lod3; /* 1x1 sampling. */
    lod_et lod; /* The current lod level (see: `lod_et`). */
} chunk_t;

/* Returns the `is_solid` bit for the given vertex in the chunk (coordinates relative to chunk origin). */
#define CHUNK_GET_IS_SOLID(chunk, x, y, z) \
    ((chunk.is_solid[CHUNK_FLAT(x, y, z) / UFG_CHUNK_SIZE] >> (CHUNK_FLAT(x, y, z) % UFG_CHUNK_SIZE)) & 1)

/* Sets high the `is_solid` bit for the given vertex in the chunk (coordinates relative to chunk origin). */
#define CHUNK_SET_IS_SOLID_HIGH(chunk, x, y, z) \
    (chunk.is_solid[CHUNK_FLAT(x, y, z) / UFG_CHUNK_SIZE] |= ((uint64_t)1 << (CHUNK_FLAT(x, y, z) % UFG_CHUNK_SIZE)))

/* Sets low the `is_solid` bit for the given vertex in the chunk (coordinates relative to chunk origin). */
#define CHUNK_SET_IS_SOLID_LOW(chunk, x, y, z) \
    (chunk.is_solid[CHUNK_FLAT(x, y, z) / UFG_CHUNK_SIZE] &= ~((uint64_t)1 << (CHUNK_FLAT(x, y, z) % UFG_CHUNK_SIZE)))

#endif