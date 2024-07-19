#include "../src/bitgrid.h"
#include <criterion/criterion.h>

Test(bitgrid, init) {
        bitgrid bg = bitgrid_init(1, 1);
        cr_assert_eq(bg.width, 1);
        cr_assert_eq(bg.height, 64);
        bitgrid_fini(&bg);
        bg = bitgrid_init(2, 64);
        cr_assert_eq(bg.width, 2);
        cr_assert_eq(bg.height, 64);
        bitgrid_fini(&bg);
        bg = bitgrid_init(2, 65);
        cr_assert_eq(bg.width, 2);
        cr_assert_eq(bg.height, 128);
        bitgrid_fini(&bg);
}


Test(bitgrid, modification) {
        bitgrid bg = bitgrid_init(64, 64);
        cr_assert_eq(bg.width, 64);
        cr_assert_eq(bg.height, 64);
        for (uint x = 0; x < 64; x++)
                for (uint y = 0; y < 64; y++) {
                        cr_assert(!bitgrid_get(&bg, x, y));
                        bitgrid_set(&bg, x, y);
                        cr_assert(bitgrid_get(&bg, x, y));
                        bitgrid_unset(&bg, x, y);
                        cr_assert(!bitgrid_get(&bg, x, y));
                }
        bitgrid_fini(&bg);
}
