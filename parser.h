#ifndef PARSER_H_
#define PARSER_H_

#include "scanner.h"

// A single node of the abstract syntax tree
typedef struct node {
  token_t tok;
  struct node *left, *right;
} ast_node_t;

// The abstract syntax tree
typedef struct {
  ast_node_t *root;
} ast_t;

ast_t *parse_equ(char *equ);

#endif
