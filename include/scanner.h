#ifndef SCANNER_H_
#define SCANNER_H_

#define OPPREC_0 0 // Precedence doesn't matter
#define OPPREC_1 1 // + -
#define OPPREC_2 2 // * /
#define OPPREC_3 3 // ^
#define OPPREC_4 4 // functions

typedef enum {

  // VARIABLE/NUMBER TOKEN
  TOK_VAR, TOK_NUM,
  
  // OPERATOR TOKENS
  TOK_PLUS, TOK_MINUS, TOK_MULT, TOK_DIV, TOK_EXP, TOK_LPAREN, TOK_RPAREN,

  // FUNCTION TOKENS
  TOK_SIN, TOK_COS, TOK_TAN, TOK_SQRT, TOK_LN,

  // MISC TOKENS
  TOK_EOF, TOK_UNKNOWN,

} token_type_t;

typedef struct {
  token_type_t type;  // token type
  int prec;           // precedence of token (if operator)
  char *rep;          // string representation of token
} token_t;

void init_scanner(char *equ);
token_t *next_token();
void print_token(token_t *tok);

#endif
