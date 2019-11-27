
#include "list.h"

List listSetUnion(List s1, List s2) {
	// TODO
  List s1_c = listSortedCopy(s1);
  List s2_c = listSortedCopy(s2);
  
  if(s1->head == NULL){
    freeList(s1_c);
    return s2_c;
  }
  if(s2->head == NULL){
    freeList(s2_c);
    return s1_c;
  }

  List s3;
  struct node* curr1 = s1_c->head;
  for(; curr1->next != NULL; curr1 = curr1->next){}

  curr1->next = s2_c->head;

  s3 = listSortedCopy(s1_c);
  curr1->next = NULL;
  struct node* curr = s3->head->next; 
  for(struct node* prev = s3->head; curr != NULL;){
    if(curr->value == prev->value){
      curr = curr->next;
      free(prev->next);
      prev->next = curr;
      continue;
    }
    prev = curr;
    curr = curr->next;
  }
  freeList(s1_c);
  freeList(s2_c);
  
  return s3;
}

