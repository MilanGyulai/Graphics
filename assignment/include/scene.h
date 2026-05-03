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

/*void draw_origin();*/


/**
 * Egyetlen 3D-s kockát (téglatestet) rajzol ki.
 * Ez az építőköve a kibertér adat-oszlopainak. 
 * Tartalmazza a normálvektorokat a fényekhez és az UV koordinátákat a textúrázáshoz.
 */
void draw_cube();


/**
 * Ellenőrzi a távolságot a kamera (drón) és az oszlopok között.
 * Ha a játékos elég közel ér egy célponthoz, megállítja a 3D mozgást,
 * és elindítja a 2D-s hacker minijátékot.
 * 
 * @param scene  A játéktér állapota
 * @param cam_x  A kamera aktuális X koordinátája
 * @param cam_y  A kamera aktuális Y koordinátája
 */
void hack_tower(Scene* scene, float cam_x,  float cam_y);


/**
 * 2D-s (ortografikus) nézetben kirajzolja a képernyő tetejére a folyamatjelző sávot.
 * A zöld sáv szélessége a sikeresen feltört oszlopok számától függ (0-tól 3-ig jelenleg).
 * 
 * @param scene  A játéktér állapota
 */
void draw_progress_bar(const Scene* scene);


/**
 * Feldolgozza a játékos billentyűzet-bemenetét a hacker minijáték közben.
 * Ellenőrzi, hogy a kiválasztott sorszám megegyezik-e a helyes SQL injekciós megoldással.
 * 
 * @param scene   A játéktér állapota
 * @param choice  A játékos által választott opció (1, 2 vagy 3)
 */
void process_hack_input(Scene* scene, int choice);


/**
 * 2D-s nézetben rárajzolja a képernyő közepére a felugró hacker terminált.
 * A megfelelő SQL feladvány képét jeleníti meg az aktuális nehézségi szint alapján.
 * A kép betöltése nem volt egyértelmű mert balról fentről kezdődött a betöltése 
 *
 * @param scene  A játéktér állapota (csak olvasható pointer)
 */
void draw_terminal(const Scene* scene);


#endif /* SCENE_H */
