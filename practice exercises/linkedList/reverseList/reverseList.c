
#include "list.h"

void listReverse(List l) {
	// TODO
  if(l->head == NULL || l->head->next == NULL)
    return;
  
  struct node* curr = l->head;
  struct node* ptr;
  struct node* prev = curr;
  for(; curr != NULL; curr = ptr){
    if(curr == l->head){
      curr = curr->next;
      prev->next =  NULL;
    }
    ptr = curr->next;
    curr->next = prev;
    prev = curr;
  }
  l->head = prev;
}

