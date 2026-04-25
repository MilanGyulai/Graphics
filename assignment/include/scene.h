#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

//4x4 tile
#define DATA_COUNT 100

typedef struct Scene
{
    float sphere_rotation;
    int data_values[DATA_COUNT];
    double uptime;
    GLuint texture_id;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void draw_cube();

#endif /* SCENE_H */
