#ifndef SIMPSON_H_
#define SIMPSON_H_

#include "ast.h"
#include "args.h"

long double simpson_approximate_integral(ast_t *equ, args_t *args);
long double integrate_simpson(ast_t *ast, long double a, long double b, int n);

#endif
