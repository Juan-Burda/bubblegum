#include "wrapper-functions.h"
#include <stdio.h>
#include "error-codes.h"

void* _malloc(size_t size) {
    void* result;

    if ((result = malloc(size)) == NULL) {
        perror(ERROR_MALLOC);
        exit(EXIT_FAILURE);
    }
    return result;
}

void* _calloc(size_t nmemb, size_t size) {
    void* result;

    if ((result = calloc(nmemb, size)) == NULL) {
        perror(ERROR_MALLOC);
        exit(EXIT_FAILURE);
    }
    return result;
}