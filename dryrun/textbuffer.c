#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "textbuffer.h"

struct textbuffer{
  int n_line;
  char** line;
};
/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.
 */
TB newTB (char text[]) {
  TB tb = malloc(sizeof(*tb));
  tb->line = NULL;
  int idx = 0;
  int size = 0;
  
  for(int i = 0; i < strlen(text); i++){
    if(text[i] == '\n'){
      tb->line = realloc(tb->line, sizeof(*tb->line) * (++size));
      char* new_str = malloc(sizeof(char) * (i - idx + 1));
      tb->line[size - 1] = new_str;
      memcpy(new_str, &text[idx], i - idx);
      new_str[i - idx] = '\0';
      //new_str = strsep(&new_str, "\n");
      idx = i + 1;
    }
  }
  tb->n_line = size;
  
  return tb;
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
  for(int i = tb->n_line; i > 0; i--)
    free(tb->line[i - 1]);
  free(tb->line);
  free(tb);
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number iff showLineNumbers == TRUE
 */
char *dumpTB (TB tb, bool showLineNumbers){
  if(tb == NULL || tb->line == NULL){
    char* empty_str = malloc(sizeof(*empty_str));
    memset(empty_str, '\0', 1);
    return empty_str;
  }

  int size = 0;
  for(int i = 0; i < linesTB(tb); i++){
    if(showLineNumbers)
      size += (strlen(tb->line[i]) + 4 + i/10 + 1); //log10(i + 1)
    else
      size += strlen(tb->line[i]) + 1;
  }
  
  char* str = malloc(sizeof(*str) * (size + 1));
  str[0] = '\0';
  if(linesTB(tb) == 0)
    return str;

  int n_ch = 0;
  for(int i = 0, n = linesTB(tb), l = 0; l < n; i++){
    
    if(tb->line[l][i] == '\0'){
      //size += strlen(tb->line[l]);
      //str = realloc(str, sizeof(*str) * n_ch);
      
      if(showLineNumbers){
	      sprintf(str + strlen(str), "%d. ", l + 1);
        //str = realloc(str, sizeof(*str) * n_ch);
      }
      
      strcat(str, tb->line[l]);
      strcat(str, "\n");
      //str[n_ch + i] = '\n';
      l++;
      i = 0;
      //printf("size: %d\n", n_ch);
    }
    n_ch++;
  }

  return str;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
  return tb->n_line;
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
  assert(pos1 > 0 && pos2 > 0);
  assert(pos1 <= pos2);
  assert(pos1 <= linesTB(tb) && pos2 <= linesTB(tb));
  assert(prefix != NULL);

  if(pos2 > tb->n_line)
    pos2 = tb->n_line;

  for(int i = pos1 - 1, len = strlen(prefix); i < pos2; i++){
    int size = strlen(tb->line[i]) + len;
    tb->line[i] = realloc(tb->line[i], sizeof(char*) * size);

    char tmp[size - len + 1];
    memcpy(tmp, tb->line[i], strlen(tb->line[i]) + 1);
    //printf("%s\n", tmp);
    memcpy(tb->line[i], prefix, len + 1);
    //printf("%s\n", tb->line[i]);
    //memmove(tb->line[i], prefix, len);
    strcat(tb->line[i], tmp);
  }

  //printf("ok\n");
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
  assert(pos > 0);
  if(pos > tb1->n_line + 1)
    abort();
  if(tb1 == tb2)
    return;

  int size = tb1->n_line + tb2->n_line;
  tb1->line = realloc(tb1->line, sizeof(*tb1->line) * size);

  for(int i = size - 1, j = 1, n = pos - 1 + tb2->n_line, k = tb1->n_line, z = tb2->n_line - 1
      ; i >= pos - 1; i--, j++){
    
    if(k - j >= pos - 1){
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb1->line[k - j]) + 1));
      strcpy(tmp, tb1->line[k - j]);
      free(tb1->line[k - j]);
      tb1->line[i] = tmp;
    }
    if(i < n && z >= 0){
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb2->line[z]) + 1));
      strcpy(tmp, tb2->line[z]);
      tb1->line[i] = tmp;
      z--;
    }
  }
  tb1->n_line = size;
  releaseTB(tb2);
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
  assert(pos > 0);
  if(pos > tb1->n_line + 1)
    abort();

  int size = tb1->n_line + tb2->n_line;
  tb1->line = realloc(tb1->line, sizeof(*tb1->line) * size);
  for(int i = size - 1, j = 1, n = pos - 1 + tb2->n_line, k = tb1->n_line, z = tb2->n_line - 1
      ; i >= pos - 1; i--, j++){
    
    if(k - j >= pos - 1){
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb1->line[k - j]) + 1));
      memcpy(tmp, tb1->line[k - j],  strlen(tb1->line[k - j]) + 1);
      free(tb1->line[k - j]);
      tb1->line[k - j] = tmp;
      tb1->line[i] = tmp;
    }
    if(i < n && z >= 0){
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb2->line[z]) + 1));
      memcpy(tmp, tb2->line[z], strlen(tb2->line[z]) + 1);
      tb1->line[i] = tmp;
      z--;
    }
    //printf("---%d %d---\n", i, z);
  }

  tb1->n_line = size;
  //printf("----> %d\n", tb1->n_line);
}

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
TB cutTB (TB tb, int from, int to){
  assert(from > 0 && to > 0);
  assert(from <= tb->n_line && to <= tb->n_line);
  //assert(to >= from);

  if(to < from)
    return NULL;

  TB cut = malloc(sizeof(*cut));
  cut->line = malloc(sizeof(*cut->line) * (to - from + 1));
  cut->n_line = to - from + 1;

	if(tb == NULL)
    return tb;

  for(int i = from, j = 0, k = 0, n = linesTB(tb); i - 1 < n; i++, j++, k++){
    if(i - 1 < to){
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb->line[i - 1]) + 1));
      memcpy(tmp, tb->line[i - 1], strlen(tb->line[i - 1]) + 1);
      cut->line[k] = tmp;
    }

    if(to + j < n){
      free(tb->line[i - 1]);
      char* tmp = malloc(sizeof(*tmp) * (strlen(tb->line[to + j]) + 1));
      memcpy(tmp, tb->line[to + j], strlen(tb->line[to + j]) + 1);
      tb->line[i - 1] = tmp;
    }else if(i - 1 >= n - (cut->n_line)){
      free(tb->line[i - 1]);
    }
  }

  tb->n_line -= cut->n_line;
  return cut;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match new_matchNode(){
  Match m = malloc(sizeof(*m));
  m->columnNumber = -1;
  m->lineNumber = -1;
  m->next = NULL;

  return m;
}

