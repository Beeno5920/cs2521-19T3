// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L) {
	DLList peaksL = newDLList();
    DLListNodeP curr_p = peaksL->curr;

    if(L->first == L->last){
        return peaksL;
    }

    for(DLListNodeP curr = L->curr; curr != NULL; curr = curr->next){
        if(curr == L->first && curr->next->value < curr->value){
            if(L->nitems > 2 && curr->next->next->value < curr->next->value){
                continue;
            }

            curr_p = newDLListNode(curr->value);
            peaksL->first = peaksL->curr = curr_p;
            peaksL->nitems++;
            continue;
        }

        if(curr->next != NULL && curr->prev != NULL){
            if(curr->prev->value < curr->value && curr->value > curr->next->value){
                if(!curr_p){
                    curr_p = newDLListNode(curr->value);
                    peaksL->first = peaksL->curr = curr_p;
                }else{
                    curr_p->next = newDLListNode(curr->value);
                    curr_p->next->prev = curr_p;
                    curr_p = curr_p->next;
                }
                peaksL->nitems++;
            }
        }else if(curr->next == NULL && curr->value > curr->prev->value){
            if(L->nitems > 2 && curr->prev->prev->value < curr->prev->value){
                continue;
            }

            if(!curr_p){
                    curr_p = newDLListNode(curr->value);
                    peaksL->first = peaksL->curr = curr_p;
                }else{
                    curr_p->next = newDLListNode(curr->value);
                    curr_p->next->prev = curr_p;
                    curr_p = curr_p->next;
                }
            peaksL->nitems++;
        }
    }

    peaksL->last = curr_p;

	
	return peaksL;
}



