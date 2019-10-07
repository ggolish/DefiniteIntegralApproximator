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
static token_t *make_token(token_type_t type, int prec);
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
  if(c == '\0') return make_token(TOK_EOF, OPPREC_0);

  add_rep(c);
  
  // Check if token is a number
  if(isdigit(c)) {
    while(isdigit(peek())) {
      c = advance();
      add_rep(c);
    }
    if(peek() == '.') {
      c = advance();
      add_rep(c);
      while(isdigit(peek())) {
        c = advance();
        add_rep(c);
      }
    }
    end_rep();
    return make_token(TOK_NUM, OPPREC_0);
  }

  // Check if the token is a variable or function name
  if(isalpha(c)) {
    while(isalpha(peek())) {
      c = advance();
      add_rep(c);
    }
    end_rep();
    if(peek() == '(') {
      if(strcasecmp("sin", rep) == 0) {
        return make_token(TOK_SIN, OPPREC_4);
      }
      if(strcasecmp("cos", rep) == 0) {
        return make_token(TOK_COS, OPPREC_4);
      }
      if(strcasecmp("tan", rep) == 0) {
        return make_token(TOK_TAN, OPPREC_4);
      }
      if(strcasecmp("sqrt", rep) == 0) {
        return make_token(TOK_SQRT, OPPREC_4);
      }
      if(strcasecmp("ln", rep) == 0) {
        return make_token(TOK_SQRT, OPPREC_4);
      }
      return make_token(TOK_UNKNOWN, OPPREC_0);
    } else {
      return make_token(TOK_VAR, OPPREC_0);
    }
  }

  // Find single character tokens
  switch(c) {
    case '+':
      return make_token(TOK_PLUS, OPPREC_1);
    case '-':
      return make_token(TOK_MINUS, OPPREC_1);
    case '*':
      return make_token(TOK_MULT, OPPREC_2);
    case '/':
      return make_token(TOK_DIV, OPPREC_2);
    case '^':
      return make_token(TOK_EXP, OPPREC_3);
    case '(':
      return make_token(TOK_LPAREN, OPPREC_0);
    case ')':
      return make_token(TOK_RPAREN, OPPREC_0);
  }

  return make_token(TOK_UNKNOWN, OPPREC_0);
}

// Prints a token based on its type
void print_token(token_t *tok)
{
  if(!tok) {
    printf("NULL token!\n");
  }

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
    case TOK_LN:
      printf("TOK_LN\n");
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

// Creates a new token of a given type
static token_t *make_token(token_type_t type, int prec)
{
  token_t *tok = NULL;
  
  if((tok = (token_t *)malloc(sizeof(token_t))) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    return NULL;
  }

  // Fill in token attributes
  tok->type = type;
  tok->prec = prec;
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

