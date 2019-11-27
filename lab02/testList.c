// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"
void status(DLList L);
void test_DLListBefore(DLList L, int n);
void test_DLListMoveTo(DLList L, int n);
void test_DLListMove(DLList L, int n);
void test_DLListAfter(DLList L, int n);
void test_DLListDelete(DLList L, int n);

int main (void)
{
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));

	// TODO: more tests needed here
	printf("========== Testing DLListBefore() ===========\n");
	status(myList);
	test_DLListBefore(myList, 10);
	assert (validDLList (myList));

	printf("========== Testing DLListMoveTo() ===========\n");
	test_DLListMoveTo(myList, 4);
	assert (validDLList (myList));
	test_DLListMoveTo(myList, 10000);
	assert (validDLList (myList));
	test_DLListMoveTo(myList, 6);
	assert (validDLList (myList));
	printf("The current List is:\n");
	putDLList(stdout, myList);
	
	printf("========== Testing DLListMove() =============\n");
	test_DLListMove(myList, 3);
	assert (validDLList (myList));
	test_DLListMove(myList, -1);
	assert (validDLList (myList));
       	test_DLListMove(myList, 314159);
	assert (validDLList (myList));
	test_DLListMove(myList, -20000);
	assert (validDLList (myList));
	printf("The current list is:\n");
	putDLList(stdout, myList);

	printf("========== Testing DLListAfter() ============\n");
	DLListMoveTo(myList, 2);
	test_DLListAfter(myList, 3);
	assert (validDLList (myList));

	printf("========== Testing DLListDelete() ===========\n");
	status(myList);
	test_DLListDelete(myList, 4);
	assert (validDLList (myList));

	printf("========== Finished all the tests =========\n");

	freeDLList (myList);
	return EXIT_SUCCESS;
}

void status(DLList L){
  assert(validDLList(L));
  if(DLListLength(L)){
    
    printf("> number of items: %zu\n", DLListLength(L));
    printf("> current is: %s\n", DLListCurrent(L));
    //printf("first is: %s\n", L->first->value);
    //printf("last is: %s\n", L->last->value);
  }
}

void test_DLListBefore(DLList L, int n){
  printf("Inserting %d items before the current node\n", n);
  for(int i = 0; i < n; i++){
    char str[2];
    sprintf(str, "%d", i);
    DLListBefore(L, str);
  }
  status(L);
  printf("The current list:\n");
  putDLList(stdout, L);
}

void test_DLListMoveTo(DLList L, int n){
  printf("Moving cursor to position %d\n", n);
  DLListMoveTo(L, n);
  status(L);
}

void test_DLListMove(DLList L, int n){
  if(n > 0)
    printf("Moving %d steps forward\n", n);
  if(n < 0)
    printf("Moving %d steps backward\n", -n);
  DLListMove(L, n);
  status(L);
}

void test_DLListAfter(DLList L, int n){
  printf("Inserting %d items after the current node\n", n);
  for(int i = 20, k = i + n; i < k; i++){
    char str[10];
    sprintf(str, "%d", i);
    DLListAfter(L, str);
  }
  status(L);
  printf("The current list:\n");
  putDLList(stdout, L);
}

void test_DLListDelete(DLList L, int n){
  printf("Deleting %d item(s)\n", n);
  for(int i = 0; i < n; i++){
    DLListDelete(L);
    status(L);
  }
  printf("The current list:\n");
  putDLList(stdout, L);
}
