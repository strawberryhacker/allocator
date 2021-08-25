// Author: strawberryhacker

#include "allocator.h"
#include "assert.h"

//--------------------------------------------------------------------------------------------------

#define ALIGNMENT   8
#define MEMORY_SIZE 1024 * 1024  // Set this to the memory size managed by the allocator.

//--------------------------------------------------------------------------------------------------

typedef struct Block Block;
struct Block {
    Block*  next;
    int     size;
};

typedef struct {
    Block   dummy_block;
    Block*  dummy;
    Block*  last;
    int     capacity;
    int     used;
} ListAllocator;

//--------------------------------------------------------------------------------------------------

static ListAllocator list_allocator;
static u8 memory[MEMORY_SIZE];

//--------------------------------------------------------------------------------------------------

void allocator_init() {
    u8* memory_start = pointer_align_up(memory, ALIGNMENT);
    u8* memory_end = pointer_align_down(memory + MEMORY_SIZE, ALIGNMENT);

    memory_end -= sizeof(Block);

    list_allocator.capacity = memory_end - memory_start;
    list_allocator.used = 0;

    Block* start = (Block *)memory_start;
    Block* end   = (Block *)memory_end;

    start->size = list_allocator.capacity;
    start->next = end;
    
    end->size = 0;
    end->next = 0;

    list_allocator.dummy = &list_allocator.dummy_block;
    list_allocator.dummy->size = 0;
    list_allocator.dummy->next = start;
    list_allocator.last = end;
}

//--------------------------------------------------------------------------------------------------

int allocator_get_capacity() {
    return list_allocator.capacity;
}

//--------------------------------------------------------------------------------------------------

int allocator_get_used() {
    return list_allocator.used;
}

//--------------------------------------------------------------------------------------------------

static void insert_block(Block* block) {
    Block* it;
    for (it = list_allocator.dummy; it && (ptr)it->next <= (ptr)block; it = it->next);

    // Check for backward coalescing.
    if ((ptr)it + it->size == (ptr)block) {
        it->size += block->size;
        block = it;
    }

    // Check for forward coalescing.
    if ((ptr)block + block->size == (ptr)block && it->next != list_allocator.last) {
        block->size += it->next->size;
        block->next = it->next->next;
    }
    else {
        block->next = it->next;
    }

    // Fix the pointers in case of backward coalescing.
    if (block != it) {
        it->next = block;
    }
}

//--------------------------------------------------------------------------------------------------

void* allocate(int size) {
    size = align_up(size + sizeof(Block), ALIGNMENT);

    Block* previous = list_allocator.dummy;
    Block* current = list_allocator.dummy->next;

    while (current && current->size < size) {
        previous = current;
        current = current->next;
    }

    if (current == 0) {
        return 0;
    }

    previous->next = current->next;

    // Split the current block if it can contain the current allocation plus a new one.
    if (current->size - size >= sizeof(Block) + ALIGNMENT) {
        Block* block = (Block *)((u8 *)current + size);
        block->size = current->size - size;
        current->size = size;
        insert_block(block);
    }

    list_allocator.used += current->size;
    return current + 1;
}

//--------------------------------------------------------------------------------------------------

void free(void* pointer) {
    assert(pointer);
    Block* block = (Block *)pointer - 1;
    list_allocator.used -= block->size;
    insert_block(block);
}
