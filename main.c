#include "simpson.h"
#include "parser.h"
#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

  // TODO: Move the stablizing process below to its own function in the simpson
  // module

  // Keep approximating the integral, doubling the number of subdivisions each
  // time, until the approximation stablizes
  long double k = 2;
  long double ans = integrate_simpson(ast, a, b, k);
  for(;;) {
    k *= 2;
    long double curr = integrate_simpson(ast, a, b, k);
    if(fabsl(curr - ans) < 0.0001L) {  // Ensures accurracy to 3 decimal places
      ans = curr;
      break;
    }
    ans = curr;
  }

  printf("%.3Lf\n", ans);

  return EXIT_SUCCESS;
}
