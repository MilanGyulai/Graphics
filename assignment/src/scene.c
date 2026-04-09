#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <utils.h>

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
        glEnd();
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
    draw_origin();

    //grid
    float gridSize = 30.0f; // size
    glBegin(GL_LINES);
    float step = 2.0f;      // density
    //green
    glColor3f(0.0f, 0.3f, 0.5f);
        for (float z = -30.0f; z <= 30.0f; z += step * 2) {
            for(int i = -gridSize; i <= gridSize; i += step){
                //x axis
                glVertex3f(i, -gridSize, z); glVertex3f(i, gridSize, z); 
                //y axis
                glVertex3f(-gridSize, i, z); glVertex3f(gridSize, i, z); 
            }
    }
        for (float x = -gridSize; x <= gridSize; x += step * 2) {
            for (float y = -gridSize; y <= gridSize; y += step * 2) {
                // x,y axis lines
                glVertex3f(x, y, -30.0f);
                glVertex3f(x, y, 30.0f);
        }
    }
    glEnd();

    //cubes generating
    //4x4
    ///to-do: pulsating data_values with moving?, textures?,files?
    int index = 0;
    for (int x = 0; x < 4; x++){
        for (int y = 0; y < 4; y++){
            if(index > DATA_COUNT) break;
            int current_value = scene->data_values[index];

            glPushMatrix();
            glTranslatef(x * 2.0f, y * 2.0f, 0.0f);
            if(current_value > 100){
                //magenta
                glColor3f(1.0f,0.0f,0.8f);
            } else{
                //cyan
                glColor3f(0.0f,0.8f,1.0f);
            }
            
            float height = current_value / 20.0f;
            glScalef(0.8f,0.8f,height);

            draw_cube();
            glPopMatrix();
            index++;
        } 
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);

    glEnd();
}