#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
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
int ProgramGrammarAction(const int value) {
	LogDebug("\tProgramGrammarAction(%d)", value);
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
	state.result = value;
	return value;
}

int Return0() {
	return 0;
}

int IntegerConstantGrammarAction(const int value) {
	LogDebug("\tIntegerConstantGrammarAction(%d)", value);
	return value;
}

ParamShapeNode * ParamShapeAction(ParamShapeType type, ParamTypeColorNode * fillColor, ParamTypeColorNode * borderColor, int borderWidth, int rotation) {
	LogDebug("\tParamShapeAction");

	ParamShapeNode * result = (ParamShapeNode*) calloc(1, sizeof(ParamShapeNode));
	result->type = type;
	result->fillColor = fillColor;
	result->borderColor = borderColor;
	result->borderWidth = borderWidth;
	result->rotation = rotation;

	return result;
}

ParamListRectangleNode* ParamListRectangleEmptyAction() {
	LogDebug("\tParamListRectangleEmptyAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->paramListRectangleType = RL_EMPTY;
	result->ParamListRectangleNode = NULL;
	result->paramRectangleNode = NULL;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListRectangleNode* ParamListRectangleAddParamShapeAction(ParamShapeNode* paramShape , ParamListRectangleNode* paramListRectangle) {
	LogDebug("\tParamListRectangleAddParamShapeAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->paramListRectangleType = RL_SHAPE_RECTANGLE_LIST;
	result->ParamListRectangleNode = paramListRectangle;
	result->paramRectangleNode = NULL;
	result->ParamShapeNode = paramShape;

	return result;
}

ParamListRectangleNode* ParamListRectangleAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListRectangleAddParamShapeAndEndAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->paramListRectangleType = RL_SHAPE;
	result->ParamListRectangleNode = NULL;
	result->paramRectangleNode = NULL;
	result->ParamShapeNode = paramShape;

	return result;
}

ParamListRectangleNode * ParamListRectangleAddParamRectangleAction(ParamRectangleNode* paramRectangle, ParamListRectangleNode*  paramListRectangle) {
	LogDebug("\tParamListRectangleAddParamRectangleAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->paramListRectangleType = RL_RECTANGLE_RECTANGLE_LIST;
	result->ParamListRectangleNode = paramListRectangle;
	result->paramRectangleNode =paramRectangle;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListRectangleNode * ParamListRectangleAddParamRectangleAndEndAction(ParamRectangleNode* paramRectangle) {
	LogDebug("\tParamListRectangleAddParamRectangleAndEndAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->paramListRectangleType = RL_RECTANGLE;
	result->ParamListRectangleNode = NULL;
	result->paramRectangleNode =paramRectangle;
	result->ParamShapeNode = NULL;

	return result;
}

ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, int height, int width) {
	LogDebug("\tParamRectangleAction");

	ParamRectangleNode * result = (ParamRectangleNode*) calloc(1, sizeof(ParamRectangleNode));
	result->type = type;
	result->height = height;
	result->width = width;

	return result;
}

ParamListEllipseNode* ParamListEllipseEmptyAction() {
	LogDebug("\tParamListEllipseEmptyAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));
	result->paramListEllipseType = EL_EMPTY;
	result->ParamListEllipseNode = NULL;
	result->paramEllipseNode = NULL;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListEllipseNode* ParamListEllipseAddParamShapeAction(ParamShapeNode* paramShape , ParamListEllipseNode* paramListEllipse) {
	LogDebug("\tParamListEllipseAddParamShapeAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));
	result->paramListEllipseType = EL_SHAPE_ELLIPSE_LIST;
	result->ParamListEllipseNode = paramListEllipse;
	result->paramEllipseNode = NULL;
	result->ParamShapeNode = paramShape;

	return result;
}

ParamListEllipseNode* ParamListEllipseAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListEllipseAddParamShapeAndEndAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));

	result->paramListEllipseType = EL_SHAPE;
	result->ParamListEllipseNode = NULL;
	result->paramEllipseNode = NULL;
	result->ParamShapeNode = paramShape;

	return result;
}

ParamListEllipseNode* ParamListEllipseAddParamEllipseAction(ParamEllipseNode* paramEllipse, ParamListEllipseNode*  paramListEllipse) {
	LogDebug("\tParamListEllipseAddParamEllipseAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));

	result->paramListEllipseType = EL_ELLIPSE_ELLIPSE_LIST;
	result->ParamListEllipseNode = paramListEllipse;
	result->paramEllipseNode = paramEllipse;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListEllipseNode* ParamListEllipseAddParamEllipseAndEndAction(ParamEllipseNode* paramEllipse) {
	LogDebug("\tParamListEllipseAddParamEllipseAndEndAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));

	result->paramListEllipseType = EL_ELLIPSE;
	result->ParamListEllipseNode = NULL;
	result->paramEllipseNode = paramEllipse;
	result->ParamShapeNode = NULL;

	return result;
}

ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, int xAxis, int yAxis) {
	LogDebug("\tParamEllipseAction");

	ParamEllipseNode * result = (ParamEllipseNode*)calloc(1,sizeof(ParamEllipseNode));
	result->type = type;
	result->x_axis = xAxis;
	result->y_axis = yAxis;

	return result;
}

ParamListTriangleNode* ParamListTriangleEmptyAction() {
	LogDebug("\tParamListTriangleEmptyAction");

	ParamListTriangleNode * result = (ParamListTriangleNode*) calloc(1, sizeof(ParamListTriangleNode));
	result->paramListTriangleType = TL_EMPTY;
	result->ParamListTriangleNode = NULL;
	result->paramTriangleNode = NULL;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListTriangleNode* ParamListTriangleAddParamShapeAction(ParamShapeNode* paramShape , ParamListTriangleNode* paramListTriangle) {
	LogDebug("\tParamListTriangleAddParamShapeAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = TL_SHAPE;
	paramListTriangleNode->ParamListTriangleNode = paramListTriangle;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = paramShape;

	return paramListTriangleNode;

}

ParamListTriangleNode* ParamListTriangleAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListTriangleAddParamShapeAndEndAction");

	ParamListTriangleNode * result = (ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	result->paramListTriangleType = TL_SHAPE;
	result->ParamListTriangleNode = NULL;
	result->paramTriangleNode = NULL;
	result->ParamShapeNode = paramShape;

	return result;
}

ParamListTriangleNode* ParamListTriangleAddParamTriangleAction(ParamTriangleNode* paramTriangle, ParamListTriangleNode*  paramListTriangle) {
	LogDebug("\tParamListTriangleAddParamTriangleAction");

	ParamListTriangleNode * result = (ParamListTriangleNode*) calloc(1, sizeof(ParamListTriangleNode));

	result->paramListTriangleType = TL_TRIANGLE_TRIANGLE_LIST;
	result->ParamListTriangleNode = paramListTriangle;
	result->paramTriangleNode = paramTriangle;
	result->ParamShapeNode = NULL;

	return result;
}

ParamListTriangleNode* ParamListTriangleAddParamTriangleAndEndAction(ParamTriangleNode* paramTriangle) {
	LogDebug("\tParamListTriangleAddParamTriangleAndEndAction");

	ParamListTriangleNode * result = (ParamListTriangleNode*) calloc(1, sizeof(ParamListTriangleNode));

	result->paramListTriangleType = TL_TRIANGLE;
	result->ParamListTriangleNode = NULL;
	result->paramTriangleNode = paramTriangle;
	result->ParamShapeNode = NULL;

	return result;
}

ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, int base, int height) {
	LogDebug("\tParamTriangleAction");

	ParamTriangleNode * result = (ParamTriangleNode*)calloc(1,sizeof(ParamTriangleNode));

	result->type = type;
	result->height = height;
	result->base = base;

	return result;
}


/* Vectors */
// For images
ParamListImageNode * ParamListImageMultipleAction(ParamImageNode * paramImageNode, ParamListImageNode * paramListImageNode) {
	LogDebug("\tParamListImageMultipleAction");

	ParamListImageNode * result = (ParamListImageNode *) calloc(1, sizeof(ParamListImageNode));
	result->paramImageNode = paramImageNode;
	result->paramListImageNode = paramListImageNode;

	return result;
}

ParamListImageNode * ParamListImageAction(ParamImageNode * paramImageNode) {
	LogDebug("\tParamListImageAction");

	ParamListImageNode * result = (ParamListImageNode*) calloc(1, sizeof(ParamListImageNode));
	result->paramImageNode = paramImageNode;
	result->paramListImageNode = NULL;

	return result;
}

ParamImageNode * ParamImageAction(char * typeUrl) {
	LogDebug("\t ParamImageAction");

	ParamImageNode * result = (ParamImageNode*) calloc(1, sizeof(ParamImageNode));
	result->typeUrl = typeUrl;

	return result;
}

// For text
ParamListTextNode * ParamListTextMultipleAction(ParamTextNode * paramTextNode, ParamListTextNode * paramListTextNode) {
	LogDebug("\t ParamListTextMultipleAction");

	ParamListTextNode * result = (ParamListTextNode*)calloc(1,sizeof(ParamListTextNode));
	result->paramTextNode = paramTextNode;
	result->paramListTextNode = paramListTextNode;

	return result;
}

ParamListTextNode * ParamListTextAction(ParamTextNode * paramTextNode){
	LogDebug("\t ParamListTextAction");

	ParamListTextNode * result = (ParamListTextNode*) calloc(1,sizeof(ParamListTextNode));
	result->paramTextNode = paramTextNode;
	result->paramListTextNode = NULL;

	return result;
}

ParamTextNode * ParamTextAction(ParamTextType type, int fontWidth, fontfamily_t fontFamily, int fontWeight, fontstyle_t fontStyle, textdeco_t textDeco, ParamTypeColorNode * paramTypeColorNode) {
	LogDebug("\t ParamTextAction");

	ParamTextNode * result = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	result->type = type;
	result->fontWidth = fontWidth;
	result->fontFamily = fontFamily;
	result->fontWeight = fontWeight;
	result->fontStyle = fontStyle;
	result->textDecoration = textDeco;
	result->paramTypeColorNode = paramTypeColorNode;

	return result;
}

/* Data types actions*/
ParamTypeColorNode * ParamTypeColorAction(char * typeColor){
	ParamTypeColorNode * result = (ParamTypeColorNode*) calloc(1, sizeof(ParamTypeColorNode));
	result->typeColor = typeColor;

	return result;
}

ParamFloatNode * ParamTypeFloatMultipleAction(float floating, ParamFloatNode * paramFloatNode) {
	ParamFloatNode * result = (ParamFloatNode*) calloc(1, sizeof(ParamFloatNode));
	result->floating = floating;
	result->paramFloatNode = paramFloatNode;

	return result;
}

ParamFloatNode * ParamTypeFloatAction(float floating) {
	ParamFloatNode * result = (ParamFloatNode*) calloc(1, sizeof(ParamFloatNode));
	result->floating = floating;
	result->paramFloatNode = NULL;

	return result;
}
