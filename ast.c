#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static ast_t *new_ast();
static ast_node_t *new_ast_node(token_t *tok);
static long double evaluate_node(ast_node_t *n, long double var_val);
static int process_token(token_t *t, stack_t *node_stack);

ast_t *make_ast(queue_t *outqueue)
{
  ast_t *ast = new_ast();
  stack_t *node_stack = new_stack();

  token_t *t = (token_t *)pop_queue(outqueue);
  while(!isempty_queue(outqueue)) {
    process_token(t, node_stack);
    t = (token_t *)pop_queue(outqueue);
  }
  
  if(process_token(t, node_stack) == -1) {
    fprintf(stderr, "Error: Unbalanced equation!\n");
    return NULL;
  }

  if(node_stack->size != 1) {
    fprintf(stderr, "Unbalanced equation! Node stack left: %d\n", node_stack->size);
    return NULL;
  }
  
  ast->root = (ast_node_t *)pop_stack(node_stack);
  return ast;
}

long double evaluate_ast(ast_t *ast, long double var_val)
{
  if(!ast->root) return NAN;
  return evaluate_node(ast->root, var_val);
}

static long double evaluate_node(ast_node_t *n, long double var_val)
{
  if(!n) return NAN;
  if(n->left == NULL && n->right == NULL) {
    if(n->tok->type == TOK_VAR) {
      n->value = var_val;
    } else if(n->tok->type == TOK_NUM) {
      if(isnan(n->value)) {
        n->value = strtold(n->tok->rep, NULL); 
      }
    }
    return n->value;
  }

  long double lv = evaluate_node(n->left, var_val);
  long double rv = evaluate_node(n->right, var_val);

  switch(n->tok->type) {
    case TOK_PLUS:
      n->value = lv + rv;
      break;
    case TOK_MINUS:
      n->value = lv - rv;
      break;
    case TOK_MULT:
      n->value = lv * rv;
      break;
    case TOK_DIV:
      n->value = lv / rv;
      break;
    case TOK_EXP:
      n->value = powl(lv, rv);
      break;
    case TOK_SIN:
      n->value = sinl(rv);
      break;
    case TOK_COS:
      n->value = cosl(rv);
      break;
    case TOK_TAN:
      n->value = tanl(rv);
      break;
    case TOK_SQRT:
      n->value = sqrtl(rv);
      break;
    case TOK_LN:
      n->value = logl(rv);
      break;
    default:
      fprintf(stderr, "Invalid token is ast!\n");
      break;
  }

  return n->value;
}

static int process_token(token_t *t, stack_t *node_stack)
{
  ast_node_t *n = new_ast_node(t);
  if(t->prec == OPPREC_0) {
    push_stack(node_stack, (void *)n);
  } else if(t->prec < OPPREC_4) {
    if(node_stack->size < 2) return -1;
    n->right = (ast_node_t *)pop_stack(node_stack);
    n->left = (ast_node_t *)pop_stack(node_stack);
    push_stack(node_stack, (void *)n);
  } else {
    if(node_stack->size < 1) return -1;
    n->right = (ast_node_t *)pop_stack(node_stack);
    push_stack(node_stack, (void *)n);
  }
  return 1;
}

static ast_t *new_ast()
{
  ast_t *ast = NULL;

  if((ast = (ast_t *)malloc(sizeof(ast_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  ast->root = NULL;
  return ast;
}

static ast_node_t *new_ast_node(token_t *tok)
{
  ast_node_t *n = NULL;

  if((n = (ast_node_t *)malloc(sizeof(ast_node_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  n->tok = tok;
  n->value = NAN;
  n->left = n->right = NULL;
  return n;
}

