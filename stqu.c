#include "stqu.h"

#include <stdio.h>
#include <stdlib.h>

static llnode_t *new_llnode(void *v);

queue_t *new_queue()
{
  queue_t *q = NULL;

  if((q = (queue_t *)malloc(sizeof(queue_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  q->head = q->tail = NULL;
  q->size = 0;
  return q;
}

void push_queue(queue_t *q, void *v)
{
  llnode_t *tmp = new_llnode(v);
  q->size++;
  if(isempty_queue(q)) {
    q->head = q->tail = tmp;
  } else {
    q->tail->next = tmp;
    q->tail = tmp;
  }
}

void *pop_queue(queue_t *q)
{
  if(isempty_queue(q)) return NULL;
  void *v = q->head->value;
  llnode_t *tmp = q->head;
  if(q->head == q->tail) {
    q->head = q->tail = NULL;
  } else {
    q->head = q->head->next;
  }
  free(tmp);
  q->size--;
  return v;
}

bool isempty_queue(queue_t *q)
{
  return (q->size == 0);
}

stack_t *new_stack()
{
  stack_t *s = NULL;

  if((s = (stack_t *)malloc(sizeof(stack_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  s->head = NULL;
  s->size = 0;
  return s;
}

void push_stack(stack_t *s, void *v)
{
  llnode_t *tmp = new_llnode(v);
  s->size++;
  if(isempty_stack(s)) {
    s->head = tmp;
  } else {
    tmp->next = s->head;
    s->head = tmp;
  }
}

void *pop_stack(stack_t *s)
{
  if(isempty_stack(s)) return NULL;
  void *v = s->head->value;
  llnode_t *tmp = s->head;
  s->head = s->head->next;
  free(tmp);
  s->size--;
  return v;
}

bool isempty_stack(stack_t *s)
{
  return (s->size == 0);
}

static llnode_t *new_llnode(void *v)
{
  llnode_t *n = NULL;

  if((n = (llnode_t *)malloc(sizeof(llnode_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  n->value = v;
  n->next = NULL;
  return n;
}
