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
// For shapes
ParamShapeNode * ParamShapeAction(ParamShapeType type, ParamShapeUnion value);

ParamListRectangleNode * ParamListRectangleAddParamAction(ParamListRectangleType type, ParamListRectangleNode * listNode, ParamShapeNode * shapeNode, ParamRectangleNode * rectangleNode);
ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, ParamRectangleUnion value);

ParamListEllipseNode * ParamListEllipseAddParamAction(ParamListEllipseType type, ParamListEllipseNode * listNode, ParamShapeNode * shapeNode, ParamEllipseNode * ellipseNode);
ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, ParamEllipseUnion value);

ParamListTriangleNode * ParamListTriangleAddParamAction(ParamListTriangleType type, ParamListTriangleNode * listNode, ParamShapeNode * shapeNode, ParamTriangleNode * ellipseNode);
ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, ParamTriangleUnion value);


/* Vector actions */
// For images
ParamListImageNode * ParamListImageAddParamAction(ParamListImageNode * listNode, ParamImageNode * imageNode);
ParamImageNode * ParamImageAction(char * typeUrl);

// For text
ParamListTextNode * ParamListTextAddParamAction(ParamListTextNode * listNode, ParamTextNode * textNode);
ParamTextNode * ParamTextAction(ParamTextType type, ParamTextUnion value);

/* Data types actions*/
ParamTypeColorNode * ParamTypeColorAction(char * typeColor);
ParamFloatNode * ParamTypePointsAddPointAction(ParamFloatNode * floatNode, float floating);

#endif
