
#include <stdlib.h>

#include "BSTree.h"

int num_node(BSTree t){
	if(t == NULL)
		return 0;
	return 1 + num_node(t->left) + num_node(t->right);
}

int BSTreeGetKth(BSTree t, int k) {
	// TODO
	int count = num_node(t->left);
	if(count == k)
		return t->value;
	if(count > k)
		return BSTreeGetKth(t->left, k);
	else
		return BSTreeGetKth(t->right, k - count - 1);

	return -1;
}

