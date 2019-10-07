#include "simpson.h"
#include "utility.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static bool is_valid_equ(ast_t *equ, args_t *args);
static long double simspon_integrate(ast_t *equ, args_t *args, int nsamples);
static long double simpson_summation(ast_t *equ, args_t *args, int nsamples, var_t *curr_variables, int current_dim, long double coefficient);

long double simpson_approximate_integral(ast_t *equ, args_t *args)
{
  if(!is_valid_equ(equ, args)) exit(1);

  int nsamples = 2;
  long double prev_est = simspon_integrate(equ, args, nsamples);

  for(;;) {
    nsamples *= 2;
    printf("Using mesh size %d...\n", nsamples);
    long double curr_est = simspon_integrate(equ, args, nsamples);
    if(fabsl(curr_est - prev_est) < 0.0000001L) {
      prev_est = curr_est;
      break;
    }
    prev_est = curr_est;
  }

  return prev_est;
}

static long double simspon_integrate(ast_t *equ, args_t *args, int nsamples)
{
  var_t *variables = (var_t *)safe_malloc(args->integral_dimension * sizeof(var_t));
  long double sum = simpson_summation(equ, args, nsamples, variables, 1, 1.0L);
  long double nthird = 1;
  for(int i = 0; i < args->integral_dimension; ++i) {
    long double delta = (args->params_list[i]->to - args->params_list[i]->from) / nsamples;
    nthird *= delta / 3.0L;
  }

  return nthird * sum;
}

static long double simpson_summation(
    ast_t *equ,
    args_t *args,
    int nsamples,
    var_t *curr_variables, 
    int current_dim, 
    long double coefficient)

{
  integral_params_t *params = args->params_list[current_dim - 1];
  long double sum = 0.0L;
  long double delta = (params->to - params->from) / nsamples;
  for(int i = 0; i <= nsamples; ++i) {
    long double m = (i == 0 || i == nsamples) ? (1.0L) : ((i % 2 == 0) ? (2.0L) : (4.0L));
    long double curr_coeficient = coefficient * m;
    long double curr_value = params->from + i * delta;
    curr_variables[current_dim] = (var_t){.name = params->variable, .value = curr_value};
    if(current_dim == args->integral_dimension) {
      sum += curr_coeficient * evaluate_ast(equ, curr_variables);
    } else {
      sum += simpson_summation(equ, args, nsamples, curr_variables, current_dim + 1, curr_coeficient);
    }
  }

  return sum;
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

