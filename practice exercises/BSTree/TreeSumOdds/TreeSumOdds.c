
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	// TODO
	if(t == NULL)
		return 0;
	
	int val = (abs(t->value) % 2 == 1) ? t->value : 0;

	return val + TreeSumOdds(t->left) + TreeSumOdds(t->right);
}

