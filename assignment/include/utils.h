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

/**
 * Betölt egy képfájlt (pl. PNG vagy JPG) a megadott elérési útvonalról,
 * és átalakítja egy használható OpenGL textúrává.
 * 
 * @param filename  A képfájl elérési útvonala (pl. "assets/matrix.png")
 * @return          A generált OpenGL textúra azonosítója (ID-ja), 
 *                  amivel a későbbiekben hivatkozni lehet rá a rajzolásnál.
 */
GLuint load_texture(const char* filename);

/**
 * Betölt egy 3D-s modellt (jellemzően .obj fájlt) a megadott elérési útvonalról.
 * Feldolgozza a modell csúcspontjait, normálvektorait és textúra koordinátáit,
 * majd feltölti a videókártyára egy OpenGL Display List formájában.
 * 
 * @param filename  A 3D modell fájljának elérési útvonala (pl. "assets/drone.obj")
 * @return          A betöltött modell OpenGL azonosítója,
 *                  amit a glCallList() függvénnyel lehet kirajzolni a térben.
 */
GLuint load_model(const char* filename);

#endif /* UTILS_H */
