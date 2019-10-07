#include "simpson.h"
#include "utility.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static bool is_valid_equ(ast_t *equ, args_t *args);

long double simpson_approximate_integral(ast_t *equ, args_t *args)
{
  if(!is_valid_equ(equ, args)) exit(1);
  return NAN;
}

// Approximates the definite integral given by the abstract syntax tree from a
// to b using n subdivisions
long double integrate_simpson(ast_t *ast, long double a, long double b, int n) {
  long double delta = (b - a) / n;
  long double sum = evaluate_ast(ast, a);
  long double a_i = a + delta;
  for(int i = 0; i < n - 1; ++i) {
    sum += ((i & 1)) ? (2.0L * evaluate_ast(ast, a_i)) : (4.0L * evaluate_ast(ast, a_i));
    a_i += delta;
  }
  sum += evaluate_ast(ast, a_i);
  return (delta / 3.0L) * sum;
}

static bool is_valid_equ(ast_t *equ, args_t *args)
{
  // First we check for unexpected variable in equ
  for(int i = 0; i < equ->vlen; ++i) {
    char curr = equ->variables[i];
    bool found = false;
    for(int j = 0; j < args->integral_dimension; ++j) {
      if(curr == args->params_list[j]->variable)
        found = true;
    }

    if(!found) {
      fprintf(stderr, "Error: Unexpected variable '%c'!\n", curr);
      return false;
    }
  }

  // Next, we check that all variables are represented in equ
  bool *found = (bool *)safe_malloc(args->integral_dimension * sizeof(bool));
  for(int i = 0; i < args->integral_dimension; ++i) {
    char curr = args->params_list[i]->variable;
    found[i] = false;
    for(int j = 0; j < equ->vlen; ++j) {
      if(curr == equ->variables[j])
        found[i] = true;
    }
  }

  for(int i = 0; i < args->integral_dimension; ++i) {
    if(!found[i]) {
      fprintf(stderr, "Error: Variable '%c' not represented in equation '%s'!\n",
          args->params_list[i]->variable, args->equation);
      return false;
    }
  }

  return true;
}
