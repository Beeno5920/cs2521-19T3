
#include <stdio.h>

#include "list.h"

void reverseList2(List l);

int main(void) {
	printf("Enter list: ");
	List l = readList();

	printf("\nOriginal list:\n");
	printList(l);

	reverseList2(l);
	printf("\nReversed list:\n");
	printList(l);

	freeList(l);
}

