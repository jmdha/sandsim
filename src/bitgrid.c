#include "bitgrid.h"
#include <stdlib.h>

bitgrid bitgrid_init(uint x, uint y) {
        if (x == 0 || y == 0)
                abort();
        if (y != 64)
                y += 64 - (y % 64);
        u64 **ptr = malloc(x * sizeof(u64 *));
        for (uint i = 0; i < x; i++)
                ptr[i] = calloc((y / 64), sizeof(u64));
        bitgrid bg = {.width = x, .height = y, ._ptr = ptr};
        return bg;
}

void bitgrid_fini(bitgrid *bg) {
        for (uint i = 0; i < bg->width; i++)
                free(bg->_ptr[i]);
        free(bg->_ptr);
}

bool bitgrid_get(const bitgrid *bg, uint x, uint y) {
        return bg->_ptr[x][y / 64] & (1ull << (y % 64));
}

void bitgrid_set(bitgrid *bg, uint x, uint y) {
        bg->_ptr[x][y / 64] |= (1ull << (y % 64));
}

void bitgrid_unset(bitgrid *bg, uint x, uint y) {
        bg->_ptr[x][y / 64] &= ~(1ull << (y % 64));
}
