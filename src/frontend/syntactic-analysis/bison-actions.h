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
AnimationNode* AnimationAction(AnimationType type, AnimationUnion value);

/* Layouts */
LayoutCompoundStatementNode* LayoutCompoundStatementAction(FunctionListNode* listNode);
LayoutNode* LayoutAction(layout_t layout, LayoutCompoundStatementNode* compoundStatement);

/* Shapes */
ShapeNode* ShapeAction(ShapeType type, ShapeUnion value);

/* Vectors */
VectorNode* VectorAction(VectorType type, VectorUnion value);

/* Parameters */
// For animations
ParamAnimationNode* ParamAnimationAction(ParameterType type, ParamAnimationUnion value);

ParamListTranslateNode* ParamListTranslateAddParamAction(ListNodeType type, ParamListTranslateNode* listNode, ParamListTranslateUnion value);
ParamTranslateNode* ParamTranslateAction(ParameterType type, ParamTranslateUnion value);

ParamListOpacityNode* ParamListOpacityAddParamAction(ListNodeType type, ParamListOpacityNode* listNode, ParamListOpacityUnion value);
ParamOpacityNode* ParamOpacityAction(ParameterType type, ParamOpacityUnion value);

ParamListRotateNode* ParamListRotateAddParamAction(ListNodeType type, ParamListRotateNode* listNode, ParamListRotateUnion value);
ParamRotateNode* ParamRotateAction(ParameterType type, ParamRotateUnion value);

ParamListResizeNode* ParamListResizeAddParamAction(ListNodeType type, ParamListResizeNode* listNode, ParamListResizeUnion value);
ParamResizeNode* ParamResizeAction(ParameterType type, ParamResizeUnion value);

ParamListMorphNode* ParamListMorphAddParamAction(ListNodeType type, ParamListMorphNode* listNode, ParamListMorphUnion value);
ParamMorphNode* ParamMorphAction(ParameterType type, ParamMorphUnion value);

ParamListRecolorNode* ParamListRecolorAddParamAction(ParamListRecolorType type, ParamListRecolorNode* listNode, ParamListRecolorUnion value);
ParamRecolorNode* ParamRecolorAction(ParameterType type, ParamRecolorUnion value);

// For shapes
ParamShapeNode* ParamShapeAction(ParameterType type, ParamShapeUnion value);

ParamListRectangleNode* ParamListRectangleAddParamAction(ListNodeType type, ParamListRectangleNode* listNode, ParamListRectangleUnion value);
ParamRectangleNode* ParamRectangleAction(ParameterType type, ParamRectangleUnion value);

ParamListEllipseNode* ParamListEllipseAddParamAction(ListNodeType type, ParamListEllipseNode* listNode, ParamListEllipseUnion value);
ParamEllipseNode* ParamEllipseAction(ParameterType type, ParamEllipseUnion value);

ParamListTriangleNode* ParamListTriangleAddParamAction(ListNodeType type, ParamListTriangleNode* listNode, ParamListTriangleUnion value);
ParamTriangleNode* ParamTriangleAction(ParameterType type, ParamTriangleUnion value);

// For vectors
ParamListImageNode* ParamListImageAddParamAction(ParamListImageNode* listNode, ParamImageNode* imageNode);
ParamImageNode* ParamImageAction(char* typeUrl);

ParamListTextNode* ParamListTextAddParamAction(ParamListTextNode* listNode, ParamTextNode* textNode);
ParamTextNode* ParamTextAction(ParameterType type, ParamTextUnion value);

// For data types
ParamTypeColorNode* ParamTypeColorAction(char* typeColor);
ParamTypePointsNode* ParamTypePointsAddPointAction(ParamTypePointsNode* pointsNode, float floating);

#endif
