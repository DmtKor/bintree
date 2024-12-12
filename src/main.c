#ifndef BINTREE
#define BINTREE
    #include "bintree.h"
#endif

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

#ifndef READARR
#define READARR
    #include "readarr.h"
#endif



/* Main function */
int main() {
    /* Vars */
    int32_t *array, *values, *heights, *same_heights;
    size_t size, new_size, same_n;
    node *tree, *n;
    char c, next;

    /* Reading and printing array with data */
    array = read_array(&size);
    printf("Array of size %zu:\n", size);
    c = ';';
    for (size_t i = 0; i < size; i++, c = i == size - 1 ? '.' : ';') 
        printf("[№%zu]: %d%c\n", i + 1, array[i], c);

    /* Creating and printing tree, deallocating array */
    tree = make_tree(size, array);
    free(array); 
    puts("\nTree:");
    print_tree(tree, 0, 2);
    
    /* Computing heights of the tree nodes */
    heights = (int32_t *)malloc(sizeof(int32_t) * size);
    if (!heights) panic("\nERROR: program failed to allocate memory!", 2);
    values = (int32_t *)malloc(sizeof(int32_t) * size);
    if (!values) panic("\nERROR: program failed to allocate memory!", 2);
    new_size = size;
    tree_heights(tree, &new_size, heights, values, NULL);

    /* Searching for all nodes with same height and listing their children */
    next = 0;
    same_n = 0;
    same_heights = (int32_t *)malloc(sizeof(int32_t) * new_size);
    if (!same_heights) panic("\nERROR: program failed to allocate memory!", 2);
    puts("\n");
    for (size_t i = 0; i < new_size; i++) {
        /* Setting 'same_heights' to default */
        for (size_t j = 0; j < new_size; j++) same_heights[j] = -1;
        /* Comparing height to previous nodes, skip if there are same before */
        next = 0;
        for (size_t j = 0; j < i; j++) {
            if (heights[j] == heights[i]) {
                next = 1;
                break;
            }
        }
        if (next) {
            next = 0;
            continue;
        }
        /* Search for nodes with same height, list their children if there is more than one */
        same_n = 1;
        same_heights[0] = values[i];
        for (size_t j = i + 1; j < new_size; j++) {
            if (heights[j] == heights[i]) {
                size_t index;
                for(index = 0; same_heights[index] != -1; index++) {;}
                same_heights[index] = values[j];
                same_n++;
            }
        }
        if (same_n > 1) {
            puts("--------------------------------------------------");
            printf("Nodes with height %d and their children:\n", heights[i]);
            for (size_t j = 0; j < same_n; j++) {
                n = search_node(tree, same_heights[j]);
                if (n) { 
                    print_children(n);
                    puts("\n");
                    print_tree(n, 0, 2);
                    putchar('\n');
                }
            }
            puts("\n--------------------------------------------------");
        }
    }

    /* Deallocating memory */
    free(same_heights);
    free(heights);
    free(values);
    free_tree(tree);

    return 0;
}