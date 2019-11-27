// testTextbuffer.c
// A stub file for you to test your textbuffer implementation.
// Note that you will NOT be submitting this - this is simply for you to
// test  your  functions as you go. We will have our own testTexbuffer.c
// for testing your submission.

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

void testNewTB();
void testAddPrefixTB();
void testMergeTB();
void testCutTB();
void testSearchTB();
void testPasteTB();
void testDeleteTB();
void testFormRichText();
void testDiffTB();


int main(void) {
	
	testNewTB();
	
	// TODO: Call more test functions
	testAddPrefixTB();
	testMergeTB();
	testCutTB();
	testSearchTB();
	testDeleteTB();
	testPasteTB();
	testFormRichText();
	testDiffTB();


	printf("All tests passed! You are awesome!\n");
}

void testNewTB() {
	printf("-----------------------------------------\n"
	       "               newTB tests               \n"
	       "-----------------------------------------\n");

	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	// Calling dumpTB immediately after newTB, without modifying the TB
	
	//printf("ok1\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, false); // Don't show line numbers
	printf("%s\n", text1);
	//assert(strcmp("hello there,\nhow\nare\nthings\n", text1) == 0);
	printf(">> pass without containing line numbers\n\n");
	free(text1);

	char* text2 = dumpTB(tb1, true); // Show line numbers
	printf("%s\n", text2);
	//assert(strcmp("1. hello there,\n2. how\n3. are\n4. things\n", text2) == 0);
	printf(">> pass with containing line numbers\n\n");
	free(text2);

	releaseTB(tb1);
	// TODO: Add more tests

	TB tb2 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");
	char* text3 = dumpTB(tb2, true);
	printf("%s\n", text3);
	free(text3);

	releaseTB(tb2);

	TB tb3 = newTB("");
	char* text4 = dumpTB(tb3, true);
	printf("%s\n", text4);
	free(text4);

	releaseTB(tb3);

	TB tb4 = newTB("\n");
	char* text5 = dumpTB(tb4, true);
	printf("%s\n", text5);
	free(text5);

	releaseTB(tb4);
}

// TODO: Add more test functions here
void testAddPrefixTB(){
	printf("-----------------------------------------\n"
	       "             addPrefixTB tests           \n"
	       "-----------------------------------------\n");
	
	TB tb = newTB("room\nmoon\ncow jumping over the moon\nlight\n");
	assert(linesTB(tb) == 4);
	addPrefixTB(tb, 1, 3, "goodlight ");
	printf("> adding prefix: \"goodlight \" from line 1 to line 3\n");
	char *text1 = dumpTB(tb, false); // Don't show line numbers
	printf("%s\n", text1);
	free(text1);
	
	char* text2 = dumpTB(tb, true); // Show line numbers
	printf("%s\n", text2);
	free(text2);
	
	releaseTB(tb);

	TB tb2 = newTB("room\nmoon\ncow jumping over the moon\nlight\n");
	addPrefixTB(tb2, 1, 1, "WoooooooooooooooooooooooooooooW ");
	printf("> adding prefix: \"WoooooooooooooooooooooooooooooW \" from line 1 to line 1\n");
	char *text3 = dumpTB(tb2, true); 
	printf("%s\n", text3);
	free(text3);
	
	releaseTB(tb2);

	TB tb3 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");
	addPrefixTB(tb3, 1, 3, "<>><><>><><>");
	printf("> adding prefix: \"<>><><>><><>\" from line 1 to line 100\n");
	char *text4 = dumpTB(tb3, true); 
	printf("%s\n", text4);
	free(text4);
	
	releaseTB(tb3);

	
	TB tb4 = newTB("hello there,\nhow\nare\nthings\n");
	addPrefixTB(tb4, 1, 2, "");
	printf("> adding prefix: \"\" from line 1 to line 2\n");
	char *text5 = dumpTB(tb4, true); 
	printf("%s\n", text5);
	free(text5);
	
	releaseTB(tb4);
	
}

