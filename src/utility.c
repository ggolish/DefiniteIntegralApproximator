#include "utility.h"

#include <stdio.h>

void *safe_malloc(size_t size)
{
  void *chunk = NULL;

  if((chunk = malloc(size)) == NULL) {
    fprintf(stderr, "Error: Malloc failed!\n");
    exit(1);
  }

  return chunk;
}

void *safe_realloc(void *ptr, size_t size)
{
  if((ptr = realloc(ptr, size)) == NULL) {
    fprintf(stderr, "Error: Realloc failed!\n");
    exit(1);
  }
  return ptr;
}
