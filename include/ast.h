#ifndef AST_H_
#define AST_H_

#include "scanner.h"
#include "stqu.h"

typedef struct {
  char name;
  long double value;
} var_t;

// A single node of the abstract syntax tree
typedef struct node {
  token_t *tok;
  long double value;
  struct node *left, *right;
} ast_node_t;

// The abstract syntax tree
typedef struct {
  ast_node_t *root;
  char *variables;
  int vlen;
  int vcap;
} ast_t;

ast_t *make_ast(queue_t *outqueue);
long double evaluate_ast(ast_t *ast, var_t *variables);

#endif
