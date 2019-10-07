#ifndef SIMPSON_H_
#define SIMPSON_H_

#include "ast.h"
#include "args.h"

long double simpson_approximate_integral(ast_t *equ, args_t *args);

#endif