Match searchTB (TB tb, char* search){
  if(search == NULL)
    abort();

  if(strcmp(search, "") == 0){
    //Match emp_m = malloc(sizeof(*emp_m));
    return NULL;
  }

  char* str = dumpTB(tb, false);
  char* str_copy = str;
  Match head = NULL;
  Match ptr = NULL;
  int line = 1;
  char* next_ln = strchr(str_copy, '\n');
  next_ln = &next_ln[1];
  char* tmp = str_copy;
  char* first_ocur = strstr(tmp, search);
  //printf("F>>>>>>>>>%s\n", first_ocur);
  for(int i = 0, n = strlen(str_copy); i < n; i++){
    if(first_ocur != NULL){
      
      while(1){
        if(next_ln - first_ocur <= 0){
          str_copy = next_ln;
          next_ln = strchr(str_copy, '\n');
          next_ln = &next_ln[1];
          line++;
        }else{
          break;
        }
      }
      //printf("%d>>>>>>>>>%s\n", i, str);
      Match curr = new_matchNode();
      curr->columnNumber = first_ocur - str_copy + 1;
      curr->lineNumber = line;
      curr->next = NULL;
      tmp = &first_ocur[strlen(search)];
      //printf("T>>>>>>>>>%s\n", tmp);
      if(head == NULL){
        head = ptr = curr;
      }else{
        ptr->next = curr;
        ptr = curr;
      }
 
      //printf("F>>>>>>>>>%s\n", str);
      first_ocur = strstr(tmp, search);
    }
  }
  free(str);
  return head;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
  assert(from >= 0 && to >= 0);
  assert(from <= linesTB(tb) && to <= linesTB(tb));
  
  if(to < from)
    abort();

	if(tb == NULL)
    return;

  for(int i = from - 1, n = tb->n_line, diff = to - from, j = 0; i < n; i++, j++){
    if(i + diff + 1 < n){
      if(strlen(tb->line[i]) < strlen(tb->line[i + diff + 1]))
        tb->line[i] = realloc(tb->line[i], sizeof(*tb->line[i]) * (strlen(tb->line[i + diff + 1]) + 1));
      memcpy(tb->line[i], tb->line[i + diff + 1], strlen(tb->line[i + diff + 1]) + 1);
      /**char* tmp = malloc(sizeof(*tmp) * strlen(tb->line[i + diff + 1]));
      memmove(tmp, tb1->line[k - j],  strlen(tb1->line[i + diff + 1]) + 1);
      tb->line[i] = tmp;*/
    }
  }

  for(int i = 0, n = tb->n_line - 1, diff = to - from + 1; i < diff; i++){
    free(tb->line[n--]);
    tb->n_line--;
  }
}


