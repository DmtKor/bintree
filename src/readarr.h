#ifndef INCLUDES
#define INCLUDES
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif

/*
* Read user input into array (it will be allocated here and must be deallocated later), 
* size will be written into address in 'size' pointer.
*/
int32_t *read_array(size_t *size);


