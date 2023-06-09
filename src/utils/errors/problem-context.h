#ifndef PROBLEM_CONTEXT_H_
#define PROBLEM_CONTEXT_H_

#include "../error-codes.h"

typedef enum {
    WARNING,
    ERROR
} ProblemType;

typedef struct {
    char* message;
    int lineno;
    ProblemType type;
} ProblemContext;

ProblemContext* createProblemContext(ProblemType type, char* message, int lineno);

char* problemToString(ProblemContext* context);

#endif  // PROBLEM_CONTEXT_H_
