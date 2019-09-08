#ifndef SIMPSON_H_
#define SIMPSON_H_

#include "ast.h"

long double integrate_simpson(ast_t *ast, long double a, long double b, int n);

#endif
