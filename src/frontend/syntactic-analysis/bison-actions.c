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

	ParamShapeNode * paramShapeNode = (ParamShapeNode*) calloc(1,sizeof(ParamShapeNode));

	paramShapeNode->type = type;
	paramShapeNode->fillColor = fillColor;
	paramShapeNode->borderColor = borderColor;
	paramShapeNode->borderWidth = borderWidth;
	paramShapeNode->rotation = rotation;

	return paramShapeNode;
}

ParamListRectangleNode* ParamListRectangleEmptyAction() {
	LogDebug("\tParamListRectangleEmptyAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RL_EMPTY;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamListRectangleNode* ParamListRectangleAddParamShapeAction(ParamShapeNode* paramShape , ParamListRectangleNode* paramListRectangle) {
	LogDebug("\tParamListRectangleAddParamShapeAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RL_SHAPE_RECTANGLE_LIST;
	paramListRectangleNode->ParamListRectangleNode = paramListRectangle;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = paramShape;

	return paramListRectangleNode;

}

ParamListRectangleNode* ParamListRectangleAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListRectangleAddParamShapeAndEndAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = SHAPE;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = paramShape;

	return paramListRectangleNode;
}

ParamListRectangleNode * ParamListRectangleAddParamRectangleAction(ParamRectangleNode* paramRectangle, ParamListRectangleNode*  paramListRectangle) {
	LogDebug("\tParamListRectangleAddParamRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RL_RECTANGLE_RECTANGLE_LIST;
	paramListRectangleNode->ParamListRectangleNode = paramListRectangle;
	paramListRectangleNode->paramRectangleNode =paramRectangle;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamListRectangleNode * ParamListRectangleAddParamRectangleAndEndAction(ParamRectangleNode* paramRectangle) {
	LogDebug("\tParamListRectangleAddParamRectangleAndEndAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RL_RECTANGLE;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode =paramRectangle;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, int height, int width) {
	LogDebug("\tParamRectangleAction");

	ParamRectangleNode * paramRectangleNode = (ParamRectangleNode*)calloc(1,sizeof(ParamRectangleNode));

	paramRectangleNode->type = type;
	paramRectangleNode->height = height;
	paramRectangleNode->width = width;

	return paramRectangleNode;
}

ParamListEllipseNode* ParamListEllipseEmptyAction() {
	LogDebug("\tParamListEllipseEmptyAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = EL_EMPTY;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamListEllipseAddParamShapeAction(ParamShapeNode* paramShape , ParamListEllipseNode* paramListEllipse) {
	LogDebug("\tParamListEllipseAddParamShapeAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = EL_SHAPE_ELLIPSE_LIST;
	paramListEllipseNode->ParamListEllipseNode = paramListEllipse;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = paramShape;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamListEllipseAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListEllipseAddParamShapeAndEndAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = SHAPE;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = paramShape;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamListEllipseAddParamEllipseAction(ParamEllipseNode* paramEllipse, ParamListEllipseNode*  paramListEllipse) {
	LogDebug("\tParamListEllipseAddParamEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = EL_ELLIPSE_ELLIPSE_LIST;
	paramListEllipseNode->ParamListEllipseNode = paramListEllipse;
	paramListEllipseNode->paramEllipseNode = paramEllipse;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamListEllipseAddParamEllipseAndEndAction(ParamEllipseNode* paramEllipse) {
	LogDebug("\tParamListEllipseAddParamEllipseAndEndAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = EL_ELLIPSE;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = paramEllipse;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}

ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, int xAxis, int yAxis) {
	LogDebug("\tParamEllipseAction");

	ParamEllipseNode * paramEllipseNode = (ParamEllipseNode*)calloc(1,sizeof(ParamEllipseNode));

	paramEllipseNode->type = type;
	paramEllipseNode->x_axis = xAxis;
	paramEllipseNode->y_axis = yAxis;

	return paramEllipseNode;
}

ParamListTriangleNode* ParamListTriangleEmptyAction() {
	LogDebug("\tParamListTriangleEmptyAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = EMPTY_TRIANGLE_LIST;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamListTriangleAddParamShapeAction(ParamShapeNode* paramShape , ParamListTriangleNode* paramListTriangle) {
	LogDebug("\tParamListTriangleAddParamShapeAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = SHAPE_TRIANGLE_LIST;
	paramListTriangleNode->ParamListTriangleNode = paramListTriangle;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = paramShape;

	return paramListTriangleNode;

}

ParamListTriangleNode* ParamListTriangleAddParamShapeAndEndAction(ParamShapeNode* paramShape) {
	LogDebug("\tParamListTriangleAddParamShapeAndEndAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = SHAPE;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = paramShape;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamListTriangleAddParamTriangleAction(ParamTriangleNode* paramTriangle, ParamListTriangleNode*  paramListTriangle) {
	LogDebug("\tParamListTriangleAddParamTriangleAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = TRIANGLE_TRIANGLE_LIST;
	paramListTriangleNode->ParamListTriangleNode = paramListTriangle;
	paramListTriangleNode->paramTriangleNode = paramTriangle;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamListTriangleAddParamTriangleAndEndAction(ParamTriangleNode* paramTriangle) {
	LogDebug("\tParamListTriangleAddParamTriangleAndEndAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = TRIANGLE;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = paramTriangle;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}

ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, int base, int height) {
	LogDebug("\tParamTriangleAction");

	ParamTriangleNode * paramTriangleNode = (ParamTriangleNode*)calloc(1,sizeof(ParamTriangleNode));

	paramTriangleNode->type = type;
	paramTriangleNode->height = height;
	paramTriangleNode->base = base;

	return paramTriangleNode;
}

/* Image actions*/

ParamListImageNode * ParamListImageMultipleAction(ParamImageNode * paramImageNode, ParamListImageNode * paramListImageNode) {
	LogDebug("\tParamListImageMultipleAction");

	ParamListImageNode * paramListImageNode = (ParamListImageNode*)calloc(1,sizeof(ParamListImageNode));
	paramListImageNode->paramImageNode=paramImageNode;
	paramListImageNode->paramListImageNode = paramListImageNode;

	return paramListImageNode;
}

ParamListImageNode * ParamListImageAction(ParamImageNode * paramImageNode) {
	LogDebug("\tParamListImageAction");

	ParamListImageNode * paramListImageNode = (ParamListImageNode*)calloc(1,sizeof(ParamListImageNode));
	paramListImageNode->paramImageNode=paramImageNode;
	paramListImageNode->paramListImageNode = NULL;

	return paramListImageNode;
}

ParamImageNode * ParamImageAction(char * typeUrl) {
	LogDebug("\t ParamImageAction");

	ParamImageNode * paramImageNode = (ParamImageNode*)calloc(1,sizeof(ParamImageNode));
	paramImageNode->typeUrl = typeUrl;

	return paramImageNode;
}

/* Text parameters actions */
ParamListTextNode * ParamListTextMultipleAction(ParamTextNode * paramTextNode, ParamListTextNode * paramListTextNode) {
	LogDebug("\t ParamListTextMultipleAction");

	ParamListTextNode * paramListTextNode = (ParamListTextNode*)calloc(1,sizeof(ParamListTextNode));
	paramListTextNode->paramTextNode = paramTextNode;
	paramListTextNode->paramListTextNode = paramListTextNode;

	return paramListTextNode;
}

ParamListTextNode * ParamListTextAction(ParamTextNode * paramTextNode){
	LogDebug("\t ParamListTextAction");

	ParamListTextNode * paramListTextNode = (ParamListTextNode*) calloc(1,sizeof(ParamListTextNode));
	paramListTextNode->paramTextNode = paramTextNode;
	paramListTextNode->paramListTextNode = NULL;

	return paramListTextNode;
}

ParamTextNode * ParamTextAction(ParamTextType type, int fontWidth, fontfamily_t fontFamily, int fontWeight, fontstyle_t fontStyle, textdeco_t textDeco, ParamTypeColorNode * paramTypeColorNode) {
	LogDebug("\t ParamTextAction");

	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = type;
	paramTextNode->fontWidth = fontWidth;
	paramTextNode->fontFamily = fontFamily;
	paramTextNode->fontWeight = fontWeight;
	paramTextNode->fontStyle = fontStyle;
	paramTextNode->textDecoration = textDeco;
	paramTextNode->paramTypeColorNode = paramTypeColorNode;

	return paramTextNode;
}

/* Data types actions*/
ParamTypeColorNode * ParamTypeColorAction(char * typeColor){
	ParamTypeColorNode * paramTypeColorNode = (ParamTypeColorNode*)calloc(1,sizeof(ParamTypeColorNode));
	paramTypeColorNode->typeColor = typeColor;
	return paramTypeColorNode;
}

ParamFloatNode * ParamTypeFloatMultipleAction(float floating, ParamFloatNode * paramFloatNode){
	ParamFloatNode * paramFloatNode = (ParamFloatNode*)calloc(1,sizeof(ParamFloatNode));
	paramFloatNode->floating = floating;
	paramFloatNode->paramFloatNode = paramFloatNode;
}

ParamFloatNode * ParamTypeFloatAction(float floating){
	ParamFloatNode * paramFloatNode = (ParamFloatNode*)calloc(1,sizeof(ParamFloatNode));
	paramFloatNode->floating = floating;
	paramFloatNode->paramFloatNode = NULL;
}
