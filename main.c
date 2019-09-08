#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *equ = NULL;
  size_t n = 0;

  // Read the function from stdin into a single buffer
  if(getline(&equ, &n, stdin) == -1) {
    fprintf(stderr, "Error: No input equation was read!\n");
    exit(1);
  }

  init_scanner(equ);
  token_t *t = next_token();
  while(t->type != TOK_EOF) {
    print_token(t);
    t = next_token();
  }
  
  return EXIT_SUCCESS;
}
