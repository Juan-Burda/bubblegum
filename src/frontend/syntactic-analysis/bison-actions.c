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

AnimationNode* AnimationAction(AnimationType type, AnimationUnion value) {
    LogDebug("\tAnimationNodeAction");

    AnimationNode* result = (AnimationNode*)_calloc(1, sizeof(AnimationNode));
    result->type = type;
    result->value = value;

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
ShapeNode* ShapeAction(ShapeType type, ShapeUnion value) {
    LogDebug("\tShapeNodeAction");

    ShapeNode* result = (ShapeNode*)_calloc(1, sizeof(ShapeNode));
    result->type = type;
    result->value = value;

    ParameterMap* map = NULL;
    stAddParametersToShape(&map, result);

    /* TODO: BORRAR!!!!
    ParameterMap *currParam, *tmp;
    HASH_ITER(hh, map, currParam, tmp) {
        switch (currParam->type) {
            case PS_S_FILL_COLOR:
            case PS_S_BORDER_COLOR:
                LogDebug("\t[ param: %d, { value: %s }}]\n", currParam->type, currParam->value.color);
                break;

            case PS_R_HEIGHT:
            default:
                LogDebug("\t[ param: %d, { value: %d }}]\n", currParam->type, currParam->value.integer);
                break;
        }
    }
    */

    return result;
}

/** Vectors */
VectorNode* VectorAction(VectorType type, VectorUnion value) {
    LogDebug("\tVectorNodeAction");

    VectorNode* result = (VectorNode*)_calloc(1, sizeof(VectorNode));
    result->type = type;
    result->value = value;

    return result;
}

/** Parameters */
/**
 * For parameters we always have the same pattern:
 * 	- We need to save a certain parameter's value -> this is done in Param<sth>Node
 * 	- We need to add a new paramter -> this is done in ParamList<sth>Node
 */
/* Animation */
ParamAnimationNode* ParamAnimationAction(ParameterType type, ParamAnimationUnion value) {
    LogDebug("\tParamAnimationAction");

    ParamAnimationNode* result = (ParamAnimationNode*)_calloc(1, sizeof(ParamAnimationNode));
    result->type = type;
    result->value = value;

    return result;
}

// For translate
ParamListTranslateNode* ParamListTranslateAddParamAction(ParamListTranslateType type, ParamListTranslateNode* listNode, ParamListTranslateUnion value) {
    LogDebug("\tParamListTranslateAddParamAction");

    ParamListTranslateNode* result = (ParamListTranslateNode*)_calloc(1, sizeof(ParamListTranslateNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamTranslateNode* ParamTranslateAction(ParameterType type, ParamTranslateUnion value) {
    LogDebug("\tParamTranslateAction");

    ParamTranslateNode* result = (ParamTranslateNode*)_calloc(1, sizeof(ParamTranslateNode));
    result->type = type;
    result->value = value;

    return result;
}

// For opacity
ParamListOpacityNode* ParamListOpacityAddParamAction(ParamListOpacityType type, ParamListOpacityNode* listNode, ParamListOpacityUnion value) {
    LogDebug("\tParamListOpacityAddParamAction");

    ParamListOpacityNode* result = (ParamListOpacityNode*)_calloc(1, sizeof(ParamListOpacityNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamOpacityNode* ParamOpacityAction(ParameterType type, ParamOpacityUnion value) {
    LogDebug("\tParamOpacityAction");

    ParamOpacityNode* result = (ParamOpacityNode*)_calloc(1, sizeof(ParamOpacityNode));
    result->type = type;
    result->value = value;

    return result;
}

// For rotate
ParamListRotateNode* ParamListRotateAddParamAction(ParamListRotateType type, ParamListRotateNode* listNode, ParamListRotateUnion value) {
    LogDebug("\tParamListRotateAddParamAction");

    ParamListRotateNode* result = (ParamListRotateNode*)_calloc(1, sizeof(ParamListRotateNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamRotateNode* ParamRotateAction(ParameterType type, ParamRotateUnion value) {
    LogDebug("\tParamRotateAction");

    ParamRotateNode* result = (ParamRotateNode*)_calloc(1, sizeof(ParamRotateNode));
    result->type = type;
    result->value = value;

    return result;
}

// For resize
ParamListResizeNode* ParamListResizeAddParamAction(ParamListResizeType type, ParamListResizeNode* listNode, ParamListResizeUnion value) {
    LogDebug("\tParamListResizeAddParamAction");

    ParamListResizeNode* result = (ParamListResizeNode*)_calloc(1, sizeof(ParamListResizeNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamResizeNode* ParamResizeAction(ParameterType type, ParamResizeUnion value) {
    LogDebug("\tParamResizeAction");

    ParamResizeNode* result = (ParamResizeNode*)_calloc(1, sizeof(ParamResizeNode));
    result->type = type;
    result->value = value;

    return result;
}

// For morph
ParamListMorphNode* ParamListMorphAddParamAction(ParamListMorphType type, ParamListMorphNode* listNode, ParamListMorphUnion value) {
    LogDebug("\tParamListMorphAddParamAction");

    ParamListMorphNode* result = (ParamListMorphNode*)_calloc(1, sizeof(ParamListMorphNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamMorphNode* ParamMorphAction(ParameterType type, ParamMorphUnion value) {
    LogDebug("\tParamMorphAction");

    ParamMorphNode* result = (ParamMorphNode*)_calloc(1, sizeof(ParamMorphNode));
    result->type = type;
    result->value = value;

    return result;
}

// For recolor
ParamListRecolorNode* ParamListRecolorAddParamAction(ParamListRecolorType type, ParamListRecolorNode* listNode, ParamListRecolorUnion value) {
    LogDebug("\tParamListRecolorAddParamAction");

    ParamListRecolorNode* result = (ParamListRecolorNode*)_calloc(1, sizeof(ParamListRecolorNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamRecolorNode* ParamRecolorAction(ParameterType type, ParamRecolorUnion value) {
    LogDebug("\tParamRecolorAction");

    ParamRecolorNode* result = (ParamRecolorNode*)_calloc(1, sizeof(ParamRecolorNode));
    result->type = type;
    result->value = value;

    return result;
}

/* Shapes */
ParamShapeNode* ParamShapeAction(ParameterType type, ParamShapeUnion value) {
    LogDebug("\tParamShapeAction");

    ParamShapeNode* result = (ParamShapeNode*)_calloc(1, sizeof(ParamShapeNode));
    result->type = type;
    result->value = value;

    return result;
}

// For rectangles
ParamListRectangleNode* ParamListRectangleAddParamAction(ParamListRectangleType type, ParamListRectangleNode* listNode, ParamListRectangleUnion value) {
    LogDebug("\tParamListRectangleAddParamAction");

    ParamListRectangleNode* result = (ParamListRectangleNode*)_calloc(1, sizeof(ParamListRectangleNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamRectangleNode* ParamRectangleAction(ParameterType type, ParamRectangleUnion value) {
    LogDebug("\tParamRectangleAction");

    ParamRectangleNode* result = (ParamRectangleNode*)_calloc(1, sizeof(ParamRectangleNode));
    result->type = type;
    result->value = value;

    return result;
}

// For ellipse
ParamListEllipseNode* ParamListEllipseAddParamAction(ParamListEllipseType type, ParamListEllipseNode* listNode, ParamListEllipseUnion value) {
    LogDebug("\tParamListEllipseAddParamAction");

    ParamListEllipseNode* result = (ParamListEllipseNode*)_calloc(1, sizeof(ParamListEllipseNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamEllipseNode* ParamEllipseAction(ParameterType type, ParamEllipseUnion value) {
    LogDebug("\tParamEllipseAction");

    ParamEllipseNode* result = (ParamEllipseNode*)_calloc(1, sizeof(ParamEllipseNode));
    result->type = type;
    result->value = value;

    return result;
}

// For triangle
ParamListTriangleNode* ParamListTriangleAddParamAction(ParamListTriangleType type, ParamListTriangleNode* listNode, ParamListTriangleUnion value) {
    LogDebug("\tParamListTriangleAddParamShapeAction");

    ParamListTriangleNode* result = (ParamListTriangleNode*)_calloc(1, sizeof(ParamListTriangleNode));
    result->type = type;
    result->tail = listNode;
    result->value = value;

    return result;
}

ParamTriangleNode* ParamTriangleAction(ParameterType type, ParamTriangleUnion value) {
    LogDebug("\tParamTriangleAction");

    ParamTriangleNode* result = (ParamTriangleNode*)_calloc(1, sizeof(ParamTriangleNode));
    result->type = type;
    result->value = value;

    return result;
}

/* Vectors */
// For images
ParamListImageNode* ParamListImageAddParamAction(ParamListImageNode* listNode, ParamImageNode* imageNode) {
    LogDebug("\tParamListImageMultipleAction");

    ParamListImageNode* result = (ParamListImageNode*)_calloc(1, sizeof(ParamListImageNode));
    result->tail = listNode;
    result->paramImageNode = imageNode;

    return result;
}

ParamImageNode* ParamImageAction(char* typeUrl) {
    LogDebug("\tParamImageAction");

    ParamImageNode* result = (ParamImageNode*)_calloc(1, sizeof(ParamImageNode));
    result->typeUrl = typeUrl;

    return result;
}

// For text
ParamListTextNode* ParamListTextAddParamAction(ParamListTextNode* listNode, ParamTextNode* textNode) {
    LogDebug("\tParamListTextMultipleAction");

    ParamListTextNode* result = (ParamListTextNode*)_calloc(1, sizeof(ParamListTextNode));
    result->tail = listNode;
    result->paramTextNode = textNode;

    return result;
}

ParamTextNode* ParamTextAction(ParameterType type, ParamTextUnion value) {
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
    result->typeColor = typeColor;

    return result;
}

ParamTypePointsNode* ParamTypePointsAddPointAction(ParamTypePointsNode* pointsNode, float floating) {
    ParamTypePointsNode* result = (ParamTypePointsNode*)_calloc(1, sizeof(ParamTypePointsNode));
    result->nextPoint = pointsNode;
    result->floating = floating;

    return result;
}