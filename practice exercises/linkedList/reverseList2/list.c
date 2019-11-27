// A doubly linked list of integers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static List strToList(char *s);
static char *myStrdup(char *s);
static Node newNode(int value);

List newList(void) {
	List l = malloc(sizeof(*l));
	if (l == NULL) {
		fprintf(stderr, "couldn't allocate list\n");
		exit(EXIT_FAILURE);
	}
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	return l;
}

List readList(void) {
	char buf[MAX_LINE_LEN + 2] = {0};
	fgets(buf, MAX_LINE_LEN + 2, stdin);
	return strToList(buf);
}

static List strToList(char *s) {
	char *copy = myStrdup(s);
	List l = newList();
	char *token = strtok(copy, " \n\t");
	while (token != NULL) {
		Node n = newNode(atoi(token));
		if (l->first == NULL) {
			l->first = n;
		} else {
			l->last->next = n;
			n->prev = l->last;
		}
		l->last = n;
		l->size++;
		token = strtok(NULL, " \n\t");
	}
	free(copy);
	return l;
}

static char *myStrdup(char *s) {
	char *copy = malloc((strlen(s) + 1) * sizeof(char));
	strcpy(copy, s);
	return copy;
}

static Node newNode(int value) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate node\n");
		exit(EXIT_FAILURE);
	}
	n->value = value;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

void freeList(List l) {
	Node curr = l->first;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(l);
}

void printList(List l) {
	Node curr;
	printf("Size: %d\n", l->size);
	
	printf("Forwards:  ");
	curr = l->first;
	while (curr != NULL) {
		printf("[%d] -> ", curr->value);
		curr = curr->next;
	}
	printf("X\n");

	printf("Backwards: ");
	curr = l->last;
	while (curr != NULL) {
		printf("[%d] -> ", curr->value);
		curr = curr->prev;
	}
	printf("X\n");
}

