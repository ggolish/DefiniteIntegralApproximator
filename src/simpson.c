#include "simpson.h"

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
