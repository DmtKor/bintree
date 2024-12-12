#ifndef BINTREE
#define BINTREE
    #include "bintree.h"
#endif

#ifndef PANIC
#define PANIC
    #include "panic.h"
#endif


/*
* Free memory used by tree (recursive).
* Parameters:
* node *base - root node of a tree.
*/
void free_tree(node *base) {
    if (!base) return;
    free_tree(base->left);
    free_tree(base->right);
    free(base);
}


/*
* Insert value into binary tree (recursive).
* Parameters:
* int32_t val - value that'll be inserted into tree;
* node *base - root of the tree, shouldn't be empty (NULL or not allocated).
*/
void insert_node(int32_t val, node *base) {
    /* Lesser values go to the left, 
    *  greater to the right,
    *  equal are skipped */
    if (val == base->val) return;
    if (val < base->val) {
        if (base->left) insert_node(val, base->left); 
        else {
            base->left = (node *)malloc(sizeof(node)); // Make new node
            if (!base->left) panic("\nERROR: program failed to allocate memory!", 2);
            base->left->val = val;
            base->left->left = base->left->right = NULL;
        }
    }
    else {
        if (base->right) insert_node(val, base->right);
        else {
            base->right = (node *)malloc(sizeof(node)); // Make new node
            if (!base->right) panic("\nERROR: program failed to allocate memory!", 2);
            base->right->val = val;
            base->right->left = base->right->right = NULL;
        }
    }
}


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
node *make_tree(size_t size, int32_t *values) {
    if (!size) return NULL; // If array is empty
    
    node *base;
    base = (node *)malloc(sizeof(node)); // Tree root
    if (!base) panic("\nERROR: program failed to allocate memory!", 2);
    base->val = values[0];
    base->left = base->right = NULL;

    for (size_t i = 1; i < size; i++) // Filling tree
        insert_node(values[i], base); 
    return base;
}


/*
* Print binary tree (recursive).
* Parameters:
* node *base - root node of a tree;
* int16_t depth - current depth of the node, set 0 when calling;
* char left - 2 for root node, 1 for left child, 0 for right.
*/
void print_tree(node *base, int16_t depth, char left) {
    /* Calling function for left nodes */
    if (base->left) print_tree(base->left, depth + 1, 1);
    putchar('|');
    for (int16_t i = 0; i < depth; i++) 
        putchar('\t');

    /* Printing value */
    if (left == 2) fputs("->", stdout);
    else if (left) putchar('/');
    else putchar('\\');
    printf("%d\n", base->val);

    /* Calling function for right nodes */
    if (base->right) print_tree(base->right, depth + 1, 0);
}


/*
* Compute height of a subtree with root in node 'n' (recursive).
*/
int32_t tree_height(node *n) { 
    if (!n->right && !n->left) return 0; // If node is a leaf
    /* Computing length of right and left branches */
    int32_t right_l, left_l;
    right_l = left_l = 0;
    if (n->left) left_l = tree_height(n->left) + 1;
    if (n->right) right_l = tree_height(n->right) + 1;

    /* Height is chosen by comparing these lengths */
    return right_l > left_l ? right_l : left_l;
 }


/*
* Returns max value of a tree with root in node 'base' (recursive).
*/
int32_t max_node(node *base) { 
    // Right branch always contains bigger value than current node (if it exists)
    if (base->right) return max_node(base->right);
    return base->val;
 }


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
void tree_heights(node *base, size_t *size, int32_t *heights, int32_t *values, size_t *i) {
    /* Static values are common for all function calls */
    static int32_t max_n = 0;
    static char first = 1;
    static size_t i_st = 0;

    /* First call logic */
    if (!i) i = &i_st;
    if (first) {
        first = 0;
        max_n = max_node(base);
    }

    /* Catching potential errors */
    if (*i >= *size) panic("\nERROR: *i value in tree_heights is invalid.", 3);
    if (!base)       panic("\nERROR: *base in tree_heights do not exist.", 3);

    /* Computing heights for left nodes */
    if (base->left) tree_heights(base->left, size, heights, values, i);

    /* Computing height of a current node */
    heights[*i] = tree_height(base);
    values[*i]  = base->val;
    (*i)++;

    /* Computing heights for right nodes */
    if (base->right) tree_heights(base->right, size, heights, values, i);

    /* Last function call will be used at node with max value, here we're setting 
    *  static values to default in case we decide to call this function later */
    if (base->val == max_n) {
        *size = *i;
        first = 1;
        max_n = 0;
        i_st  = 0;
    }
}


/*
* Print children of node n (recursive).
*/
void print_children(node *n) {
    static char first = 1;
    char loc_first = first;
    if (first) {
        printf("\nChildren of node <%d>:\n", n->val);
        if (!n->left && !n->right) {
            puts("No children.");
            return;
        }
        first = 0;
    }

    if (n->left)    print_children(n->left);
    if (n->right)   print_children(n->right);
    if (!loc_first) printf("<%d>", n->val); // Only clidren nodes will be printed
    
    if (loc_first) first = 1; // Set static var to default when done
}


/*
* Returns node with 'val' field equal to 'value' argument. 
* If corresponding node do not exist, returns NULL. Recursive.
*/
node *search_node(node *base, int32_t value) {
    if (value == base->val) return base;
    else if (value < base->val) return base->left ? search_node(base->left, value) : NULL;
    return base->right ? search_node(base->right, value) : NULL;
}