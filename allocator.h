// Author: strawberryhacker

#ifndef LIST_ALLOCATOR_H
#define LIST_ALLOCATOR_H

#include "utilities.h"

//--------------------------------------------------------------------------------------------------

void allocator_init();
int allocator_get_capacity();
int allocator_get_used();
void* allocate(int size);
void free(void* pointer);

#endif
