#ifndef SCENE_H
#define SCENE_H

#include "camera.h"



typedef struct Scene
{    
    double uptime;
    float sphere_rotation;
    float tower_x[256];
    float tower_y[256];
    int data_values[256];
    int is_hacked[256];
    int hacked_count;
    int hacker_mode;
    int active_tower_index;
    int current_hack_level;
    int is_target[256];
    GLuint texture_id;
    GLuint model_id;
    GLuint terminal_id[3];
    GLuint matrix_texture_id;

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

void hack_tower(Scene* scene, float cam_x,  float cam_y);

void draw_progress_bar(const Scene* scene);

void process_hack_input(Scene* scene, int choice);

void draw_terminal(const Scene* scene);


#endif /* SCENE_H */
