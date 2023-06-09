#ifndef _WRAPPER_FUNCTIONS_H_
#define _WRAPPER_FUNCTIONS_H_

#include <stdlib.h>

/**
 * Wrapper functions to those in C libraries that ensure errors are handled correctly
 */

#define ERROR_MALLOC "malloc()"
#define ERROR_CALLOC "calloc()"

void* _malloc(size_t size);
void* _calloc(size_t nmemb, size_t size);

#endif
