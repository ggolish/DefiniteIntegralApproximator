#ifndef STQU_H_
#define STQU_H_

#include <stdbool.h>

typedef struct llnode {
  void *value;
  struct llnode *next;
} llnode_t;

typedef struct {
  llnode_t *head;
  llnode_t *tail;
  int size;
} queue_t;

typedef struct {
  llnode_t *head;
  int size;
} stack_t;

queue_t *new_queue();
void push_queue(queue_t *q, void *v);
void *pop_queue(queue_t *q);
bool isempty_queue(queue_t *q);

stack_t *new_stack();
void push_stack(stack_t *q, void *v);
void *pop_stack(stack_t *q);
bool isempty_stack(stack_t *q);

#endif
