
#include "list.h"

bool listIsOrdered(List l) {
	// TODO
  if(l->head == NULL)
    return true;
  
  struct node* curr = l->head->next;
  struct node* next_one = curr->next;
  int order = curr->value - l->head->value;
  while(next_one != NULL){
    if(order > 0){
      if(curr->value > next_one->value)
	return false;
    }else if(order < 0){
      if(curr->value < next_one->value)
	return false;
    }
    curr = next_one;
    next_one = next_one->next;
  }

  return true;
}

