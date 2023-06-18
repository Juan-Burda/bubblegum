#include "problem-context.h"
#include <stdio.h>
#include <string.h>
#include "../error-codes.h"
#include "../stringify.h"
#include "../wrapper-functions.h"

ProblemContext* createProblem(ProblemType type, char* message, int lineno) {
    ProblemContext* result = (ProblemContext*)_calloc(1, sizeof(ProblemContext));
    result->message = (char*)_calloc(strlen(message), sizeof(char));
    strcpy(result->message, message);
    result->lineno = lineno;
    result->type = type;

    return result;
}

char* problemToString(ProblemContext* context) {
    char* result = _calloc(WE_SIZE, sizeof(char));
    sprintf(result, "[%s] Line %d: %s\n", stringifyProblemType(context->type), context->lineno, context->message);

    return result;
}