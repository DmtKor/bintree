#ifndef INCLUDES
#define INCLUDES
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdio.h>
#endif


/*
* Data type for binary tree node.
* Fields:
* int_32t val - value of node;
* node *right, *left - right and left child nodes (NULL if empty);
* There is no need to store parent node in this program.
*/
typedef struct tree_node {
    int32_t val;
    struct tree_node *left, *right;
} node;


/*
* Free memory used by tree (recursive).
* Parameters:
* node *base - root node of a tree.
*/
void free_tree(node *base);

/*
* Insert value into binary tree (recursive).
* Parameters:
* int32_t val - value that'll be inserted into tree;
* node *base - root of the tree, shouldn't be empty (NULL or not allocated).
*/
void insert_node(int32_t val, node *base);

/*
* Make tree using array of integers.
* Parameters:
* size_t size - exact size of array, if it's too small function will return unexpected output,
*               if it's too big, it will likely cause segmentation fault;
* int32_t *values - array, that will be used to generate tree.
* Returns:
* Pointer to the root of a tree (should be deallocated with free_node function when not needed);
* May return NULL if something goes wrong.
*/
node *make_tree(size_t size, int32_t *values);

/*
* Print binary tree (recursive).
* Parameters:
* node *base - root node of a tree;
* int16_t depth - current depth of the node, set 0 when calling;
* char left - 2 for root node, 1 for left child, 0 for right.
*/
void print_tree(node *base, int16_t depth, char left);

/*
* Compute height of a subtree with root in node 'n' (recursive).
*/
int32_t tree_height(node *n);

/*
* Returns max value of a tree with root in node 'base' (recursive).
*/
int32_t max_node(node *base);

/*
* Compute height of a tree (or subtree) (recursive).
* Arguments:
* node *base - root node of a tree;
* int32_t *size - pointer to the variable with size of arrays (listed below), if tree size is lesser, 
*             this variable will change;
* int32_t *heights - array of size 'size' will contain heights of the nodes listed in 'values';
* int32_t *values - array of size 'size' will contain values of nodes;
* size_t *i - current index in arrays above. When calling, just pass NULL.
*/
void tree_heights(node *base, size_t *size, int32_t *heights, int32_t *values, size_t *i);

/*
* Print children of node n (recursive).
*/
void print_children(node *n);

/*
* Returns node with 'val' field equal to 'value' argument. 
* If corresponding node do not exist, returns NULL. Recursive.
*/
node *search_node(node *base, int32_t value);




