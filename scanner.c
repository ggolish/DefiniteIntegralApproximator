#include "scanner.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define K 1024

// The equation that is being scanned
static char *curr = NULL;
// The rep of the current token being scanned
static char rep[K] = "";
static int rep_index = 0;

static char advance();
static char peek();
static bool finished();
static token_t *make_token(token_type_t type);
static void add_rep(char c);
static void end_rep();
static void clear_rep();

// Initializes the scanners input string
void init_scanner(char *equ)
{
  curr = equ;
}

// Returns the next token
token_t *next_token()
{
  // Check if the scanner has been initialized
  if(curr == NULL) {
    fprintf(stderr, "Error: Scanner uninitialized!\n");
    return NULL;
  }

  char c = advance();

  // Eat whitespace to get to next token
  while(isspace(c)) c = advance();

  // Check if we are out of input
  if(finished()) return make_token(TOK_EOF);

  add_rep(c);
  
  // Check if token is a number
  if(isdigit(c)) {
    while(isdigit(peek())) {
      c = advance();
      add_rep(c);
    }
    end_rep();
    return make_token(TOK_NUM);
  }

  // Check if the token is a variable or function name
  if(isalpha(c)) {
    while(isalpha(peek())) {
      c = advance();
      add_rep(c);
    }
    end_rep();
    if(peek() == '(') {
      if(strcmp("sin", rep) == 0) {
        return make_token(TOK_SIN);
      }
      if(strcmp("cos", rep) == 0) {
        return make_token(TOK_COS);
      }
      if(strcmp("tan", rep) == 0) {
        return make_token(TOK_TAN);
      }
      if(strcmp("sqrt", rep) == 0) {
        return make_token(TOK_SQRT);
      }
      return make_token(TOK_UNKNOWN);
    } else {
      return make_token(TOK_VAR);
    }
  }

  // Find single character tokens
  switch(c) {
    case '+':
      return make_token(TOK_PLUS);
    case '-':
      return make_token(TOK_MINUS);
    case '*':
      return make_token(TOK_MULT);
    case '/':
      return make_token(TOK_DIV);
    case '^':
      return make_token(TOK_EXP);
    case '(':
      return make_token(TOK_LPAREN);
    case ')':
      return make_token(TOK_RPAREN);
  }

  return make_token(TOK_UNKNOWN);
}

// Prints a token based on its type
void print_token(token_t *tok)
{
  switch(tok->type) {
    case TOK_VAR:
      printf("TOK_VAR[%s]\n", tok->rep);
      break;
    case TOK_NUM:
      printf("TOK_NUM[%s]\n", tok->rep);
      break;
    case TOK_PLUS:
      printf("TOK_PLUS\n");
      break;
    case TOK_MINUS:
      printf("TOK_MINUS\n");
      break;
    case TOK_MULT:
      printf("TOK_MULT\n");
      break;
    case TOK_DIV:
      printf("TOK_DIV\n");
      break;
    case TOK_EXP:
      printf("TOK_EXP\n");
      break;
    case TOK_LPAREN:
      printf("TOK_LPAREN\n");
      break;
    case TOK_RPAREN:
      printf("TOK_RPAREN\n");
      break;
    case TOK_SIN:
      printf("TOK_SIN\n");
      break;
    case TOK_COS:
      printf("TOK_COS\n");
      break;
    case TOK_TAN:
      printf("TOK_TAN\n");
      break;
    case TOK_SQRT:
      printf("TOK_SQRT\n");
      break;
    case TOK_EOF:
      printf("TOK_EOF\n");
      break;
    case TOK_UNKNOWN:
      printf("TOK_UNKNOWN[%s]\n", tok->rep);
      break;
  }
}

// Advances the scanner and returns the current value (we are always one ahead
// of the current value)
static char advance()
{
  curr++;
  return *(curr - 1);
}

// Return the next character that advance will return without advancing
static char peek()
{
  return *curr;
}

// Determines whether the end of input has been reached
static bool finished()
{
  return (*curr == '\0'); 
}

// Creates a new token of a given type
static token_t *make_token(token_type_t type)
{
  token_t *tok = NULL;
  
  if((tok = (token_t *)malloc(sizeof(token_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  // Fill in token attributes
  tok->type = type;
  tok->rep = strdup(rep);
  clear_rep();

  return tok;
}

static void add_rep(char c)
{
  if(rep_index >= K - 2) return;
  rep[rep_index++] = c;
}

static void end_rep()
{
  rep[rep_index] = '\0';
}

// Clears the current rep
static void clear_rep()
{
  rep[0] = '\0';
  rep_index = 0;
}

