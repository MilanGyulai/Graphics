#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <utils.h>
#include <stdio.h>

void draw_cube(){
    glBegin(GL_QUADS);

        glNormal3f(0.0f, -1.0f, 0.0f);
        //front side
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0,0,0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1,0,0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1,0,1);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(0,0,1);

        glNormal3f(0.0f, -1.0f, 0.0f);
        //back side
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(0,1,0);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1,1,0);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f);  
        glVertex3f(0,1,1);

        glNormal3f(1.0f, 0.0f, 0.0f);
        //right side
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(1,0,0);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1,1,0);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(1,0,1);


        glNormal3f(-1.0f, 0.0f, 0.0f);
        //left side
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0,0,0); 
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0,1,0); 
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0,1,1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0,0,1);

        glNormal3f(0.0f, 0.0f, 1.0f);
        //top side
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0,0,1);
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1,0,1);
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0,1,1);

        //base not sure if I should implement because it wont be seen (except if I transform the cube somehow)
        glEnd();
}
 

void init_scene(Scene* scene)
{
    scene->sphere_rotation = 0.0f; 
    scene->uptime = 0.0f;
    scene->texture_id = load_texture("assets/material.jpg");
    scene->model_id = load_model("assets/drone.obj");

    int demo_data[] = {20, 45, 12, 180, 50, 60, 30, 90, 200, 15, 88, 40, 10, 160, 25, 70};

    for(int i = 0; i < DATA_COUNT; ++i){
        scene->data_values[i] = demo_data[i];
    }
}

void update_scene(Scene* scene, double time)
{
    scene->uptime += time;
}

void render_scene(const Scene* scene)
{
    draw_origin();
    
    //grid
    float gridSize = 30.0f; // size
    glBegin(GL_LINES);
    float step = 2.0f;      // density
    
    glColor3f(0.0f, 0.3f, 0.5f);
    
    //green
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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    //cubes generating
    //4x4
    ///to-do: pulsating data_values with moving?, textures?,files?
    int index = 0;
    for (int x = 0; x < 16; x++){
        for (int y = 0; y < 16; y++){
            if(index > DATA_COUNT) break;

            int current_value = scene->data_values[index];
            
            glPushMatrix();
            glTranslatef(x * 2.0f, y * 2.0f, 0.0f);

            float norm = (float)current_value / 200.0f;
            float base_r, base_g, base_b;
            float time_offset = (float)index * 0.5f;
            float random_speed =  5.0f + ((index % 5)*2.0f);

            if(norm < 0.5f){
                base_r = 0.0f;
                base_g = norm * 1.0f;
                base_b = 1.0f;
            }else{
                float red_intensity = (norm - 0.5f) * 2.0f;
                base_r = 1.0f;
                base_g = 0.5f * (1.0f - red_intensity);
                base_b = 0.0f;
                }

            float pulse = sin((scene->uptime * random_speed) + time_offset) * 0.25f;

            glColor3f(
                base_r + pulse,
                base_g + pulse,
                base_b + pulse
                );

            float height = current_value /20.0f;
            glScalef(0.8f,0.8f,height);
            draw_cube();
            glPopMatrix();
            index++;
            } 
        }
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, scene->texture_id);
            glColor3f(1.0f, 1.0f, 1.0f);

            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 10.0f); 
                glScalef(0.1f, 0.1f, 0.1f); 
                glCallList(scene->model_id);
            glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);

    glEnd();
}