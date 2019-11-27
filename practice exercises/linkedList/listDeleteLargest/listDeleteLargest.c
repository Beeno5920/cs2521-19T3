
#include "list.h"

int listDeleteLargest(List l) {
  if(l->head == NULL)
    return 0;
  
  struct node* curr = l->head->next;
  struct node* temp = l->head;
  int out = 0;

  while(curr != NULL){
    if(curr->value > temp->value)
      temp = curr;
    curr = curr->next;
  }
  
  curr = l->head;
  if(curr == temp){
    if(curr->next == NULL){
      out = temp->value;
      free(curr);
      l->head = NULL;
    }else
    l->head = curr->next;
    out = temp->value;
    free(curr);
    return out;
  }
  
  while(curr != NULL){
    if(curr->next == temp){
      curr->next = temp->next;
      out = temp->value;
      free(temp);
      break;
    }
    curr = curr->next;
  }

  return out;
}

