#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LINE_COUNT 100

typedef struct Color {
    Uint8 r, g, b;
} Color;

typedef struct Line {
    int x1, y1;
    int x2, y2;
    Color color;
} Line;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Line drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    
    bool quit = false;
    SDL_Event event;
    
    int start_x, start_y;
    bool drawing = false;
    Color currentColor = {255, 255, 255};

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                printf("Mouse position: x=%d, y=%d\n", event.motion.x, event.motion.y);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (!drawing) {
                        start_x = event.button.x;
                        start_y = event.button.y;
                        drawing = true;
                    } else {
                        if (line_count < MAX_LINE_COUNT) {
                            lines[line_count] = (Line){start_x, start_y, event.button.x, event.button.y, currentColor};
                            line_count++;
                        }
                        drawing = false;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < line_count; i++) {
            SDL_SetRenderDrawColor(renderer, lines[i].color.r, lines[i].color.g, lines[i].color.b, 255);
            SDL_RenderDrawLine(renderer, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}