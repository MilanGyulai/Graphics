#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// --- KÜLSŐ KÖNYVTÁR: tinyobjloader-c ---
// Forrás: https://github.com/syoyo/tinyobjloader-c
// Licenc: MIT
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"


double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

GLuint load_texture(const char* filename){
	GLuint texture;
	SDL_Surface* surface;

	surface = IMG_Load(filename);
	if(surface == NULL){
		printf("ERROR: file was not found %s \n", filename);
		printf("ERROR: SDL_image %s \n", IMG_GetError());
		return 0;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4){
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	return texture;
}

static void file_reader(void* ctx, const char* filename, const int is_mtl,
                        const char* obj_filename, char** data, size_t* len) {
    (void)ctx; (void)is_mtl; (void)obj_filename;
    FILE* file = fopen(filename, "rb");
    if (!file) { *data = NULL; *len = 0; return; }
    fseek(file, 0, SEEK_END);
    *len = ftell(file);
    fseek(file, 0, SEEK_SET);
    *data = (char*)malloc(*len + 1);
    fread(*data, 1, *len, file);
    (*data)[*len] = '\0';
    fclose(file);
}

GLuint load_model(const char* filename) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t* materials = NULL;
    size_t num_materials;

    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
    int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials, 
                                filename, file_reader, NULL, flags);

    if (ret != TINYOBJ_SUCCESS) {
        printf("ERROR TinyObjLoader did not found the file: %s\n", filename);
        return 0;
    }

    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    for (size_t i = 0; i < num_shapes; i++) {
        size_t index_offset = 0;
        
        for (size_t f = 0; f < attrib.num_face_num_verts; f++) {
            for (size_t v = 0; v < 3; v++) {
                tinyobj_vertex_index_t idx = attrib.faces[index_offset + v];

                if (idx.v_idx >= 0 && attrib.num_texcoords > 0 && idx.vt_idx >= 0) {
                    float tx = attrib.texcoords[2 * idx.vt_idx + 0];
                    float ty = attrib.texcoords[2 * idx.vt_idx + 1];
                    glTexCoord2f(tx, ty);
                }

                if (idx.v_idx >= 0 && attrib.num_normals > 0 && idx.vn_idx >= 0) {
                    float nx = attrib.normals[3 * idx.vn_idx + 0];
                    float ny = attrib.normals[3 * idx.vn_idx + 1];
                    float nz = attrib.normals[3 * idx.vn_idx + 2];
                    glNormal3f(nx, ny, nz);
                }

                if (idx.v_idx >= 0) {
                    float vx = attrib.vertices[3 * idx.v_idx + 0];
                    float vy = attrib.vertices[3 * idx.v_idx + 1];
                    float vz = attrib.vertices[3 * idx.v_idx + 2];
                    glVertex3f(vx, vy, vz);
                }
            }
            index_offset += 3;
        }
    }

    glEnd();
    glEndList();

    tinyobj_attrib_free(&attrib);
    if (shapes) tinyobj_shapes_free(shapes, num_shapes);
    if (materials) tinyobj_materials_free(materials, num_materials);

    printf("OK TinyObjLoader loaded in: %s\n", filename);
    return list;
}
