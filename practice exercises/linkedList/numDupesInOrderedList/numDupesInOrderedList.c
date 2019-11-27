
#include "list.h"

int numDupesInOrderedList(List l) {
	// TODO
  if(l->head == NULL)
    return 0;
  
  struct node* curr = l->head;
  int numOfDupes = 0;
  
  while(curr->next != NULL){
    if(curr->value == curr->next->value){
      numOfDupes++;
    }
    curr = curr->next;
  }
  return numOfDupes;
}

