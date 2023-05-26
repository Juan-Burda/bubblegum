#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
#include "../data-types.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
int ProgramGrammarAction(const int value);

int Return0();

// Constantes.
int IntegerConstantGrammarAction(const int value);

/* Parameters */
// For animations
ParamAnimationNode * ParamAnimationAction(ParamAnimationType type, ParamAnimationUnion value);

ParamListTranslateNode * ParamListTranslateAddParamAction(ParamListTranslateType type, ParamListTranslateNode * listNode, ParamListTranslateUnion value);
ParamTranslateNode * ParamTranslateAction(ParamTranslateType type, ParamTranslateUnion value);

ParamListOpacityNode * ParamListOpacityAddParamAction(ParamListOpacityType type, ParamListOpacityNode * listNode, ParamListOpacityUnion value);
ParamOpacityNode * ParamOpacityAction(ParamOpacityType type, ParamOpacityUnion value);

ParamListRotateNode * ParamListRotateAddParamAction(ParamListRotateType type, ParamListRotateNode * listNode, ParamListRotateUnion value);
ParamRotateNode * ParamRotateAction(ParamRotateType type, ParamRotateUnion value);

ParamListResizeNode * ParamListResizeAddParamAction(ParamListResizeType type, ParamListResizeNode * listNode, ParamListResizeUnion value);
ParamResizeNode * ParamResizeAction(ParamResizeType type, ParamResizeUnion value);

ParamListMorphNode * ParamListMorphAddParamAction(ParamListMorphType type, ParamListMorphNode * listNode, ParamListMorphUnion value);
ParamMorphNode * ParamMorphAction(ParamMorphType type, ParamMorphUnion value);

ParamListRecolorNode * ParamListRecolorAddParamAction(ParamListRecolorType type, ParamListRecolorNode * listNode, ParamListRecolorUnion value);
ParamRecolorNode * ParamRecolorAction(ParamRecolorType type, ParamRecolorUnion value);

// For shapes
ParamShapeNode * ParamShapeAction(ParamShapeType type, ParamShapeUnion value);

ParamListRectangleNode * ParamListRectangleAddParamAction(ParamListRectangleType type, ParamListRectangleNode * listNode, ParamListRectangleUnion value);
ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, ParamRectangleUnion value);

ParamListEllipseNode * ParamListEllipseAddParamAction(ParamListEllipseType type, ParamListEllipseNode * listNode, ParamListEllipseUnion value);
ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, ParamEllipseUnion value);

ParamListTriangleNode * ParamListTriangleAddParamAction(ParamListTriangleType type, ParamListTriangleNode * listNode, ParamListTriangleUnion value);
ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, ParamTriangleUnion value);

// For vectors
ParamListImageNode * ParamListImageAddParamAction(ParamListImageNode * listNode, ParamImageNode * imageNode);
ParamImageNode * ParamImageAction(char * typeUrl);

ParamListTextNode * ParamListTextAddParamAction(ParamListTextNode * listNode, ParamTextNode * textNode);
ParamTextNode * ParamTextAction(ParamTextType type, ParamTextUnion value);

// For data types
ParamTypeColorNode * ParamTypeColorAction(char * typeColor);
ParamTypePointsNode * ParamTypePointsAddPointAction(ParamTypePointsNode * pointsNode, float floating);

#endif
