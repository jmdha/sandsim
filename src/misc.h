#pragma once

#include <stdint.h>

// clang-format off

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned int uint;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// clang-format on

#define max(a, b)                                                              \
        ({                                                                     \
                __typeof__(a) _a = (a);                                        \
                __typeof__(b) _b = (b);                                        \
                _a > _b ? _a : _b;                                             \
        })

#define min(a, b)                                                              \
        ({                                                                     \
                __typeof__(a) _a = (a);                                        \
                __typeof__(b) _b = (b);                                        \
                _a < _b ? _a : _b;                                             \
        })
