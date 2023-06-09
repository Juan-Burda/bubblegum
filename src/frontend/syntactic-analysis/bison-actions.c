#include "bison-actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../backend/support/logger.h"
#include "../../backend/support/symbol-table.h"
#include "../../utils/wrapper-functions.h"

/**
 * Implementación de "bison-grammar.h".
 */

/**
 * Esta función se ejecuta cada vez que se emite un error de sintaxis.
 */
void yyerror(const char* string) {
    LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
    LogError("En ASCII es:");
    LogErrorRaw("\t");
    const int length = strlen(yytext);
    for (int i = 0; i < length; ++i) {
        LogErrorRaw("[%d]", yytext[i]);
    }
    LogErrorRaw("\n\n");
}

/** Others */
// Program
/**
 * Esta acción se corresponde con el no-terminal que representa el símbolo
 * inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
 * indica que efectivamente el programa de entrada se pudo generar con esta
 * gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
 */
Program* ProgramAction(ExpressionNode* expression) {
    LogDebug("\tProgramAction");

    Program* result = (Program*)_calloc(1, sizeof(Program));
    result->expression = expression;

    /*
     * "state" es una variable global que almacena el estado del compilador,
     * cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
     * es utilizada en la función "main".
     */
    state.succeed = true;

    /*
     * Por otro lado, "result" contiene el resultado de aplicar el análisis
     * sintáctico mediante Bison, y almacenar el nood raíz del AST construido
     * en esta variable. Para el ejemplo de la calculadora, no hay AST porque
     * la expresión se computa on-the-fly, y es la razón por la cual esta
     * variable es un simple entero, en lugar de un nodo.
     */
    state.result = 0;

    return result;
}

// Expression
ExpressionNode* ExpressionAction(ExpressionType type, ExpressionUnion value, ExpressionNode* expression) {
    LogDebug("\tExpressionNodeAction");

    ExpressionNode* result = (ExpressionNode*)_calloc(1, sizeof(ExpressionNode));
    result->type = type;
    result->value = value;
    result->nextExpression = expression;

    return result;
}

// Assign
AssignNode* AssignAction(char* varname, FunctionNode* function) {
    LogDebug("\tAssignNodeAction");

    AssignNode* result = (AssignNode*)_calloc(1, sizeof(AssignNode));
    result->varname = varname;
    result->function = function;

    return result;
}

// Function
FunctionNode* FunctionAction(FunctionType type, FunctionUnion value) {
    LogDebug("\tFunctionNodeAction");

    FunctionNode* result = (FunctionNode*)_calloc(1, sizeof(FunctionNode));
    result->type = type;
    result->value = value;

    return result;
}

