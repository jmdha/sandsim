#include "input.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

struct input input_init() {
        struct input in = {0};
        return in;
}

void input(struct input *input) {
        input->exit = false;
        input->window_event = false;
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
                switch (e.type) {
                case SDL_QUIT:
                        input->exit = true;
                        break;
                case SDL_WINDOWEVENT:
                        input->window_event = true;
                        break;
                case SDL_MOUSEBUTTONDOWN:
                        input->is_pressed = true;
                        break;
                case SDL_MOUSEBUTTONUP:
                        input->is_pressed = false;
                        break;
                }
        }
        SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
}
