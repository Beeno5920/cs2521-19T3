// A singly linked list of integers

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
	l->head = NULL;
	return l;
}

List readList(void) {
	char buf[MAX_LINE_LEN + 2] = {0};
	fgets(buf, MAX_LINE_LEN + 2, stdin);
	return strToList(buf);
}

static List strToList(char *s) {
	char *copy = myStrdup(s);
	Node head = NULL;
	Node curr = NULL;
	char *token = strtok(copy, " \n\t");
	while (token != NULL) {
		Node n = newNode(atoi(token));
		if (head == NULL) {
			head = n;
		} else {
			curr->next = n;
		}
		curr = n;
		token = strtok(NULL, " \n\t");
	}
	free(copy);
	List l = newList();
	l->head = head;
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
	return n;
}

void freeList(List l) {
	Node curr = l->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(l);
}

void printList(List l) {
	Node curr = l->head;
	while (curr != NULL) {
		printf("[%d] -> ", curr->value);
		curr = curr->next;
	}
	printf("X\n");
}

////////////////////////////////////////////////////////////////////////
// The functions below are used to check that certain rules are followed

static int listLength(List l);

NodeData *getListNodeData(List l) {
	int len = listLength(l);
	NodeData *addrs = malloc((len + 1) * sizeof(NodeData));
	int i = 0;
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
		addrs[i].addr = curr;
		addrs[i].value = curr->value;
		i++;
	}
	addrs[i].addr = NULL;
	return addrs;
}

bool noNewNodes(NodeData *before, NodeData *after) {
	for (int i = 0; after[i].addr != NULL; i++) {
		bool isNew = true;
		for (int j = 0; before[j].addr != NULL; j++) {
			if (after[i].addr == before[j].addr) {
				isNew = false;
				break;
			}
		}
		if (isNew) return false;
	}
	return true;
}

bool noChangedValues(NodeData *before, NodeData *after) {
	for (int i = 0; after[i].addr != NULL; i++) {
		for (int j = 0; before[j].addr != NULL; j++) {
			if (after[i].addr == before[j].addr) {
				if (after[i].value != before[j].value) {
					return false;
				}
				break;
			}
		}
	}
	return true;
}

bool notModified(NodeData *before, NodeData *after) {
	int i = 0;
	while (after[i].addr != NULL && before[i].addr != NULL) {
		if (after[i].addr != before[i].addr ||
				after[i].value != before[i].value) {
			return false;
		}
		i++;
	}
	return (before[i].addr == NULL && after[i].addr == NULL);
}

static int listLength(List l) {
	int length = 0;
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
		length++;
	}
	return length;
}

