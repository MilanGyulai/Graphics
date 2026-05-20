#include "scene.h"
#include "camera.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <utils.h>
#include <stdio.h>
#include <stdlib.h>


void draw_cube() {
    glBegin(GL_QUADS);
    //fényvisszaverődés
        glNormal3f(0.0f, -1.0f, 0.0f);
        //textúra
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1,0,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1,0,1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0,0,1);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0,1,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1,1,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0,1,1);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1,0,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1,1,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1,0,1);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0,1,0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0,1,1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0,0,1);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1,0,1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0,1,1);
    glEnd();
}

/*void draw_origin() {
    glBegin(GL_LINES);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
        glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
    glEnd();
}*/

void draw_sky(GLuint sky_texture){
    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;

    int n_slices, n_stacks;
    double radius;
    int i, k;

    n_slices = 36;
    n_stacks = 16;
    radius = 275.0f;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sky_texture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glScaled(radius, radius, radius);
    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double)(i) / n_stacks;
        v2 = (double)(i + 1) / n_stacks;

        phi1 = (v1 * M_PI) - (M_PI / 2.0);
        phi2 = (v2 * M_PI) - (M_PI / 2.0);

        for (k = 0; k <= n_slices; ++k) {
            u = (double)k / n_slices;
            theta = u * 2.0 * M_PI;

            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1);

            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2);

            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);

            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
            }
        }
        glEnd();
        glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

}

void draw_help_menu(const Scene* scene) {
    if (scene->show_help == 0) return;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0); 
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->help_texture_id);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(25.0f, 25.0f); 
        glTexCoord2f(1.0f, 1.0f); glVertex2f(75.0f, 25.0f); 
        glTexCoord2f(1.0f, 0.0f); glVertex2f(75.0f, 75.0f); 
        glTexCoord2f(0.0f, 0.0f); glVertex2f(25.0f, 75.0f); 
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void draw_progress_bar(const Scene* scene) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0); //100x100

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //mélység
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    // Sötétszürke
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(5.0f, 90.0f);
        glVertex2f(95.0f, 90.0f);
        glVertex2f(95.0f, 95.0f);
        glVertex2f(5.0f, 95.0f);
    glEnd();

    float progress = (float)scene->hacked_count / 3.0f; 
    if (progress > 1.0f) progress = 1.0f; //túlcsordulás

    float bar_width = 5.0f + (90.0f * progress); // dinamikus szélesség

    // zöld
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(5.0f, 90.0f);
        glVertex2f(bar_width, 90.0f);
        glVertex2f(bar_width, 95.0f);
        glVertex2f(5.0f, 95.0f);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void draw_terminal(const Scene* scene) {
    if (scene->hacker_mode == 0) return;

    //2d mód
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0); 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST); 
    glEnable(GL_TEXTURE_2D);
    //aktuális kép
    glBindTexture(GL_TEXTURE_2D, scene->terminal_id[scene->current_hack_level]);
    glColor3f(1.0f, 1.0f, 1.0f); //eredeti szín

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(20.0f, 20.0f); 
        glTexCoord2f(1.0f, 1.0f); glVertex2f(80.0f, 20.0f); 
        glTexCoord2f(1.0f, 0.0f); glVertex2f(80.0f, 80.0f); 
        glTexCoord2f(0.0f, 0.0f); glVertex2f(20.0f, 80.0f); 
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void process_hack_input(Scene* scene, int choice) {
    if (scene->hacker_mode == 0) return;

    int correct_answer = 0;
    switch (scene->current_hack_level) {
        case 0: correct_answer = 3; break;
        case 1: correct_answer = 2; break;
        case 2: correct_answer = 1; break;
    }

    if (choice == correct_answer) { 
        scene->is_hacked[scene->active_tower_index] = 1; //zöld torony
        scene->hacked_count++; //proggress
        printf("HACK SUCCESFUL SQL CODE ACCEPTED!\n");
    } else {
        printf("HACK WAS NOT SUCCESFUL ALERT! BAD QUERY.\n");
    }
    
    //visszaadjuk az írányítást
    scene->hacker_mode = 0;
}

void hack_tower(Scene* scene, float cam_x, float cam_y) {
    float closest_dist = 9999.0f;
    int closest_index = -1;

    for (int i = 0; i < 256; i++) {
        float dx = scene->tower_x[i] - cam_x;
        float dy = scene->tower_y[i] - cam_y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < closest_dist) {
            closest_dist = distance;
            closest_index = i;
        }

        if (distance < 4.0f && scene->is_hacked[i] == 0 && scene->is_target[i] == 1) {
            scene->hacker_mode = 1; //mód váltás
            scene->active_tower_index = i; //eltároljuk a tornyot
            scene->current_hack_level = rand() % 3; //random feladvány
            printf("TERMINAL HACK STARTED ON COLUMN %d\n", i);
            return;
        }
    }
    printf("HACK WAS NOT SUCCESFUL Closest: column %d | Dist: %.2f | Status: %d\n", 
           closest_index, closest_dist, scene->is_hacked[closest_index]);
}


