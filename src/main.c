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

//   ast_t *ast = parse_equ(equ);
// 
//   if(!ast) {
//     fprintf(stderr, "Error: Unable to parse equation.\n");
//     exit(1);
//   }
// 
//   // Keep approximating the integral, doubling the number of subdivisions each
//   // time, until the approximation stablizes
//   long double k = 2;
//   long double ans = integrate_simpson(ast, a, b, k);
//   for(;;) {
//     k *= 2;
//     long double curr = integrate_simpson(ast, a, b, k);
//     if(fabsl(curr - ans) < 0.0001L) {  // Ensures accurracy to 3 decimal places
//       ans = curr;
//       break;
//     }
//     ans = curr;
//   }
// 
//   printf("%.3Lf\n", ans);

  args_destroy(args);

  return EXIT_SUCCESS;
}
