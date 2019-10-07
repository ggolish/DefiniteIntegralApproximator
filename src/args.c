#include "args.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHUNK 2

static void usage(char *argv[]);
static args_t *args_new();
static void parse_params_list(char *params_list, args_t *args);
static integral_params_t *params_new(long double from, long double to, char variable);

// Parses the command line arguments to the program. Possible arguments are as
// follows:
//
//         [-n <num>]: <num> represents the integral dimension. Default is 1.
// [-p <params-list>]: <params-list> is a colon separated list of integral 
//                     params, each of which is a comma separated list of 
//                     the form <from>,<to>,<variable>. If -p is used, the 
//                     params-list should include <num> params.
//    [-e <equation>]: <equation> represents the equation to be integrated. It
//                     should contain only the variables that are specifed in 
//                     the params list.
//               [-h]: Displays the usage message.
args_t *args_parse(int argc, char *argv[])
{
  args_t *args = args_new();

  int opt;
  while((opt = getopt(argc, argv, "n:p:e:h")) != -1) {
    switch(opt) {
      case 'n':
        args->integral_dimension = atoi(optarg);
        break;
      case 'p':
        parse_params_list(optarg, args);
        break;
      case 'e':
        args->equation = strdup(optarg);
        break;
      case 'h':
        usage(argv);
        break;
    }
  }

  return args;
}

// Read the parameter list from stdin
void read_integral_params(args_t *args)
{
  args->params_list = (integral_params_t **)safe_malloc(
      args->integral_dimension * sizeof(integral_params_t *));

  for(int i = 0; i < args->integral_dimension; ++i) {
    long double from, to;
    char v;

    if(scanf("%Lf %Lf %c\n", &from, &to, &v) != 3) {
      fprintf(stderr, "Error: Parameter list is too small!\n");
      exit(1);
    }

    args->params_list[i] = params_new(from, to, v);
  }
}

// Reads the equation from stdin
void read_equation(args_t *args)
{
  size_t n = 0;
  args->equation = NULL;
  if(getline(&args->equation, &n, stdin) <= 0) {
    fprintf(stderr, "Error: Unable to read equation!\n");
    exit(1);
  }
}

// Destroys an argument list.
void args_destroy(args_t *args)
{
  if(!args) return;
  if(args->params_list) {
    if(args->integral_dimension > 0) {
      for(int i = 0; i < args->integral_dimension; ++i) {
        free(args->params_list[i]);
      }
    }
    free(args->params_list);
  }
  if(args->equation) free(args->equation);
  free(args);
}

void args_print(args_t *args)
{
  printf("Integral Dimensions: %d\n", args->integral_dimension);
  for(int i = 0; i < args->integral_dimension; ++i) {
    integral_params_t *curr = args->params_list[i];
    printf("Integrating %c from %.2Lf to %.2Lf\n", curr->variable, curr->from, curr->to);
  }
  printf("Equation: %s\n", args->equation);
}

static void usage(char *argv[])
{
  fprintf(stderr, "Usage: %s [-h] || [-n <dim> [-p <params-list>]] [-e <equation>]\n", argv[0]);
  exit(0);
}

// Creates a new argument list.
static args_t *args_new()
{
  args_t *args = (args_t *)safe_malloc(sizeof(args_t));
  args->integral_dimension = 1;
  args->params_list = NULL;
  args->equation = NULL;
  return args;
}

// Parses the params list given as a command line argument.
static void parse_params_list(char *params_list, args_t *args)
{
  int len = 0, cap = 0;
  for(char *params = strtok(params_list, ":"); params; params = strtok(NULL, ":")) {
    long double to, from;
    char v;

    if(sscanf(params, "%Lf,%Lf,%c", &from, &to, &v) != 3) {
      fprintf(stderr, "Error: Invalid integral specification '%s'!\n", params);
      exit(1);
    }

    integral_params_t *p = params_new(from, to, v);
    args_destroy(args);

    if(len >= cap - 1) {
      cap = (cap == 0) ? CHUNK : cap * 2;
      args->params_list = (integral_params_t **)safe_realloc(
          args->params_list, 
          cap * sizeof(integral_params_t *));
    }
    args->params_list[len++] = p;

    if(len > args->integral_dimension) {
      fprintf(stderr, "Error: Invalid parameter list size. Please specify integral dimension before parameter list.\n");
      exit(1);
    }
  }

  if(len < args->integral_dimension) {
    fprintf(stderr, "Error: Not enough parameter given for %d dimensional integral!\n", 
        args->integral_dimension);
    exit(1);
  }
}

// Creates a new parameter 
static integral_params_t *params_new(long double from, long double to, char variable)
{
  integral_params_t *p = (integral_params_t *)safe_malloc(sizeof(integral_params_t));
  p->from = from;
  p->to = to;
  p->variable = variable;
  return p;
}

