#pragma once

#include <stdbool.h>

#include "misc.h"

// 2 dimensional bit vector
// stored as a vector of bit vectors (not jagged)
// the x dimension can be any arbeitary length, 
// however the y dimension can only be in lengths divisible by 64
typedef struct {
        u64 **_ptr;
        uint width;
        uint height;
} bitgrid;

// creates a bitgrid of capable of holding "x" * "y"
// rounds up in case of not being a multiple of 64
bitgrid bitgrid_init(uint x, uint y);
void bitgrid_fini(bitgrid *bg);

bool bitgrid_get(const bitgrid *bg, uint x, uint y);

void bitgrid_set(bitgrid *bg, uint x, uint y);
void bitgrid_unset(bitgrid *bg, uint x, uint y);
