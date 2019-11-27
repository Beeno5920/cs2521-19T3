
#include "list.h"

List listSetIntersection(List s1, List s2) {
	// TODO
	List s3 = newList();
	struct node* curr3 = s3->head;
	List s1_c = listSortedCopy(s1);
	List s2_c = listSortedCopy(s2);

	if(s1->head == NULL || s2->head == NULL)
		return s3;
	
	struct node* curr1 = s1_c->head;
	struct node* curr2 = s2_c->head;
	for(; curr1 != NULL && curr2 != NULL;){

		if(curr1->value == curr2->value){
			struct node* new_node = newNode(curr1->value);
			if(s3->head == NULL)
				s3->head = curr3 = new_node;
			else{
				curr3->next = new_node;
				curr3 = curr3->next;
			}
			curr1 = curr1->next;
			curr2 = curr2->next;
			continue;
		}

		if(curr1->value > curr2->value)
			curr2 = curr2->next;
		else
			curr1 = curr1->next;
	}

	freeList(s1_c);
	freeList(s2_c);
	return s3;

}

