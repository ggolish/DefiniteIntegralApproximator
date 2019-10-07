#ifndef ARGS_H_
#define ARGS_H_

// Represents a single integral specification from <from> to <to> over the 
// variable <variable>
typedef struct {
  long double from;
  long double to;
  char variable;
} integral_params_t;

// The arguments to be parsed from the command line and from stdin. These 
// include the dimension of the specifed integral, a list of integral 
// specifications for the n-dimensional integral, as well as the equation
// the integral is to be performed on.
typedef struct {
  int integral_dimension;
  integral_params_t **params_list;
  char *equation;
} args_t;

args_t *args_parse(int argc, char *argv[]);
void read_integral_params(args_t *args);
void read_equation(args_t *args);
void args_destroy(args_t *args);
void args_print(args_t *args);

#endif
