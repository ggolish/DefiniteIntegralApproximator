#include "parser.h"
#include "stqu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void process_operator(token_t *tok, stack_t *opstack, queue_t *outqueue);
static void process_rparen(stack_t *opstack, queue_t *outqueue);

// Parses an equation and returns the appropriate abstract syntax tree
ast_t *parse_equ(char *equ)
{
  init_scanner(equ);
  stack_t *opstack = new_stack();
  queue_t *outqueue = new_queue();

  token_t *tok = next_token();
  while(tok->type != TOK_EOF) {
    switch(tok->type) {
      case TOK_VAR:
        if(strlen(tok->rep) != 1) {
          fprintf(stderr, "Error: Variable name '%s' longer than one character!\n", tok->rep);
          exit(1);
        }
      case TOK_NUM:
        push_queue(outqueue, (void *)tok);
        break;
      case TOK_PLUS:
      case TOK_MINUS:
      case TOK_MULT:
      case TOK_DIV:
      case TOK_EXP:
        process_operator(tok, opstack, outqueue);
        break;
      case TOK_LPAREN:
        push_stack(opstack, (void *)tok);
        break;
      case TOK_RPAREN:
        process_rparen(opstack, outqueue);
        break;
      case TOK_SIN:
      case TOK_COS:
      case TOK_TAN:
      case TOK_SQRT:
      case TOK_LN:
        push_stack(opstack, (void *)tok);
        break;
      case TOK_UNKNOWN:
        fprintf(stderr, "Error: Unknown token '%s'!\n", tok->rep);
        exit(1);
        break;
      case TOK_EOF:
        break;
    }
    tok = next_token();
  }

  // Pop the rest of the tokens of the opstack
  while(!isempty_stack(opstack)) push_queue(outqueue, pop_stack(opstack));

  return make_ast(outqueue);
}

static void process_operator(token_t *tok, stack_t *opstack, queue_t *outqueue)
{
  token_t *top = (token_t *)peek_stack(opstack);
  while(!isempty_stack(opstack) && top->prec >= tok->prec) {
    push_queue(outqueue, pop_stack(opstack));
    top = (token_t *)peek_stack(opstack);
  }
  push_stack(opstack, (void *)tok);
}

static void process_rparen(stack_t *opstack, queue_t *outqueue)
{
  token_t *top = (void *)pop_stack(opstack);
  while(!isempty_stack(opstack) && top->type != TOK_LPAREN) {
    push_queue(outqueue, (void *)top);
    top = (void *)pop_stack(opstack);
  }
}

