#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

//helper function

long int go_to_next_key(FILE * fptr, const char* key) {
  // Returns the end position of the next key in the file (using ftell)
  // Returns -1 if the key is not found
  
  char c;
  int i = 0;
  // Start from some position
  while(1) {
    c = fgetc(fptr);
    if (c == EOF) {
      return -1;
    }
    
    if (key[i] == c) {
      i++;
    }
    
    if (i == strlen(key)) {
      return ftell(fptr);
    }    
    
  }
  
}

char* get_next_term(FILE * fptr, 
                    const char* term_key,
                    const char* def_key) {
  // Gets the next term starting from the position pos
  //   Returns the term if it exists; otherwise, returns NULL
  //   Assumes file is valid
  
  // Find term beginning position
  long int tkend = go_to_next_key(fptr, term_key);
  
  if (tkend == -1) {
    return NULL;
  }
  
  // Find term ending position
  long int dkend = go_to_next_key(fptr, def_key);
  long int dkstart = dkend - (strlen(def_key)-1);
  
  // Go from beginning pos to end pos and return next term
  char* ret = (char*) malloc( ( (dkstart-1) - tkend + 2)*sizeof(char) );
  ret[0] = '\0';
  
  //printf("tkend = %ld, dkstart = %ld\n", tkend, dkstart);
  fseek(fptr, tkend, SEEK_SET);
  char c;
  for (int i = tkend; i < dkstart-1; i++) {
    c = fgetc(fptr);
    //printf("%c\n", c);
    strncat(ret, &c, 1);
  }
  //fgets(ret, (dkstart-1)-(tkend+1)+2, fptr);
  return ret;
}



int add_term(const char* file_name, const char* word, const char* definition) { 

  // See assignment
  char term_key[100] = "\n&%JF#)*NBG@$^_term\n";
  char def_key[100] = "\ndefinition&%JF#)*NBG@$&^__start\n";  
  
  FILE * fptr;
  fptr = fopen(file_name, "a+");
  
  // OPTIONAL TO DO: Check file validity; if not, then return -2
  
  // REPEAT:
  //   Find next term in file
  //     If term in file matches given term, return 0
  //   If eof, then a term has not been found
  //     In this case, add term and definition, return 1

  while(1) {
    char* next_term = get_next_term(fptr, term_key, def_key);
    
    if (next_term == NULL) {
      // write term and definition to file
      fputs(term_key, fptr); 
      fputs(word, fptr);
      fputs(def_key, fptr);
      fputs(definition, fptr);
      fclose(fptr);
      free(next_term);
      return 1;      
    }
    
    if (strcmp(next_term, word) == 0) { // strcmp returns 0 if strings are equal
      fclose(fptr);
      free(next_term);
      return 0;
    }
    
    free(next_term);
  }
}

//helper funtion
char* get_next_definition(FILE * fptr, 
                    const char* term_key,
                    const char* def_key) {
  // Gets the next definition starting from the position pos
  //   Returns the term if it exists; otherwise, returns NULL
  //   Assumes file is valid
  
  // Find term beginning position
  long int dkend = go_to_next_key(fptr, def_key);
  
  if (dkend == -1) {
    return NULL;
  }
  
  // Find definition ending position
  long int tkstart;
  long int tkend = go_to_next_key(fptr, term_key);
    if (tkend == -1){
      fseek(fptr, 0, SEEK_END);
      tkstart = ftell(fptr) + 1;
    } else {
      tkstart = tkend - (strlen(term_key)-1);
    }
  //long int tkstart = tkend - (strlen(term_key)-1);
  
  // Go from beginning pos to end pos and return next term
  char* cat = (char*) malloc( ( (tkstart-1) - dkend + 2)*sizeof(char) );
  cat[0] = '\0';

  fseek(fptr, dkend, SEEK_SET);
  char c;
  
  for (int i = dkend; i < tkstart-1; i++) {
    c = fgetc(fptr);
    strncat(cat, &c, 1);
  }

  return cat;
}


char* find_term(const char* file_name, const char* word) {
  // See assignment
  char term_key[100] = "\n&%JF#)*NBG@$^_term\n";
  char def_key[100] = "\ndefinition&%JF#)*NBG@$&^__start\n";  
  
  FILE * fptr;
  fptr = fopen(file_name, "a+");
  
  while(1) {
    char* next_term = get_next_term(fptr, term_key, def_key);
    
    if (next_term == NULL) {
      // the term is not in the file, returns NULL
      fclose(fptr);
      free(next_term);
      return NULL;      
    }
    
    if (strcmp(next_term, word) == 0) { // strcmp returns 0 if strings are equal
      char* next_definition = get_next_definition(fptr, term_key, def_key);
      fclose(fptr);
      return next_definition;
    }
  }  
}  

