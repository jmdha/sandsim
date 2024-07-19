#pragma once

#include <stdbool.h>

#include "misc.h"

struct input {
        bool exit;
        bool is_pressed;
        bool window_event;
        int mouse_x, mouse_y;
};

struct input input_init();
// I'm aware that the naming going on here is bad practice...but I couldn't resist
void input(struct input *input);
