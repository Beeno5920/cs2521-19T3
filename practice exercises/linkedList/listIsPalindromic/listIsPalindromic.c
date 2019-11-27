
#include "list.h"

bool listIsPalindromic(List l) {
	// TODO
  if(l->size == 0 || l->size == 1)
    return true;
  
  struct node* head = l->first;
  struct node* tail = l->last;

  for(; head->next != tail && head != tail; head = head->next, tail = tail->prev){
    if(head->value != tail->value)
      return false;
  }

  if(l->size % 2 == 0)
    return (head->value == tail->value);
  
  return (head->value == tail->value);
}

