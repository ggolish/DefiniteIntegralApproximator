#include "simpson.h"
#include "parser.h"
#include "ast.h"
#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  args_t *args = args_parse(argc, argv); 

  if(!args->params_list) read_integral_params(args);
  if(!args->equation) read_equation(args);

  args_print(args);

  ast_t *equ = parse_equ(args->equation);
  
  long double answer = simpson_approximate_integral(equ, args);

  printf("%.4Lf\n", answer);

  args_destroy(args);

  return EXIT_SUCCESS;
}