void testMergeTB(){
	printf("-----------------------------------------\n"
	       "              mergeTB tests              \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb2 = newTB("room\nmoon\ncow jumping over the moon\nlight\n");

	char* text1 = dumpTB(tb1, true);
	printf("Original text 1: \n%s\n", text1);
	free(text1);

	char* text2 = dumpTB(tb2, true);
	printf("Original text 2: \n%s\n", text2);
	free(text2);

	printf("-----Mearge text 2 into text 1 at line 4-----\n");

	mergeTB(tb1, 4, tb2);
	char* text = dumpTB(tb1, true);
	printf("%s\n", text);
	free(text);

	releaseTB(tb1);

	printf("---------------------------------------------\n");

	TB tb3 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");
	TB tb4 = newTB("hello there,\nhow\nare\nthings\n");
	
	char* text3 = dumpTB(tb3, true);
	printf("Original text 3: \n%s\n", text3);
	free(text3);

	char* text4 = dumpTB(tb4, true);
	printf("Original text 4: \n%s\n", text4);
	free(text4);

	printf("-----Mearge text 4 into text 3 at line 1-----\n");

	mergeTB(tb3, 1, tb4);
	char* text5 = dumpTB(tb3, true);
	printf("%s\n", text5);
	free(text5);

	releaseTB(tb3);

	printf("---------------------------------------------\n");

	TB tb5 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb6 = newTB("room\nmoon\ncow jumping over the moon\nlight\n");

	char* text6 = dumpTB(tb5, true);
	printf("Original text 5: \n%s\n", text6);
	free(text6);

	char* text7 = dumpTB(tb6, true);
	printf("Original text 6: \n%s\n", text7);
	free(text7);

	printf("-----Mearge text 6 into text 5 at line 5-----\n");

	mergeTB(tb5, 5, tb6);
	char* text8 = dumpTB(tb5, true);
	printf("%s\n", text8);
	free(text8);

	releaseTB(tb5);

	printf("---------------------------------------------\n");

	TB tb7 = newTB("");
	TB tb8 = newTB("");

	char* text9 = dumpTB(tb7, true);
	printf("Original text 7: \n%s\n", text9);
	free(text9);

	char* text10 = dumpTB(tb8, true);
	printf("Original text 8: \n%s\n", text10);
	free(text10);

	printf("-----Mearge text 8 into text 7 at line 1-----\n");

	mergeTB(tb7, 1, tb8);
	char* text11 = dumpTB(tb7, true);
	printf("%s\n", text11);
	free(text11);

	releaseTB(tb7);

}

void testCutTB(){
	printf("-----------------------------------------\n"
	       "                cutTB tests              \n"
	       "-----------------------------------------\n");
	TB tb1 = newTB("A well a everybody\'s heard about the bird\nB-b-b bird, bird, bird, b-bird\'s the word\nA well a bird, bird, bird, the bird is the word\nA well a bird, bird, bird, well the bird is the word\nA well a bird, bird, bird, b-bird\'s the word\n");

	char* text1 = dumpTB(tb1, true);
	printf("%s\n", text1);
	free(text1);

	printf("-----Cut line 2 to 4-----\n\n");
	TB tb2 = cutTB(tb1, 2, 4);

	char* text3 = dumpTB(tb1, true);
	printf("Original: \n%s\n", text3);
	free(text3);

	releaseTB(tb1);

	char* text2 = dumpTB(tb2, true);
	printf("Cut: \n%s\n", text2);
	free(text2);
	if(tb2 != NULL)
		releaseTB(tb2);

	printf("---------------------------------------------\n");

	TB tb3 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");

	char* text4 = dumpTB(tb3, true);
	printf("%s\n", text4);
	free(text4);

	printf("-----Cut line 1 to 8-----\n\n");
	TB tb4 = cutTB(tb3, 1, 8);

	char* text5 = dumpTB(tb3, true);
	printf("Original: \n%s\n", text5);
	free(text5);

	releaseTB(tb3);

	char* text6 = dumpTB(tb4, true);
	printf("Cut: \n%s\n", text6);
	free(text6);
	if(tb4 != NULL)
		releaseTB(tb4);

	printf("---------------------------------------------\n");

	TB tb5 = newTB("Hello World My\nname is jarred lovegood\nand i love carley ray jepson\n");

	char* text7 = dumpTB(tb5, true);
	printf("%s\n", text7);
	free(text7);

	printf("-----Cut line 1 to 1-----\n\n");
	TB tb6 = cutTB(tb5, 1, 1);

	char* text8 = dumpTB(tb5, true);
	printf("Original: \n%s\n", text8);
	free(text8);

	releaseTB(tb5);

	char* text9 = dumpTB(tb6, true);
	printf("Cut: \n%s\n", text9);
	free(text9);
	if(tb6 != NULL)
		releaseTB(tb6);
	
}

void testSearchTB(){
	printf("-----------------------------------------\n"
	       "             searchTB tests              \n"
	       "-----------------------------------------\n");

	TB tb1 = newTB("Hello World My\nname is jarred lovegood\nand i love carley ray jepson\n");
	TB tb2 = newTB("A well a everybody\'s heard about the bird\nB-b-b bird, bird, bird, b-bird\'s the word\nA well a bird, bird, bird, the bird is the word\nA well a bird, bird, bird, well the bird is the word\nA well a bird, bird, bird, b-bird\'s the word\n");
	TB tb3 = newTB("abracadabra alacazam\nabracadabracadabracadabracadabra\n");
	TB tb4 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");
	Match m1 = searchTB(tb1, "love");
	Match m2 = searchTB(tb2, "bird");
	Match m3 = searchTB(tb3, "abracadabra");
	Match m4 = searchTB(tb4, "assignment");
	Match m5 = searchTB(tb4, "draft");

	char* text1 = dumpTB(tb1, true);
	printf("%s\nSearching result of \"love\" (line, index): \n", text1);
	free(text1);
	for(Match cur = m1; cur != NULL; cur = cur->next)
		printf("(%d, %d) --> ", cur->lineNumber, cur->columnNumber);
	printf("X\n\n");

	char* text2 = dumpTB(tb2, true);
	printf("%s\nSearching result of \"bird\" (line, index): \n", text2);
	free(text2);
	for(Match cur = m2; cur != NULL; cur = cur->next)
		printf("(%d, %d) --> ", cur->lineNumber, cur->columnNumber);
	printf("X\n\n");

	char* text3 = dumpTB(tb3, true);
	printf("%s\nSearching result of \"abracadabra\" (line, index): \n", text3);
	free(text3);
	for(Match cur = m3; cur != NULL; cur = cur->next)
		printf("(%d, %d) --> ", cur->lineNumber, cur->columnNumber);
	printf("X\n\n");

	char* text4 = dumpTB(tb4, true);
	printf("%s\nSearching result of \"assignment\" (line, index): \n", text4);
	free(text4);
	for(Match cur = m4; cur != NULL; cur = cur->next)
		printf("(%d, %d) --> ", cur->lineNumber, cur->columnNumber);
	printf("X\n\n");
	char* text5 = dumpTB(tb4, true);
	printf("%s\nSearching result of \"draft\" (line, index): \n", text5);
	free(text5);
	for(Match cur = m5; cur != NULL; cur = cur->next)
		printf("(%d, %d) --> ", cur->lineNumber, cur->columnNumber);
	printf("X\n\n");

	releaseTB(tb1);
	releaseTB(tb2);
	releaseTB(tb3);
	releaseTB(tb4);

   	for(Match tmp; m1 != NULL;){
       tmp = m1;
       m1 = m1->next;
       free(tmp);
    }

	for(Match tmp; m2 != NULL;){
       tmp = m2;
       m2 = m2->next;
       free(tmp);
    }

	for(Match tmp; m3 != NULL;){
       tmp = m3;
       m3 = m3->next;
       free(tmp);
    }

	for(Match tmp; m4 != NULL;){
       tmp = m4;
       m4 = m4->next;
       free(tmp);
    }

	for(Match tmp; m5 != NULL;){
       tmp = m5;
       m5 = m5->next;
       free(tmp);
    }
}

void testDeleteTB(){
	printf("-----------------------------------------\n"
	       "             DeleteTB tests              \n"
	       "-----------------------------------------\n");

	TB tb = newTB("hello there,\nhow\nare\nthings\n");
	char* text1 = dumpTB(tb, true);
	printf("Original: \n%s\n", text1);
	free(text1);

	printf("-----delete line 1 to 2-----\n");
	deleteTB(tb, 1, 2);
	char* text2 = dumpTB(tb, true);
	printf("After deleted: \n%s\n", text2);
	free(text2);

	releaseTB(tb);

	printf("---------------------------------------------\n");

	TB tb2 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");

	char* text3 = dumpTB(tb2, true);
	printf("Original: \n%s\n", text3);
	free(text3);

	printf("-----delete line 8 to 8-----\n");
	deleteTB(tb2, 8, 8);
	char* text4 = dumpTB(tb2, true);
	printf("After deleted: \n%s\n", text4);
	free(text4);

	releaseTB(tb2);

	printf("---------------------------------------------\n");

	TB tb3 = newTB("A well a everybody\'s heard about the bird\nB-b-b bird, bird, bird, b-bird\'s the word\nA well a bird, bird, bird, the bird is the word\nA well a bird, bird, bird, well the bird is the word\nA well a bird, bird, bird, b-bird\'s the word\n");

	char* text5 = dumpTB(tb3, true);
	printf("Original: \n%s\n", text5);
	free(text5);

	printf("-----delete line 1 to 5-----\n");
	deleteTB(tb3, 1, 5);
	char* text6 = dumpTB(tb3, true);
	printf("After deleted: \n%s\n", text6);
	free(text6);

	releaseTB(tb3);
}

void testPasteTB(){
	printf("-----------------------------------------\n"
	       "              PasteTB tests              \n"
	       "-----------------------------------------\n");

	TB tb1 = newTB("Never gonna give you up\nNever gonna let you down\n");
	TB tb2 = newTB("hello there,\nhow\nare\nthings\n");
	char* text1 = dumpTB(tb1, true);
	char* text3 = dumpTB(tb2, true);
	printf("Original: \nT1: \n%s\nT2: \n%s\n", text1, text3);
	free(text1);
	free(text3);

	printf("-----paste T1 to line 2 of T1-----\n");
	pasteTB(tb1, 2, tb1);
	char* text2 = dumpTB(tb1, true);
	printf("After paste: \n%s\n", text2);
	free(text2);
	//releaseTB(tb1);

	//tb1 = newTB("Never gonna give you up\nNever gonna let you down\n");

	printf("-----paste T2 to line 5 of T1-----\n");
	pasteTB(tb1, 5, tb2);
	char* text4 = dumpTB(tb1, true);
	printf("After paste: \n%s\n", text4);
	free(text4);

	releaseTB(tb1);
	releaseTB(tb2);

	printf("---------------------------------------------\n");

	TB tb3 = newTB("The draft submission link for the MATH1081 assignment is now available in the Assignment section of the Moodle page for\nMATH1081.  Please ensure that you carefully review the assignment instructions before submitting your draft. \nThe deadline is 5pm on Friday of week 6.\nFollowing the draft submission you will have one week to complete a review of the work of one peer.  You must submit a\nreasonable attempt to the draft submission in order to obtain marks for your peer reviewing quality.\nNote that by the end of today's lecture the material for Q3 will have been covered.  The first tutorial next week may also\ncover some relevant material.  So while it's a good idea to start on your draft immediately, if you haven't already done so,\nyou should probably review your draft next week before submitting it.\n");
	TB tb4 = newTB("hello there,\nhow\nare\nthings\n");
	char* text5 = dumpTB(tb3, true);
	char* text6 = dumpTB(tb4, true);
	printf("Original: \nT3: \n%s\nT4: \n%s\n", text5, text6);
	free(text5);
	free(text6);

	printf("-----paste T4 to line 1 of T3-----\n");
	pasteTB(tb3, 1, tb4);
	char* text7 = dumpTB(tb3, true);
	printf("After paste: \n%s\n", text7);
	free(text7);
	//releaseTB(tb1);

	//tb1 = newTB("Never gonna give you up\nNever gonna let you down\n");

	printf("-----paste T3 to line 4 of T4-----\n");
	pasteTB(tb4, 4, tb3);
	char* text8 = dumpTB(tb4, true);
	printf("After paste: \n%s\n", text8);
	free(text8);

	releaseTB(tb4);
	releaseTB(tb3);
}

void testFormRichText(){
	printf("-----------------------------------------\n"
	       "            formRichText tests           \n"
	       "-----------------------------------------\n");

	TB tb = newTB("#string_stuff_\n#\n###\n*some string*\n*some string*lol*\n*some_string*again_\n*some* _string_\nsome *string_again_\nsome#string*once_again*\n#string_stuff_\nHello ** World\nhello **world*\nhello **world**\n***_hello__World_**\n_*HelloWorld*_*\n_*_**\n**hello***world**\n***hello*\n*_*_*__***_*_*\n"); 
	char* text1 = dumpTB(tb, true);
	printf("Original: \n%s\n", text1);
	free(text1);
	formRichText(tb);
	char* text2 = dumpTB(tb, true);
	printf("After: \n%s\n", text2);
	free(text2);
	releaseTB(tb);
}

void testDiffTB(){
	printf("-----------------------------------------\n"
	       "               DiffTB tests              \n"
	       "-----------------------------------------\n");

	TB tb1 = newTB("Never gonna give you up\nNever gonna let you down\n");
	TB tb2 = newTB("hello there,\nhow\nare\nthings\n");

	char* text1 = dumpTB(tb1, true);
	char* text2 = dumpTB(tb2, true);
	printf("T1: \n%s\nT2: \n%s\n", text1, text2);
	free(text1);
	free(text2);

	char* diff = diffTB(tb1, tb2);
	printf("diff: \n%s\n", diff);
	free(diff);

	releaseTB(tb1);
	releaseTB(tb2);
}