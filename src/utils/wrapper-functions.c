#include "wrapper-functions.h"

void* _malloc(size_t size) {
    void* result;

    if ((result = malloc(size)) == NULL)
        exit(EXIT_FAILURE);
    return result;
}

void* _calloc(size_t nmemb, size_t size) {
    void* result;

    if ((result = calloc(nmemb, size)) == NULL)
        exit(EXIT_FAILURE);
    return result;
}