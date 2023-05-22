#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

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

#endif
