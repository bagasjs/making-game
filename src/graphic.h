#ifndef RENDERER_H_
#define RENDERER_H_

#include "gm.h"
#include <stdint.h>

typedef struct Renderer Renderer;

Renderer *render_init(void);
void render_close(Renderer *render);

#define INVALID_ID 0

typedef uint32_t ShaderID;
typedef struct {
    const char *vert_glsl_source;
    const char *frag_glsl_source;
} ShaderDesc;
ShaderID render_create_shader(Renderer *render, ShaderDesc desc);

typedef uint32_t TextureID;
typedef struct {
    uint8_t *pixels;
    uint32_t width;
    uint32_t height;
    uint32_t nchannels;
} TextureDesc;
TextureID render_create_texture(Renderer *render, TextureDesc desc);

typedef uint32_t MeshID;
MeshID render_create_mesh(Renderer *render);

typedef uint32_t PipelineID;
MeshID render_create_pipeline(Renderer *render);

typedef struct Camera {

} Camera;

/*void render_use_pipeline(Renderer *ren, GraphicPipeline *pipe);*/
/*void render_use_mesh(Renderer *ren, Mesh *mesh);*/
/*void render_use_texture(Renderer *ren, Texture *tex);*/
/*void render_use_shader(Renderer *ren, Shader *shader);*/
/*void render_draw(Renderer *ren);*/
/*void render_clear(Renderer *ren);*/

#endif // RENDERER_H_
