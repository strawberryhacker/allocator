// Author: strawberryhacker

#include "stdio.h"
#include "allocator.h"

//--------------------------------------------------------------------------------------------------

int main() {
    allocator_init();

    while (1) {
        int* number = allocate(sizeof(int));
        if (number == 0)
            break;

        printf("Total = %d, used = %d\n", allocator_get_capacity(), allocator_get_used());
    }

    return 0;
}
