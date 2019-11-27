
#include <stdlib.h>

#include "tree.h"

int t_height(Tree t){
	if(t == NULL)
		return 0;
	
	int l_h = t_height(t->left);
	int r_h = t_height(t->right);

	//return l_h > r_h ? l_h + 1 : r_h + 1; 
	return 1 + l_h + r_h;
}

bool TreeIsPerfectlyBalanced(Tree t) {
	// TODO
	if(t == NULL)
		return true;
	
	int l_h = t_height(t->left);
	int r_h = t_height(t->right);

	if(abs(l_h - r_h) <= 1 && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right))
		return true;

	return false;
}