/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
void formRichText (TB tb){
  char star_replacement_head[] = "<b>";
  char star_replacement_tail[] = "</b>";
  char underscore_replacement_head[] = "<i>";
  char underscore_replacement_tail[] = "</i>";
  char hash_replacement_head[] = "<h1>";
  char hash_replacement_tail[] = "</h1>";

  for(int i = 0, n_line = linesTB(tb); i < n_line; i++){
    //char* line = tb->line[i];
    char line_copy[strlen(tb->line[i]) + 1];
    int size = strlen(tb->line[i]);

    strcpy(line_copy, tb->line[i]);

    if(tb->line[i][0] == '#'){
      if(size != 1){
        char tmp[size];
        memcpy(tmp, &tb->line[i][1], strlen(tb->line[i]));
        tb->line[i] = realloc(tb->line[i], sizeof(*tb->line[i]) * (strlen(tb->line[i]) + 10));
        size += 10;
        memcpy(tb->line[i], hash_replacement_head, strlen(hash_replacement_head) + 1);
        strcat(tb->line[i], tmp);
        strcat(tb->line[i], hash_replacement_tail);
      }
      //tb->line[i] = line;
      //printf("%d--->> %s\n", i, tb->line[i]);
      continue;
    }

    
    char* first_star = strchr(line_copy, '*');
    char* first_underscore = strchr(line_copy, '_');
    char* second_star = NULL;
    char* second_underscore = NULL;
    char* newLine = malloc(sizeof(*newLine) * (size * 4));
    size *= 4;
    memset(newLine, '\0', size);

    for(; first_star != NULL || first_underscore != NULL;){
      //case that there are only * in the line OR * comes before _
      if((first_underscore == NULL || first_star < first_underscore) && first_star != NULL){
        //newLine = realloc(newLine, sizeof(*newLine) * (size + 15));
        //size += 15;
        second_star = strchr(&first_star[1], '*');

        if(&first_star[1] == second_star){
          first_star = second_star;
          continue;
        }

        if(second_star != NULL){
          //char tmp[size];
          char before[size];
          char between[size];

          memset(before, '\0', size);
          memcpy(between, &first_star[1], second_star - first_star - 1);
          between[second_star - first_star - 1] = '\0';

          if(first_star != &line_copy[0]){
            memcpy(before, line_copy, first_star - line_copy);
          }

          if(newLine[0] == '\0')
            strcpy(newLine, before);
          else
            strcat(newLine, before);
          strcat(newLine, star_replacement_head);
          strcat(newLine, between);
          strcat(newLine, star_replacement_tail);
          //strcpy(tmp, &second_star[1]);
          //strcpy(line_copy, &second_star[1]);
          //strcpy(line_copy, tmp);
          memmove(line_copy, &second_star[1], strlen(&second_star[1]) + 1);

          first_star = strchr(line_copy, '*');
          first_underscore = strchr(line_copy, '_');
        }

        
        //printf("f* -> %s\n", first_star);
        //printf("copy : %s\n", line_copy);

        //if(first_star == NULL || second_star == NULL)
          //strcat(newLine, line_copy);
        
        if(second_star == NULL)
          first_star = NULL;
          
      }else if((first_star == NULL || first_underscore < first_star) && first_underscore != NULL){
        //newLine = realloc(newLine, sizeof(*newLine) * (size + 15));
        //size += 15;
        second_underscore = strchr(&first_underscore[1], '_');

        if(&first_underscore[1] == second_underscore){
          first_underscore = second_underscore;
          continue;
        }

        if(second_underscore != NULL){
          char before[size];
          char between[size];

          memset(before, '\0', size);
          memcpy(between, &first_underscore[1], second_underscore - first_underscore - 1);
          between[second_underscore - first_underscore - 1] = '\0';

          if(first_underscore != &line_copy[0]){
            memcpy(before, line_copy, first_underscore - line_copy);
          }
          //printf("before: %s\n", before);
          if(newLine[0] == '\0')
            strcpy(newLine, before);
          else
            strcat(newLine, before);
          strcat(newLine, underscore_replacement_head);
          strcat(newLine, between);
          strcat(newLine, underscore_replacement_tail);
          //strcpy(line_copy, &second_underscore[1]);
          memmove(line_copy, &second_underscore[1], strlen(&second_underscore[1]) + 1);

          first_underscore = strchr(line_copy, '_');
          first_star = strchr(line_copy, '*');
        }

        
        //printf("f_ -> %s\n", first_underscore);
        //printf("copy : %s\n", line_copy);

        //if(first_underscore == NULL || second_underscore == NULL)
          //strcat(newLine, line_copy);
        
        if(second_underscore == NULL)
          first_underscore = NULL;
      }
    }

    if(first_star == NULL || first_underscore == NULL)
      strcat(newLine, line_copy);

    free(tb->line[i]);
    tb->line[i] = newLine;
    //printf("%d ---> %s\n", i, newLine);
    
  }
}

char *diffTB (TB tb1, TB tb2){
  char *diff = malloc(sizeof(*diff));
  memset(diff, '\0', 1);
  int max_nline = (tb1->n_line > tb2->n_line) ? tb1->n_line : tb2->n_line;
  int size = 0;

  for(int i = 0; i < max_nline; i++){
    if(i >= tb1->n_line || (i < tb1->n_line && strcmp(tb1->line[i], tb2->line[i]) != 0)){
      diff = realloc(diff, sizeof(*diff) * (size + strlen(tb2->line[i]) + 10));
      size += strlen(tb2->line[i]) + 10;
      char line_num_tmp[i/10 + 2];
      sprintf(line_num_tmp, "%d", i + 1);

      if(i < tb1->n_line){
        if(diff[0] == '\0')
          strcpy(diff, "-,");
        else
          strcat(diff, "-,");
        strcat(diff, line_num_tmp);
        strcat(diff, "\n");
      }
      strcat(diff, "+,");
      strcat(diff, line_num_tmp);
      strcat(diff, ",");
      strcat(diff, tb2->line[i]);
      strcat(diff, "\n");
    }
  }
  
  return diff;
}

void undoTB (TB tb){
  return;
}

void redoTB (TB tb){
  return;
}

 