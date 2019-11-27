
#include "list.h"

void reverseDLList(List l) {
	// TODO
  if(l->size == 0 || l->size == 1)
    return;

  struct node* curr = l->first;
  struct node* temp = NULL;
  l->last = l->first;
  while(curr != NULL){
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  
  l->first = temp->prev;
}

