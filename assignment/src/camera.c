#include "camera.h"
#include <GL/gl.h>
#include <math.h>
#include <scene.h>

void init_camera(Camera* camera)
{
    camera->position.x = 3.0;
    camera->position.y = -10.0;
    camera->position.z = 10.0;

    camera->rotation.x = -30.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 90.0;

    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->rotation_speed.x = 0.0;
    camera->rotation_speed.y = 0.0;
    camera->rotation_speed.z = 0.0;
}

int can_move(const Scene* scene, double next_x, double next_y) {

    if (next_x < -29.0 || next_x > 29.0 || next_y < -29.0 || next_y > 29.0) {
        return 0;
    }

    double hitbox_radius = 1.2f; 
    for (int i = 0; i < 256; i++) {
        double dx = scene->tower_x[i] - next_x;
        double dy = scene->tower_y[i] - next_y;
        
        double distance = sqrt(dx * dx + dy * dy);

        if (distance < hitbox_radius) {
            return 0;
        }
    }

    return 1;
}

void update_camera(Camera* camera, const Scene* scene , double time)
{
    double angle;
    double side_angle;

    camera->rotation.z += camera->rotation_speed.z * time;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    double planned_x = camera->position.x + (cos(angle) * camera->speed.y * time) + (cos(side_angle) * camera->speed.x * time);
    double planned_y = camera->position.y + (sin(angle) * camera->speed.y * time) + (sin(side_angle) * camera->speed.x * time);

    if(can_move(scene, planned_x, planned_y) == 1){
        camera->position.x = planned_x;
        camera->position.y = planned_y;
    }

    camera->position.z += camera->speed.z * time;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed) {
    camera->speed.z = speed;
}
void set_camera_rotation_speed(Camera* camera, double speed) {
    camera->rotation_speed.z = speed;
}