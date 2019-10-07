#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdlib.h>

void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);

#endif