void init_scene(Scene* scene) {
    scene->sphere_rotation = 0.0f; 
    scene->uptime = 0.0f;
    scene->texture_id = load_texture("assets/material.jpg");
    scene->model_id = load_model("assets/drone.obj");
    scene->hacked_count = 0;
    scene->hacker_mode = 0;
    scene->active_tower_index = -1;
    scene->current_hack_level = 0;
    scene->show_help = 0;
    
    scene->terminal_id[0] = load_texture("assets/hack1.png");
    scene->terminal_id[1] = load_texture("assets/hack2.png");
    scene->terminal_id[2] = load_texture("assets/hack3.png");
    scene->matrix_texture_id = load_texture("assets/matrix.png");
    scene->help_texture_id = load_texture("assets/help.png");
    scene->sky_texture_id = load_texture("assets/sky.png");
    

    for(int i = 0; i < 256; ++i) {
        scene->data_values[i] = (rand() % 150) + 10;
        scene->is_hacked[i] = 0;
        scene->is_target[i] = 0;
        // float x, y , dist;
        //koordináták +30 és -30 között
        scene->tower_x[i] = ((rand() % 600) / 10.0f) - 30.0f; 
        scene->tower_y[i] = ((rand() % 600) / 10.0f) - 30.0f;
    }

    int targets_assigned = 0;
    while (targets_assigned < 3) {
        int r = rand() % 256;
        if (scene->is_target[r] == 0) {
            scene->is_target[r] = 1;
            targets_assigned++;
        }
    }
}

void update_scene(Scene* scene, double time) {
    scene->uptime += time;
}

void render_scene(const Scene* scene) {
    /*draw_origin();*/
    draw_sky(scene->sky_texture_id);
    
    int victory = (scene->hacked_count >= 3);

    //grid
    float gridSize = 30.0f; 
    glBegin(GL_LINES);
    float step = 2.0f;      
    
    //win condition
    if (victory) glColor3f(0.0f, 1.0f, 1.0f);
    else glColor3f(0.0f, 0.3f, 0.5f);
    
    //vonalak
    for (float z = -30.0f; z <= 30.0f; z += step * 2) {
        for(int i = -gridSize; i <= gridSize; i += step){
            glVertex3f(i, -gridSize, z); glVertex3f(i, gridSize, z); 
            glVertex3f(-gridSize, i, z); glVertex3f(gridSize, i, z); 
        }
    }
    for (float x = -gridSize; x <= gridSize; x += step * 2) {
        for (float y = -gridSize; y <= gridSize; y += step * 2) {
            glVertex3f(x, y, -30.0f); glVertex3f(x, y, 30.0f);
        }
    }
    glEnd();

    //effect
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->matrix_texture_id);
    
    //animáció
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0f, scene->uptime * 0.1f, 0.0f);
    glMatrixMode(GL_MODELVIEW);

    for (int i = 0; i < 256; i++) {
        int current_value = scene->data_values[i];
        
        glPushMatrix();
        glTranslatef(scene->tower_x[i], scene->tower_y[i], 2.0f);

        //színkódolás
        if (victory) {
            glColor3f(0.0f, 0.6f, 1.0f); 
        } else if (scene->is_hacked[i] == 1) {
            glColor3f(0.0f, 1.0f, 0.0f); 
        } else if (scene->is_target[i] == 1) {
            float pulse = sin(scene->uptime * 4.0f) * 0.5f;
            glColor3f(1.0f, 0.3f + pulse, 0.3f + pulse); 
        } else {
            float norm = (float)current_value / 200.0f;
            glColor3f(1.0f, 1.0f, 0.3f + (norm * 0.2f)); 
        }

        float height = current_value / 20.0f;
        glScalef(0.8f, 0.8f, height);
        draw_cube();
        glPopMatrix();
    } 
    
    //animáció leállítása a drón miatt
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

   glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id); 
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
        glTranslatef(0.0f, 30.0f, 5.0f); 
        glRotatef(scene->uptime * 45.0f, 0.0f, 0.0f, 1.0f);
        glScalef(0.2f, 0.2f, 0.2f); 
        glCallList(scene->model_id);
    glPopMatrix();


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float hover = sin(scene->uptime * 3.0f) * 0.03f;

    //drón helyzete
    glTranslatef(0.0f, -0.5f + hover, -1.5f);
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glCallList(scene->model_id);
    
    glPopMatrix();

    draw_progress_bar(scene);
    draw_terminal(scene);
    draw_help_menu(scene);
}