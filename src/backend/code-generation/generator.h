#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../../utils/sb.h"
#include "../semantic-analysis/abstract-syntax-tree.h"
#include "../support/logger.h"
#include "../support/shared.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define TABS ("\t\t\t\t\t\t\t\t\t\t")

typedef struct Generator {
    StringBuilder *htmlSb;
    StringBuilder *cssSb;
    StringBuilder *jsSb;
} Generator;


#ifdef WEB_ENV

Generator generateProgram();

#else

void generateProgram();

#endif

void generateExpression(Generator generator, ExpressionNode *expression);

void generateFunction(Generator generator, FunctionNode *function);

void generateFunctionList(Generator generator, FunctionListNode *functionList);

void generateVariable(Generator generator, char* varname);

#endif
