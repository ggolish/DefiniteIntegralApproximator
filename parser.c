#include "parser.h"
#include "stqu.h"

ast_t *parse_equ(char *equ)
{
  init_scanner(equ);

  token_t *tok = next_token();
  while(tok->type != TOK_EOF) {

  }
}
