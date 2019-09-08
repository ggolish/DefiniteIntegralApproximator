#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char *equ = NULL;
  size_t n = 0;

  // Read the function from stdin into a single buffer
  if(getline(&equ, &n, stdin) == -1) {
    fprintf(stderr, "Error: No input equation was read!\n");
    exit(1);
  }
  
  parse_equ(equ);

  return EXIT_SUCCESS;
}
