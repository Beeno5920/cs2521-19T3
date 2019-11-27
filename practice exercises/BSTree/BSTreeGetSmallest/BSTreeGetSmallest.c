
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if(t == NULL)
		return t;
	if(t->left == NULL)
		return t;

	return BSTreeGetSmallest(t->left);
}

