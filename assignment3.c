#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment3.h"

// generic swap
// assumption: the memory segments don't overlap
void swap(void* a, void* b, size_t s)  {
  char* char_a = (char*)a;
  char* char_b = (char*)b;

  for (int i=0;i<s;i++) {
    char tmp = char_a[i];
    char_a[i] = char_b[i];
    char_b[i] = tmp;
  }

/* // ALTERNATIVE, requires extra space
  void* tmp = malloc(s);
  memcpy(tmp, a, s);
  memcpy(a, b, s);
  memcpy(b, tmp, s);
  free(tmp);
*/
} 

//helper function

int absv(int n){
  if (n<0) return -n;
  return n;
}

void print_pts_array(const point2d* ar, int n) {
  for (int i = 0; i < n; i++) {
    if (i < n-1)
      printf("(%d, %d), ", ar[i].x, ar[i].y);
    else
      printf("(%d, %d)", ar[i].x, ar[i].y);
  }
  printf("\n");
}

int compare_points (const void * a, const void * b){
  int ax = ((point2d*)a)->x;
  int ay = ((point2d*)a)->y;
  int bx = ((point2d*)b)->x;
  int by = ((point2d*)b)->y;

  int abs_ax = absv(ax);
  int abs_ay = absv(ay);
  int abs_bx = absv(bx);
  int abs_by = absv(by);
  
  if ( (abs_ax+abs_ay)<(abs_bx+abs_by) ) return -1;
  if ( (abs_ax+abs_ay)>(abs_bx+abs_by) ) return 1;
  
  // if abs_a==abs_b
  if (ax < bx) return -1; 
  if (ax > bx) return 1;
  
  // abs_a == abs_b && ax == bx
  if (ay < by) return -1;
  if (ay > by) return 1;

  // abs_a == abs_b && ax == bx && ay == by
  return 0;
}

void sort_points(point2d* ar, int n) {
  qsort(ar, n, sizeof(point2d), compare_points);
}  

// helper functions

int gen_insertion_sort(void* ar, int n, size_t size, int (*compare)(const void*, const void*)) {
  int count = 0;
  for(int i = 0; i<n; i++){
    // Assume arr[0..i-1] is sor
    // find the position to insertted
    int j = i;
    while ( j>0 && ((*compare)(ar+(j-1)*size, ar+j*size) > 0) ) {
      swap(ar+(j-1)*size, ar+j*size, size);
      count++;
      j--;
    }
  }
  return count;
}


int find(int* A, int start, int end, bool (*pred)(int)) {
  int i = 0;
  for(i=start; i<=end; i++){
    if( (*pred)(A[i]) == true ){
      return i;
    }
  }
  return -1;
}  


int count(int* A, int start, int end, bool (*pred)(int)) {
  int i = 0;
  int count = 0;
  for(i=start; i<=end; i++){
    if( (*pred)(A[i]) == true ){
      count++;
    }
  }
  return count;
}  


void map(int* A, int start, int end, int (*f)(int)) {
  int i = 0;
  for(i=start; i<=end; i++){
    A[i] = (*f)(A[i]);
  } 
  return;
}  


int reduce(int* A, int start, int end, int (*f)(int,int)) {
  int acc = A[start];
  if (start == end){
    return acc;
  } 
  
  for (int i = start+1; i<=end; i++){
    acc = (*f)(acc, A[i]);
    //printf("%d\n", acc);
  }
  return acc;
}  
