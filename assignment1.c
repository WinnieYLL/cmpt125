#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment1.h"

int sum_interval(int x, int y) {
    int sum = 0;
    int small = 0;
    int large = 0;
    if (x <= y){
      small = x; // Declare small and large to store the smallest integer and largest integer
      large = y;
    }
    else{
      small = y;
      large = x;
    }
    if ((large-small)%2 == 0){ // If total count of integers is odd, sum = (num of integer - 1)*(smallest num + (largest num-1))/2 + largest num
      sum = (large+small-1)*((large-small)/2)+large;
    }  
    else { // If total count of integer is even, sum = num of integer*(smallest num + largest num)/2
      sum = (large+small)*((large-small)+1)/2;
    }
  return sum;
}



int hide_letters(char* str)  {
  char* upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Declare string for upper letters and lower letters
  char* lower = "abcdefghijklmnopqrstuvwxyz";
  int count = 0;
  int i = 0;  
  int j = 0;
  for (i=0; i<=strlen(str); i++){ // Assumes ASCII might not put capital letters between 'A' and 'Z' here but if not we can use: if (letter <= 'A' && letter >= 'Z') to be more efficient 
    for (j=0; j<26; j++){ // be careful about hardcoded 26
      if (str[i] == upper[j]){ // Go through each item in str 
        str[i] = '$'; // Replace it with '$' if one in the string of upper
        count += 1; // Add one each time replacing with '$'
      }
      if (str[i] == lower[j]){ // Go through each item in str
        str[i] = '*'; // Replace it with '*' if one in the string of lower
        count += 1; // Add one each time replacing with '*'
      }
    }
  }
  return count;
}


int count_max(const int* arr, int n) {
  int max = arr[0];// Decale max = arr[0] instead of max = 0 so that works for all negative arr as well
  int i = 0;
  int count = 0;
  for (i=0; i<n; i++){ // Same as i<=(n-1)
    if(arr[i]>max){ // Go through and compare all items to get the largest number as max
      max = arr[i];
    }
  }
  for (i=0; i<n; i++){
    if(arr[i] == max){ // Go through each integer in arr and count each time it equals max
      count += 1;
    }
  }
  return count;
}


char* mult_number_by_digit(const char* num, int digit) {
  int n = strlen(num); 
  int i;
  char* arr = (char*) malloc ((n+2)*sizeof(char));// one additional for \0 and one adddtional for possible one more digit after multiplication. 
  if (arr == NULL){
    printf("memory allocation failed\n");
    return NULL;    
  }
  
  int carry = 0; // it represents carry digit from lower digit 
  
  for (i=(n-1); i>=0; i--){
    // conver char to integer first
    int num1 = num[i] - '0'; // num1 == 57 if not - '0'
    int temp = num1 * digit + carry; // int product of num 1 plus the carry value from [i+1]'s product
    int ones = temp % 10; // it gets the lower digit value
    int total_ones = ones; // total lower digit value with current and the [i+1]'s carry value
    arr[i+1] = (char) (total_ones + '0');// arr[n+1] save for "\0" so the most lower digit will save in the last second place of arr = arr[n] = arr[i+1].
    carry = (temp / 10) % 10; // higer digit value to be carry and add in the i-1 product's ones digit.
    arr[i] = (char) (carry + '0'); // conver integer to char and save
  }

  
  if (!carry){ // there is no carry value for product of num[0]*digit
    for (i=0; i<=(n+1); i++){
	arr[i] = arr[i+1]; // move each value one space forward   
    }
  }
  return arr;
}  


char* mult_digits(const int* digits, int n) {
  int j;
  char* latest_result = (char*) malloc ((n+2)*sizeof(char)); //malloc declared to store the output of products
  if (latest_result == NULL){
    printf("memory allocation failed\n");
    return NULL;    
  }
  
  latest_result[0]= (char) (digits[0] + '0'); //convert integer to char for digits[0] so that can be an input to mult_number_by_digit function
  latest_result[1]= '\0'; // end the string

  for (j=1; j<n; j++){ // call mult_number_by_digit function to do the multiplication calculation for each for the item in digits[].
    char* mult_result = mult_number_by_digit(latest_result,digits[j]);
    strcpy (latest_result, mult_result); // copy the mult_result each time it calculates the multiplication into latest_result before the result being free/erased
    free(mult_result); 
  }
  return latest_result;
}  
