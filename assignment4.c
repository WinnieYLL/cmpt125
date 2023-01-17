#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "assignment4.h"

/* Question 1 */

int queue_move(queue_t* destination, queue_t* source) {
  int count=0, temp;
  if (queue_is_empty(source) == 1) return count;
  while (queue_is_empty(source) != 1){
    temp = dequeue(source);
    count++;
    enqueue(destination, temp);
  }
  return count;
}

int queue_size(queue_t* q) {
  int temp, count=0;
  queue_t* copy = queue_create();
  while (queue_is_empty(q) != 1){
     temp = dequeue(q);
     enqueue(copy, temp);
     count++;
  }
  return count;
}

bool queue_equal(queue_t* q1, queue_t* q2) {
  // create two queues that will be the same as q1 and q2 in the end
  queue_t* q1a = queue_create();
  queue_t* q2a = queue_create();
  
  int dq1, dq2;
  bool ret = true;
  
  // dequeue elements of q1 and q2 into q1a and q2a
  while (queue_is_empty(q1)==0 && queue_is_empty(q2)==0) {
    dq1 = dequeue(q1);
    dq2 = dequeue(q2);
    
    if (dq1 != dq2) ret = false;
    
    enqueue(q1a, dq1);
    enqueue(q2a, dq2);
  }
  
  // now one of the queues is empty
  if (queue_is_empty(q1)) {
    while (!queue_is_empty(q2)) {
      ret = false;
      enqueue(q2a, dequeue(q2));
    }
  }
  
  if (queue_is_empty(q2)) {
    while (!queue_is_empty(q1)) {
      ret = false;
      enqueue(q1a, dequeue(q1));
    }
  }
  
  // now enqueue everything back
  while (!queue_is_empty(q1a)) {
    enqueue(q1, dequeue(q1a));
  }

  while (!queue_is_empty(q2a)) {
    enqueue(q2, dequeue(q2a));
  }
  
  queue_free(q1a);
  queue_free(q2a);
  
  return ret;
}

/* Question 2 */

float eval_arithmetic_expression(BTnode_t* root) {
  if (root->left == NULL && root->right == NULL) return root->value;

  if(root->value == PLUS){
    return eval_arithmetic_expression(root->left) + eval_arithmetic_expression(root->right);
  }
  if(root->value == MINUS){
    return eval_arithmetic_expression(root->left) - eval_arithmetic_expression(root->right);
  }
  if(root->value == MULT){
    return eval_arithmetic_expression(root->left)*eval_arithmetic_expression(root->right);
  }
  if(root->value == DIV){
    return eval_arithmetic_expression(root->left)/eval_arithmetic_expression(root->right);
  }
  return 0;
}


/* Question 3 */

BTnode_t* find(BTnode_t* root, bool (*pred)(int)) {
  if (root == NULL) return NULL;
  if ((*pred)(root->value) == true) return root;
  
  BTnode_t* ret = find(root->left,(*pred));
  if (ret != NULL) return ret;
  
  return find(root->right,(*pred));
}


BTnode_t* create_mirror_tree(BTnode_t* root) {
  if (root==NULL)
    return NULL;
  BTnode_t* ret_root = create_node(root->value);
  set_left_child(ret_root, create_mirror_tree(root->right));
  set_right_child(ret_root, create_mirror_tree(root->left));
  return ret_root;  
}
