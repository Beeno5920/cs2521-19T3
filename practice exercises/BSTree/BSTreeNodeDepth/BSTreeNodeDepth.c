
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	if(t != NULL && t->value == key)
		return 0;

	if(t == NULL || (t->left == NULL && t->right == NULL))
		return -1;

	int depth =  key > t->value ? BSTreeNodeDepth(t->right, key) : BSTreeNodeDepth(t->left, key);

	return depth == -1 ? -1 : depth + 1;
}

