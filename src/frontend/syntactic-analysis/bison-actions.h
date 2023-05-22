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

ParamListRectangleNode* EmptyParamListRectangleAction();
ParamListRectangleNode* ParamShapeParamListRectangleAction(ParamShapeNode* , ParamListRectangleNode*);
ParamListRectangleNode* ParamShapeRectangleAction(ParamShapeNode*);
ParamListRectangleNode * ParamRectangleParamListRectangleAction(ParamRectangleNode*, ParamListRectangleNode*);
ParamListRectangleNode * ParamRectangleAction(ParamRectangleNode*);

ParamListEllipseNode* EmptyParamListEllipseAction();
ParamListEllipseNode* ParamShapeParamListEllipseAction(ParamShapeNode* , ParamListEllipseNode*);
ParamListEllipseNode* ParamShapeEllipseAction(ParamShapeNode*);
ParamListEllipseNode * ParamEllipseParamListEllipseAction(ParamEllipseNode*, ParamListEllipseNode*);
ParamListEllipseNode * ParamEllipseAction(ParamEllipseNode*);

ParamListTriangleNode* EmptyParamListTriangleAction();
ParamListTriangleNode* ParamShapeParamListTriangleAction(ParamShapeNode* , ParamListTriangleNode*);
ParamListTriangleNode* ParamShapeTriangleAction(ParamShapeNode*);
ParamListTriangleNode * ParamTriangleParamListTriangleAction(ParamTriangleNode*, ParamListTriangleNode*);
ParamListTriangleNode * ParamTriangleAction(ParamTriangleNode*);

ParamRectangleNode * HeightParamRectangleAction(int);
ParamRectangleNode * WidthParamRectangleAction(int);

ParamEllipseNode * XAxisParamEllipseAction(int);
ParamEllipseNode * YAxisParamEllipseAction(int); 

ParamTriangleNode * HeightParamTriangleAction(int);
ParamTriangleNode * BaseParamTriangleAction(int);

ParamShapeNode * FillColorParamShapeAction(TypeColorNode *);
ParamShapeNode * BorderColorParamShapeAction(TypeColorNode *);
ParamShapeNode * BorderWidthParamShapeAction(int width);
ParamShapeNode * RotationParamShapeAction(int rotation);

/* Image actions */

ParamListImageNode * ParamListImageMultipleAction(ParamImageNode * paramImageNode, ParamListImageNode * paramListImageNode);
ParamListImageNode * ParamListImageAction(ParamImageNode * paramImageNode);
ParamImageNode * ParamImageAction(char * typeUrl);

/* Text parameters actions */

ParamListTextNode * ParamListTextMultipleAction(ParamTextNode * paramTextNode, ParamListTextNode * paramListTextNode);
ParamListTextNode * ParamListTextAction(ParamTextNode * paramTextNode);

ParamTextNode * ParamFontWidthAction(int fontWidth);
ParamTextNode * ParamFontFamilyAction(fontfamily_t fontFamily);
ParamTextNode * ParamFontWeightAction(int fontWeight);
ParamTextNode * ParamFontStyleAction(fontstyle_t fontStyle);
ParamTextNode * ParamTextDecorationAction(textdeco_t textDecoration);
ParamTextNode * ParamBackgroundColorAction(ParamTypeColorNode * paramTextValueNode);

/* Data types actions*/

ParamTypeColorNode * ParamTypeColorAction(char * typeColor);
ParamFloatNode * ParamTypeFloatMultipleAction(float floating, ParamFloatNode * paramFloatNode);
ParamFloatNode * ParamTypeFloatAction(float floating);

#endif
