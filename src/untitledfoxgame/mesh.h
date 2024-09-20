#ifndef UFG_MESH_H
#define UFG_MESH_H

#include "toolkit/toolkit.h"
#include "sdlext/opengl.h"
#include "cglm/cglm.h"

/* Vertex in the context of OpenGL (floats everywhere). */
typedef struct vertex_t {
    vec3 pos;
    vec3 norm;
    vec2 uv;
} vertex_t;

DEFINE_ARR_FOR_TYPE(vertex_t);

/* Supported (or wanted-to-be-supported) texture types. */
typedef enum texture_types_et {
    TT_DIFFUSE, /* Regular texture, like a photo. */
    TT_ALBEDO, /* Unlit pure texture. */
    TT_NORMAL, /* Directional of normals for shading. */
    TT_SPECULAR, /* Greyscale shininess. */
    TT_DISPLACEMENT, /* Greyscale displacement for depth. */
    TT_BUMP, /* Greyscale faked depth. */
    TT_ROUGHNESS, /* Greyscale gloss. */
    TT_OPACITY, /* Greyscale transparency. */
    TT_EMISSIVE, /* Monochrome does/doesn't glow. */
} texture_types_et;

/* Links an OpenGL texture (via unsigned int id) to a handling mode. */
typedef struct texture_t {
    gl_tex_t id;
    texture_types_et type;
} texture_t;

DEFINE_ARR_FOR_TYPE(texture_t);

/* Renderable mesh. */
typedef struct mesh_t {
    arr_vertex_t  vertices;
    arr_uint64_t  indices;
    arr_texture_t textures;
} mesh_t;

#endif