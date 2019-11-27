// A doubly linked list of integers

#ifndef LIST_H
#define LIST_H

#include <stdbool.h> // Provides the constants 'true' and 'false'
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 1024

typedef struct node *Node;
struct node {
	int value;
	Node next;
	Node prev;
};

typedef struct list *List;
struct list {
	Node first;
	Node last;
	int size;
};

/**
 * Creates a new, empty list
 */
List newList(void);

/**
 * Reads  in  a line of integers from stdin and converts it into a list.
 * Assumes  that the line consists entirely of space-separated integers,
 * and that the line is no longer than 1024 characters.
 */
List readList(void);

void freeList(List l);

void printList(List l);

#endif

