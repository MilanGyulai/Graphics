#ifndef UTILS_H
#define UTILS_H
#include <GL/gl.h>

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

/**
 * Color with RGB components
 */
typedef struct Color
{
    float red;
    float green;
    float blue;
} Color;

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

GLuint load_texture(const char* filename);
GLuint load_model(const char* filename);

#endif /* UTILS_H */
