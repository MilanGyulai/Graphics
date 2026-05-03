#include "app.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

static float light_intensity = 1.0f;
void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Origin!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->uptime = (double)SDL_GetTicks() / 1000;
    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.02f, 0.02f, 0.06f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glLineWidth(2.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambient_light[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_pos[] = { 0.0f, 50.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glEnable(GL_FOG);
    GLfloat fog_color[] = {0.02f, 0.02f, 0.06f, 1.0f}; 
    glFogfv(GL_FOG_COLOR, fog_color);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.035f);
    glFogi(GL_FOG_HINT, GL_NICEST);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 1000
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE: app->is_running = false; break;
            case SDL_SCANCODE_F1: SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "Help:\n",
                "Movement:\n"
                "W, A, S, D - forward, left, back, right \n"
                "Q, E - up, down\n"
                "Mouse left button(hold) move camera with swipe\n"
                "+, - light intensity up and down",
                app->window
            );
            break;
            case SDL_SCANCODE_KP_PLUS:
            light_intensity += 1.0f;
            if(light_intensity > 10.0f){
                light_intensity = 10.0f;
            }
            printf("Light intensity: %f\n", light_intensity);
            break;
            case SDL_SCANCODE_KP_MINUS:
            light_intensity -= 1.0f;
            if(light_intensity < -10.0f){
                light_intensity = -10.0f;
            }
            printf("Light intensity: %f\n", light_intensity);
            break;
            case SDL_SCANCODE_F:
            printf("F button pressed! Kamera: X=%.2f, Y=%.2f\n", 
                       app->camera.position.x, app->camera.position.y);
            hack_tower(&(app->scene), app->camera.position.x, app->camera.position.y);
            break;
            case SDL_SCANCODE_1: process_hack_input(&(app->scene), 1);break;
            case SDL_SCANCODE_2: process_hack_input(&(app->scene), 2);break;
            case SDL_SCANCODE_3: process_hack_input(&(app->scene), 3);break;
            case SDL_SCANCODE_W: set_camera_speed(&(app->camera), 10); break;
            case SDL_SCANCODE_S: set_camera_speed(&(app->camera), -10); break;
            case SDL_SCANCODE_A: set_camera_side_speed(&(app->camera), 10); break;
            case SDL_SCANCODE_D: set_camera_side_speed(&(app->camera), -10); break;
            
            case SDL_SCANCODE_E: set_camera_vertical_speed(&(app->camera), 10); break;
            case SDL_SCANCODE_Q: set_camera_vertical_speed(&(app->camera), -10); break;
            
            case SDL_SCANCODE_J: set_camera_rotation_speed(&(app->camera), 90.0); break;
            case SDL_SCANCODE_L: set_camera_rotation_speed(&(app->camera), -90.0); break;
            default: break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S: set_camera_speed(&(app->camera), 0); break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D: set_camera_side_speed(&(app->camera), 0); break;
            
            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_E: set_camera_vertical_speed(&(app->camera), 0); break;
            
            case SDL_SCANCODE_J:
            case SDL_SCANCODE_L: set_camera_rotation_speed(&(app->camera), 0); break;
            default: break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT) {
                is_mouse_down = true;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), (double)(mouse_x - x) * 0.2, (double)(mouse_y - y) * 0.2);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT) {
                is_mouse_down = false;
            }
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    
    update_scene(&(app->scene), elapsed_time); 
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    GLfloat current_light[] = { light_intensity, light_intensity, light_intensity, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, current_light);
    GLfloat ambient_light[] = { light_intensity * 0.2f, light_intensity * 0.2f, light_intensity * 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
