
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	// TODO
	if(t == NULL){
		BSTree node = newBSTNode(val);
		return node;
	}

	BSTree tmp = t;
	while(tmp != NULL){
		if (val == tmp->value){
			break;
		}else if(val > tmp->value && tmp->right == NULL){
			BSTree node = newBSTNode(val);
			tmp->right = node;
			break;
		}else if(val < tmp->value && tmp->left == NULL){
			BSTree node = newBSTNode(val);
			tmp->left = node;
			break;
		}
		
		if(val > tmp->value)
			tmp = tmp->right;
		else
			tmp = tmp->left;
		
	}

	return t;
}

