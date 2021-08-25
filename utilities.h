// Author: strawberryhacker

#ifndef UTILITIES_H
#define UTILITIES_H

#include "stdint.h"

//--------------------------------------------------------------------------------------------------

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uintptr_t ptr;

//--------------------------------------------------------------------------------------------------

#define limit(value, max) ((int)value > (int)max) ? max : value;

//--------------------------------------------------------------------------------------------------

static inline int align_down(int value, int alignment) {
    return value / alignment * alignment;
}

//--------------------------------------------------------------------------------------------------

static inline int align_up(int value, int alignment) {
    return (value + alignment - 1) / alignment * alignment;
}

//--------------------------------------------------------------------------------------------------

static inline void* pointer_align_down(void* pointer, int alignment) {
    return (void *)((ptr)pointer / (ptr)alignment * (ptr)alignment);
}

//--------------------------------------------------------------------------------------------------

static inline void* pointer_align_up(void* pointer, int alignment) {
    return (void *)(((ptr)pointer + (ptr)alignment - 1) / (ptr)alignment * (ptr)alignment);
}

//--------------------------------------------------------------------------------------------------

static inline void memory_copy(const void* source, void* destination, int size) {
    for (int i = 0; i < size; i++) {
        ((u8 *)destination)[i] = ((const u8 *)source)[i];
    }
}

#endif
