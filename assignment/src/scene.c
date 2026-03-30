#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void draw_cube(){
    glBegin(GL_QUADS);
        //front side
        glVertex3f(0,0,0); glVertex3f(1,0,0); glVertex3f(1,0,1); glVertex3f(0,0,1);
        //back side
        glVertex3f(0,1,0); glVertex3f(1,1,0); glVertex3f(1,1,1); glVertex3f(0,1,1);
        //right side
        glVertex3f(1,0,0); glVertex3f(1,1,0); glVertex3f(1,1,1); glVertex3f(1,0,1);
        //left side
        glVertex3f(0,0,0); glVertex3f(0,1,0); glVertex3f(0,1,1); glVertex3f(0,0,1);
        //top side
        glVertex3f(0,0,1); glVertex3f(1,0,1); glVertex3f(1,1,1); glVertex3f(0,1,1);

        //base not sure if I should implement because it wont be seen (except if I transform the cube somehow)
}
 

void init_scene(Scene* scene)
{
    scene->sphere_rotation = 0.0f; 

    int demo_data[] = {20, 45, 12, 180, 50, 60, 30, 90, 200, 15, 88, 40, 10, 160, 25, 70};

    for(int i = 0; i < DATA_COUNT; ++i){
        scene->data_values[i] = demo_data[i];
    }
}

void update_scene(Scene* scene, double time)
{
    (void)time;
    (void)scene;
}

void render_scene(const Scene* scene)
{
    (void)scene;
    draw_origin();
    float gridSize = 15.0f; // size
    glBegin(GL_LINES);
    float step = 1.0f;      // density
    glColor3f(0.0f, 0.3f, 0.5f);
    for (float i = -gridSize; i <= gridSize; i += step) {
        // x axis lines
        glVertex3f(i, -gridSize, 0.0f);
        glVertex3f(i, gridSize, 0.0f);
        // y axis lines
        glVertex3f(-gridSize, i, 0.0f); 
        glVertex3f(gridSize, i, 0.0f);
    }
    glEnd();

    // to-do: make cubes somehow and make towers with them
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);

    glEnd();
}