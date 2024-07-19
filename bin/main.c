#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "../src/bitgrid.h"
#include "../src/input.h"

bitgrid grid;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void init(void) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                fprintf(stderr, "could not initialize sdl2: %s\n",
                        SDL_GetError());
                exit(1);
        }
        window = SDL_CreateWindow("sandsim", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window == NULL) {
                fprintf(stderr, "could not create window: %s\n",
                        SDL_GetError());
                exit(1);
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_GL_SetSwapInterval(1);
        grid = bitgrid_init(800, 400);
}

void fini(void) {
        bitgrid_fini(&grid);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
}

void recalibrate(int *width, int *height, float *cell_width,
                 float *cell_height) {
        SDL_GetWindowSize(window, width, height);
        *cell_width = (float)*width / grid.width;
        *cell_height = (float)*height / grid.height;
}

void redraw(float cell_width, float cell_height) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (uint x = 0; x < grid.width; x++)
                for (uint y = 0; y < grid.height; y++) {
                        if (!bitgrid_get(&grid, x, y))
                                continue;
                        SDL_Rect rect = {.w = 1.5f * cell_width,
                                         .h = 1.5f * cell_height,
                                         .x = x * cell_width,
                                         .y = y * cell_height};
                        SDL_RenderFillRect(renderer, &rect);
                }
}

void simulate(void) {
        for (int y = grid.height - 2; y >= 0; y--)
                for (uint x = 0; x < grid.width; x++) {
                        if (!bitgrid_get(&grid, x, y))
                                continue;
                        if (!bitgrid_get(&grid, x, y + 1)) {
                                bitgrid_unset(&grid, x, y);
                                bitgrid_set(&grid, x, y + 1);
                        } else if (x > 0 && !bitgrid_get(&grid, x - 1, y + 1)) {
                                bitgrid_unset(&grid, x, y);
                                bitgrid_set(&grid, x - 1, y + 1);
                        } else if (x < grid.width - 1 &&
                                   !bitgrid_get(&grid, x + 1, y + 1)) {
                                bitgrid_unset(&grid, x, y);
                                bitgrid_set(&grid, x + 1, y + 1);
                        }
                }
}

int main(void) {
        init();
        struct input in = input_init();
        int w, h;
        float cell_width, cell_height;
        recalibrate(&w, &h, &cell_width, &cell_height);
        for (uint x = 0; x < grid.width; x++)
                for (uint y = 0; y < grid.height; y++)
                        if (rand() % 10 == 0)
                                bitgrid_set(&grid, x, y);
        bool running = true;
        u64 last_sim = SDL_GetTicks64();
        while (running) {
                input(&in);
                if (in.exit) {
                        running = false;
                        break;
                }
                if (in.is_pressed) {
                        uint x = grid.width * ((float)in.mouse_x / w);
                        uint y = grid.height * ((float)in.mouse_y / h);
                        bitgrid_set(&grid, x, y);
                }
                if (SDL_GetTicks64() - last_sim > 12) {
                        simulate();
                        last_sim = SDL_GetTicks64();
                }
                recalibrate(&w, &h, &cell_width, &cell_height);
                redraw(cell_width, cell_height);
                SDL_RenderPresent(renderer);
        }
        fini();
        return 0;
}
