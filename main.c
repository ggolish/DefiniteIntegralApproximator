#include "simpson.h"
#include "parser.h"
#include "ast.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  long double a, b;

  scanf("%Lf\n", &a);
  scanf("%Lf\n", &b);

  char *equ = NULL;
  size_t n = 0;

  // Read the function from stdin into a single buffer
  if(getline(&equ, &n, stdin) == -1) {
    fprintf(stderr, "Error: No input equation was read!\n");
    exit(1);
  }
  
  ast_t *ast = parse_equ(equ);
  printf("%.3Lf\n", integrate_simpson(ast, a, b, 4));

  return EXIT_SUCCESS;
}
