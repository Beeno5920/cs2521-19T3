
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if(t == NULL)
        return -1;
    if(t->left == NULL && t->right == NULL)
        return 0;
    
    int l = TreeHeight(t->left);
    int r = TreeHeight(t->right);

    return l > r ? l + 1: r + 1;

}

