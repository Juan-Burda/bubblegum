#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"
// TO-DO: check if this is correct
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
ParamShapeNode * ParamShapeAction(ParamShapeType type, ParamTypeColorNode * fillColor, ParamTypeColorNode * borderColor, int borderWidth, int rotation);

ParamListRectangleNode * ParamListRectangleEmptyAction();
ParamListRectangleNode * ParamListRectangleAddParamShapeAction(ParamShapeNode* , ParamListRectangleNode*);
ParamListRectangleNode * ParamListRectangleAddParamShapeAndEndAction(ParamShapeNode*);
ParamListRectangleNode * ParamListRectangleAddParamRectangleAction(ParamRectangleNode*, ParamListRectangleNode*);
ParamListRectangleNode * ParamListRectangleAddParamRectangleAndEndAction(ParamRectangleNode*);

ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, int height, int width);

ParamListEllipseNode * ParamListEllipseEmptyAction();
ParamListEllipseNode * ParamListEllipseAddParamShapeAction(ParamShapeNode* , ParamListEllipseNode*);
ParamListEllipseNode * ParamListEllipseAddParamShapeAndEndAction(ParamShapeNode*);
ParamListEllipseNode * ParamListEllipseAddParamEllipseAction(ParamEllipseNode*, ParamListEllipseNode*);
ParamListEllipseNode * ParamListEllipseAddParamEllipseAndEndAction(ParamEllipseNode*);

ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, int xAxis, int yAxis);

ParamListTriangleNode * ParamListTriangleEmptyAction();
ParamListTriangleNode * ParamListTriangleAddParamShapeAction(ParamShapeNode* , ParamListTriangleNode*);
ParamListTriangleNode * ParamListTriangleAddParamShapeAndEndAction(ParamShapeNode*);
ParamListTriangleNode * ParamListTriangleAddParamTriangleAction(ParamTriangleNode*, ParamListTriangleNode*);
ParamListTriangleNode * ParamListTriangleAddParamTriangleAndEndAction(ParamTriangleNode*);

ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, int height, int base);


/* Vector actions */
// For images
ParamListImageNode * ParamListImageMultipleAction(ParamImageNode * paramImageNode, ParamListImageNode * paramListImageNode);
ParamListImageNode * ParamListImageAction(ParamImageNode * paramImageNode);
ParamImageNode * ParamImageAction(char * typeUrl);

// For text
ParamListTextNode * ParamListTextMultipleAction(ParamTextNode * paramTextNode, ParamListTextNode * paramListTextNode);
ParamListTextNode * ParamListTextAction(ParamTextNode * paramTextNode);
ParamTextNode * ParamTextAction(ParamTextType type, int fontWidth, fontfamily_t fontFamily, int fontWeight, fontstyle_t fontStyle, textdeco_t textDeco, ParamTypeColorNode * paramTypeColorNode);

/* Data types actions*/
ParamTypeColorNode * ParamTypeColorAction(char * typeColor);
ParamFloatNode * ParamTypeFloatMultipleAction(float floating, ParamFloatNode * paramFloatNode);
ParamFloatNode * ParamTypeFloatAction(float floating);

#endif
