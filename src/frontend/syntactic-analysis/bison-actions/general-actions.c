#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"
#include "bison-actions.h"

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

    stAddVariable(varname, function);  // add variable to symbol table

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