uint64_t fib3(unsigned int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  if (n == 2) return 2;
  
  uint64_t fib_nm1 = 2; // n minus 1
  uint64_t fib_nm2 = 1; // n minus 2
  uint64_t fib_nm3 = 0; // n minus 3
  uint64_t temp;
 
  // populate the array one element at a time from 3 to n
  for (int i = 3; i<=n; i++){
    temp = fib_nm1 + 2*fib_nm2 + 3*fib_nm3;
    fib_nm3 = fib_nm2;
    fib_nm2 = fib_nm1;
    fib_nm1 = temp;
  }
  return temp;
}



int count_tokens(const char* str) {
  int count = 0;
  
  if(!str){
    return count; 
  }    
  
  int s = strlen(str);
  int i = 0;
  
  while(str[i] == ' '){
    i++;
  }

  //if empty tokens or all spaces tokens, it will return 0
  if(str[i] == '\0'){
    return count; 
  }
  
  int start = i;
  
	int nvr_seen_not_lower = 1; // 1 = true: lower letters continuous; 0=false: char other than lower letters appears.
	int space_ahead = 0; // 1 = true: the lastest char is space; 0=false: otherwise. 

	for(i=start; i<=s; i++){
   //if there is a space or the end of the string, we should count 1 only if the[i-1] char is not a space and lower letters continuous.
    if(str[i] == ' '|| str[i] == '\0'){
      if (nvr_seen_not_lower == 1 && space_ahead == 0){
        count++;
      }
      nvr_seen_not_lower = 1;
      space_ahead = 1;
    }
    
    if(str[i]>= 'a' && str[i] <= 'z'){
      space_ahead = 0;
    }
    //whenever there is not lower letter appear, nvr_seen_not_lower will be set to false and it will not change untill there is a space to reset.
    if ((str[i] < 'a'|| str[i] > 'z') && (str[i] != ' ')){
      nvr_seen_not_lower = 0;
      space_ahead = 0;
 	  }
  }
	return count;	
}  



char** get_tokens(const char* str) {
  int count = 0; 
  int s = strlen(str);
  int i =0;
  int nvr_seen_not_lower = 1; // 1=true: lower letters continuous; 0 = false: char other than lower letters appears.
  int space_ahead = 0; // 1 = true: the lastest char is space; 0 = false: otherwise. 
    
  // malloc of (3*#tokens + strlen(str))
  int beginning_index [s];//start index of the tokens with lower letters
  int ending_index [s];//ending index of the tokens with lower letters
  for(int r = 0; r<s; r++){
    beginning_index [r] = -1;
    ending_index [r] = -1;
  }
  beginning_index[0] = 0;
    
  if(!str){
    count = 0;
    return NULL;
  }  

  while(str[i] == ' '){
    i++;
  }
  
  int start = i;
  beginning_index[0] = start;
  
  if(str[i] == '\0'){
    count = 0;
    return NULL;   
  } else {  
    for(i=start; i<=s; i++){
      //if there is a space or the end of the string, we should count 1 only if the[i-1] char is not a space and lower letters continuous.
      if(str[i] == ' ' || str[i] == '\0'){
        if (nvr_seen_not_lower == 1 && space_ahead == 0){
          ending_index [count] = i-1; // as ending tokens will be one index before space or \0
          count++;
        }
        nvr_seen_not_lower = 1;
        space_ahead = 1;
        beginning_index [count] = i+1; // start record b[j]+1
      }

      if(str[i]>= 'a' && str[i] <= 'z'){
        space_ahead = 0;
      }
      //whenever there is not lower letter appear, nvr_seen_not_lower will be set to false and it will not change untill there is a space to reset.
      if ((str[i] < 'a'|| str[i] > 'z') && (str[i] != ' ')){
        nvr_seen_not_lower = 0;
        space_ahead = 0;
      }  
    }
    
    if (!count) {
      return NULL;
    }
  }

      
  // --- Memory allocation ---
  int p, q=0;
  char**tokens = (char**) malloc ((count)*sizeof(char*));
  for (int w = 0; w<count; w++){
    //size is e[w]-b[w]+1+3: +1 for 0; +4 for , " " \0
    tokens[w] = (char*)malloc((ending_index [w]-beginning_index[w]+5) 
        * sizeof(char)); // instead of 5 it should be 2

    tokens[w][0] = '\0';
  }
// ---------------------------
  // Note that tokens[h][w] is same as *(*(arr+h)+w)

  while(beginning_index[q] != -1 && ending_index [q] != -1){
    // at the beginning of each tokens, add ". 
    //strcat(tokens[q], "\"");
   
    for(p =(beginning_index[q]); p<=(ending_index [q]); p++) {
    // append the first token based on b[0] and e[0] which tells the index for beginning and ending in string.
    //here p should be <= ending_index [q]-1 as it is index not length
      strncat(tokens[q], str+p , 1);
    }
    //strcat(tokens[q], "\"");
    //if (ending_index [q+1] != -1){
    //  strcat(tokens[q], ",");
    q++;
  }
  return tokens;
}