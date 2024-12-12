#ifndef INCLUDES
#define INCLUDES
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif

#ifndef PANIC
#define PANIC
    #include "panic.h"
#endif

#define N_TRIES 5 // How many times user can pass wrong value

/*
* Read user input into array (it will be allocated here and must be deallocated later), 
* size will be written into address in 'size' pointer.
*/
int32_t *read_array(size_t *size) {
    int32_t *array;
    if (scanf("%zu", size) != 1) {
        panic("\nInvalid input!", -1);
    }
    /* For some reason printf with %zu still can read negative numbers without errors and interpret them 
    *  like positive (-1 ~ SIZE_MAX) int64_t (max = 9 223 372 036 854 775 807, min = -max - 1) 
    *  should help with processing any possible value of size_t type (which length is at least 16 bit) */
    if ((int64_t)*size <= 1) { 
        panic("\nSize should be greater or equal to zero!", -1);
    }
    array = (int32_t *)malloc(sizeof(int32_t) * *size);
    if (!array) panic("\nERROR: program failed to allocate memory!", 2);

    /* Reading elements */
    for (size_t i = 0; i < *size; i++) {
        while(fgetc(stdin) != '\n'); // Skipping to the next newline
        if (scanf("%d", array + i) != 1) {
            puts("\nInvalid input!");
            exit(-1);
        }
    }
    return array;
}


