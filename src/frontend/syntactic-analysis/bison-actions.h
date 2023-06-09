#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../../backend/support/shared.h"
#include "../../utils/data-types.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

/* Others */
Program* ProgramAction(ExpressionNode* expression);

ExpressionNode* ExpressionAction(ExpressionType type, ExpressionUnion value, ExpressionNode* expression);

FunctionListNode* FunctionListAction(FunctionListType type, FunctionListNode* listNode, FunctionListUnion value);
FunctionNode* FunctionAction(FunctionType type, FunctionUnion value);

AssignNode* AssignAction(char* varname, FunctionNode* function);

/* Animations */
AnimationCompoundStatementNode* AnimationCompoundStatementAction(AnimationCompoundStatementType type, AnimationCompoundStatementUnion value);
AnimationNode* AnimationAction(AnimationType type, ParamListAnimationNode* paramList, AnimationCompoundStatementNode* compoundStatement);

/* Layouts */
LayoutCompoundStatementNode* LayoutCompoundStatementAction(FunctionListNode* listNode);
LayoutNode* LayoutAction(layout_t layout, LayoutCompoundStatementNode* compoundStatement);

/* Shapes */
ShapeNode* ShapeAction(ShapeType type, ParamListShapeNode* paramList);

/* Media */
MediaNode* MediaAction(MediaType type, ParamListMediaNode* paramList);

/* Text */
TextNode* TextAction(ParamListTextNode* paramList);

/* Parameters */
// For animations
ParamAnimationNode* ParamAnimationAction(ParameterType type, ParamAnimationUnion value);
ParamListAnimationNode* ParamListAnimationAddParamAction(boolean_t isEmpty, ParamListAnimationNode* listNode, ParamAnimationNode* value);

// For shapes
ParamShapeNode* ParamShapeAction(ParameterType type, ParamShapeUnion value);
ParamListShapeNode* ParamListShapeAddParamAction(boolean_t isEmpty, ParamListShapeNode* listNode, ParamShapeNode* value);

// For vectors
ParamMediaNode* ParamMediaAction(ParameterType type, ParamMediaUnion value);
ParamListMediaNode* ParamListMediaAddParamAction(boolean_t isEmpty, ParamListMediaNode* listNode, ParamMediaNode* value);

ParamTextNode* ParamTextAction(ParameterType type, ParamTextUnion value);
ParamListTextNode* ParamListTextAddParamAction(boolean_t isEmpty, ParamListTextNode* listNode, ParamTextNode* textNode);

// For data types
ParamTypeColorNode* ParamTypeColorAction(char* typeColor);
ParamTypePointsNode* ParamTypePointsAddPointAction(ParamTypePointsNode* pointsNode, float floating);

#endif