FunctionListNode* FunctionListAction(FunctionListType type, FunctionListNode* listNode, FunctionListUnion value) {
    LogDebug("\tFunctionListNodeAction");

    FunctionListNode* result = (FunctionListNode*)_calloc(1, sizeof(FunctionListNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

/** Animations */
AnimationCompoundStatementNode* AnimationCompoundStatementAction(AnimationCompoundStatementType type, AnimationCompoundStatementUnion value) {
    LogDebug("\tAnimationCompoundStatementNodeAction");

    AnimationCompoundStatementNode* result = (AnimationCompoundStatementNode*)_calloc(1, sizeof(AnimationCompoundStatementNode));
    result->type = type;
    result->value = value;

    return result;
}

AnimationNode* AnimationAction(AnimationType type, ParamListAnimationNode* paramList, AnimationCompoundStatementNode* compoundStatement) {
    LogDebug("\tAnimationNodeAction");

    AnimationNode* result = (AnimationNode*)_calloc(1, sizeof(AnimationNode));
    result->type = type;
    result->paramList = paramList;
    result->compoundStatement = compoundStatement;

    ParameterMap* map = NULL;
    stAddParametersToAnimation(&map, result);

    return result;
}

/** Layouts */
LayoutCompoundStatementNode* LayoutCompoundStatementAction(FunctionListNode* tail) {
    LogDebug("\tLayoutCompoundStatementNodeAction");

    LayoutCompoundStatementNode* result = (LayoutCompoundStatementNode*)_calloc(1, sizeof(LayoutCompoundStatementNode));
    result->functionList = tail;

    return result;
}

LayoutNode* LayoutAction(layout_t layout, LayoutCompoundStatementNode* compoundStatement) {
    LogDebug("\tLayoutAction");

    LayoutNode* result = (LayoutNode*)_calloc(1, sizeof(LayoutNode));
    result->layout = layout;
    result->compoundStatement = compoundStatement;

    return result;
}

/** Shapes */
ShapeNode* ShapeAction(ShapeType type, ParamListShapeNode* paramList) {
    LogDebug("\tShapeNodeAction");

    ShapeNode* result = (ShapeNode*)_calloc(1, sizeof(ShapeNode));
    result->type = type;
    result->paramList = paramList;

    ParameterMap* map = NULL;
    stAddParametersToShape(&map, result);

    return result;
}

/** Media */
MediaNode* MediaAction(MediaType type, ParamListMediaNode* paramList) {
    LogDebug("\tMediaNodeAction");

    MediaNode* result = (MediaNode*)_calloc(1, sizeof(MediaNode));
    result->type = type;
    result->paramList = paramList;

    ParameterMap* map = NULL;
    stAddParametersToMedia(&map, result);

    return result;
}

/** Text */
TextNode* TextAction(ParamListTextNode* paramList) {
    LogDebug("\tTextNodeAction");

    TextNode* result = (TextNode*)_calloc(1, sizeof(TextNode));

    ParameterMap* map = NULL;
    stAddParametersToText(&map, result);

    return result;
}

/** Parameters */
/**
 * For parameters we always have the same pattern:
 * 	- We need to save a certain parameter's value -> this is done in Param<sth>Node
 * 	- We need to add a new paramter -> this is done in ParamList<sth>Node
 */
/* Animation */
ParamAnimationNode* ParamAnimationAction(parameter_t type, ParamAnimationUnion value) {
    LogDebug("\tParamAnimationAction");

    ParamAnimationNode* result = (ParamAnimationNode*)_calloc(1, sizeof(ParamAnimationNode));
    result->type = type;
    result->value = value;

    return result;
}

ParamListAnimationNode* ParamListAnimationAddParamAction(boolean_t isEmpty, ParamListAnimationNode* listNode, ParamAnimationNode* value) {
    LogDebug("\tParamListAnimationAddParamAction");

    ParamListAnimationNode* result = (ParamListAnimationNode*)_calloc(1, sizeof(ParamListAnimationNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}

/* Shapes */
ParamShapeNode* ParamShapeAction(parameter_t type, ParamShapeUnion value) {
    LogDebug("\tParamShapeAction");

    ParamShapeNode* result = (ParamShapeNode*)_calloc(1, sizeof(ParamShapeNode));
    result->type = type;
    result->value = value;

    return result;
}

ParamListShapeNode* ParamListShapeAddParamAction(boolean_t isEmpty, ParamListShapeNode* listNode, ParamShapeNode* value) {
    LogDebug("\tParamListShapeAddParamAction");

    ParamListShapeNode* result = (ParamListShapeNode*)_calloc(1, sizeof(ParamListShapeNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}

/* Vectors */
// For images
ParamListMediaNode* ParamListMediaAddParamAction(boolean_t isEmpty, ParamListMediaNode* listNode, ParamMediaNode* value) {
    LogDebug("\tParamListImageAddParamAction");

    ParamListMediaNode* result = (ParamListMediaNode*)_calloc(1, sizeof(ParamListMediaNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}

ParamMediaNode* ParamMediaAction(parameter_t type, ParamMediaUnion value) {
    LogDebug("\tParamImageAction");

    ParamMediaNode* result = (ParamMediaNode*)_calloc(1, sizeof(ParamMediaNode));
    result->type = type;
    result->value = value;

    return result;
}

// For text
ParamListTextNode* ParamListTextAddParamAction(boolean_t isEmpty, ParamListTextNode* listNode, ParamTextNode* value) {
    LogDebug("\tParamListTextMultipleAction");

    ParamListTextNode* result = (ParamListTextNode*)_calloc(1, sizeof(ParamListTextNode));
    result->isEmpty = isEmpty;
    result->tail = listNode;
    result->parameter = value;

    return result;
}

ParamTextNode* ParamTextAction(parameter_t type, ParamTextUnion value) {
    LogDebug("\tParamTextAction");

    ParamTextNode* result = (ParamTextNode*)_calloc(1, sizeof(ParamTextNode));
    result->type = type;
    result->value = value;

    return result;
}

/* Data types actions*/
ParamTypeColorNode* ParamTypeColorAction(char* typeColor) {
    LogDebug("\tParamTypeColorAction: %s", typeColor);

    ParamTypeColorNode* result = (ParamTypeColorNode*)_calloc(1, sizeof(ParamTypeColorNode));
    result->string = typeColor;

    return result;
}

ParamTypePointsNode* ParamTypePointsAddPointAction(ParamTypePointsNode* pointsNode, float floating) {
    ParamTypePointsNode* result = (ParamTypePointsNode*)_calloc(1, sizeof(ParamTypePointsNode));
    result->nextPoint = pointsNode;
    result->floating = floating;

    return result;
}