#include "scene.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

void draw_cylinder(float radius, float height, int segments) {
    int i;
    glBegin(GL_TRIANGLE_STRIP);
    for(i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0);
        glVertex3f(x, y, height);
    }
    glEnd();
}

void draw_cone(float radius, float height, int segments) {
    int i;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, height);
    for(i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0);
    }
    glEnd();
}

void init_scene(Scene* scene)
{
    scene->sphere_rotation = 0.0f;
}

void update_scene(Scene* scene, double time)
{
    scene->sphere_rotation += 60.0f * time;
    if(scene->sphere_rotation > 360.0f) {
        scene->sphere_rotation -= 360.0f;
    }
}

void render_scene(const Scene* scene)
{
    int i, j;
    int divs = 8;
    float step = 1.0f / divs;

    draw_origin();

    glBegin(GL_QUADS);
    for(i = 0; i < divs; i++) {
        for(j = 0; j < divs; j++) {
            if((i + j) % 2 == 0) glColor3f(1.0f, 1.0f, 1.0f);
            else glColor3f(0.2f, 0.2f, 0.2f);

            float x = i * step;
            float y = j * step;
            glVertex3f(x, y, 0.0f);
            glVertex3f(x + step, y, 0.0f);
            glVertex3f(x + step, y + step, 0.0f);
            glVertex3f(x, y + step, 0.0f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(0.2f, 0.2f, 0.3f);
    glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(0.8f, 0.2f, 0.3f);
    glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(0.5f, 0.8f, 0.5f);
    glEnd();


    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.7f);
    glRotatef(scene->sphere_rotation, 0.0f, 0.0f, 1.0f);
    
    glColor3f(0.6f, 0.6f, 0.6f);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad, 0.2, 8, 8);
    gluDeleteQuadric(quad);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 0.3f, 0.0f); 
    glColor3f(0.0f, 0.5f, 1.0f);
    draw_cylinder(0.2f, 0.6f, 16); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, 0.3f, 0.0f); 
    glColor3f(1.0f, 0.5f, 0.0f);
    draw_cone(0.2f, 0.6f, 16);
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