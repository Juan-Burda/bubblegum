#include "ast-utils.h"
#include "../backend/support/logger.h"
#include "../libs/uthash.h"
#include "stringify.h"

void freeProgram(Program* program) {
    LogDebug("{FREE} Program");
    freeExpression(program->expression);
    free(program);
}

void freeExpression(ExpressionNode* node) {
    LogDebug("{FREE} Expression");

    if (node->type == E_EMPTY) {
        free(node);
        return;
    }

    switch (node->type) {
        case E_FUNCTION:
            freeFunction(node->value.functionNode);
            break;

        case E_ASSIGN:
            freeAssign(node->value.assignNode);
            break;

        default:
            break;
    }

    freeExpression(node->nextExpression);
    free(node);
}

void freeAssign(AssignNode* node) {
    LogDebug("{FREE} Assign");

    freeFunction(node->function);
    free(node->varname);
    free(node);
}

void freeFunctionList(FunctionListNode* node) {
    switch (node->type) {
        case FL_FUNCTION:
            freeFunction(node->value.functionNode);
            break;

        case FL_VARNAME:
            free(node->value.varname);
            break;
    }

    if (node->tail == NULL) {
        free(node);
        return;
    }

    freeFunctionList(node->tail);
    free(node);
}

void freeFunction(FunctionNode* node) {
    LogDebug("{FREE} Function");

    switch (node->type) {
        case F_ANIMATION:
            freeAnimation(node->value.animationNode);
            break;

        case F_LAYOUT:
            freeLayout(node->value.layoutNode);
            break;

        case F_SHAPE:
            freeShape(node->value.shapeNode);
            break;

        case F_MEDIA:
            freeMedia(node->value.mediaNode);
            break;

        case F_TEXT:
            freeText(node->value.textNode);
            break;
    }
}

void freeAnimation(AnimationNode* node) {
    LogDebug("{FREE} Animation");

    switch (node->compoundStatement->type) {
        case CS_A_FUNCTION:
            freeFunction(node->compoundStatement->value.functionNode);
            break;

        case CS_A_VARNAME:
            free(node->compoundStatement->value.varname);
            break;
    }

    freeParameterMap(node->paramMap);
    free(node);
}

void freeLayout(LayoutNode* node) {
    LogDebug("{FREE} Layout");

    freeFunctionList(node->compoundStatement->functionList);
    free(node->compoundStatement);
    free(node);
}

void freeShape(ShapeNode* node) {
    LogDebug("{FREE} Shape");

    freeParameterMap(node->paramMap);
    free(node);
}

void freeMedia(MediaNode* node) {
    LogDebug("{FREE} Media");

    freeParameterMap(node->paramMap);
    free(node);
}

void freeText(TextNode* node) {
    LogDebug("{FREE} Text");

    freeParameterMap(node->paramMap);
    free(node);
}

void freeParameterMap(ParameterMap* parameters) {
    LogDebug("{FREE} Parameter Map");

    ParameterMap *currParameter, *tmp2;

    HASH_ITER(hh, parameters, currParameter, tmp2) {
        LogDebug("\t%s", stringifyParameterType(currParameter->type));
        HASH_DEL(parameters, currParameter);

        if (PARAM_IS_STRING(currParameter->type))
            free(currParameter->value.string);
        free(currParameter);
    }
}

void freeColor(ParamTypeColorNode* node) {
    LogDebug("{FREE} Color");

    free(node->string);
    free(node);
}