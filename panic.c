#ifndef PANIC
#define PANIC
    #include "panic.h"
#endif

#ifndef INCLUDES
#define INCLUDES
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif

/*
* Function used to exit program after critical errors
*/
void panic(const char *str, int code) {
    puts(str);
    exit(code);
}


