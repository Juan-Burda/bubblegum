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

ParamListRectangleNode* EmptyParamListRectangleAction(){

	LogDebug("\tEmptyParamListRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = EMPTY;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamListRectangleNode* ParamShapeParamListRectangleAction(ParamShapeNode* paramShape , ParamListRectangleNode* paramListRectangle){
	
	LogDebug("\tParamShapeParamListRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = SHAPE_RECTANGLE_LIST;
	paramListRectangleNode->ParamListRectangleNode = paramListRectangle;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = paramShape;

	return paramListRectangleNode;

}

ParamListRectangleNode* ParamShapeRectangleAction(ParamShapeNode* paramShape){
	LogDebug("\tParamShapeParamListRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = SHAPE;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode = NULL;
	paramListRectangleNode->ParamShapeNode = paramShape;

	return paramListRectangleNode;
}

ParamListRectangleNode * ParamRectangleParamListRectangleAction(ParamRectangleNode* paramRectangle, ParamListRectangleNode*  paramListRectangle){
	
	LogDebug("\tParamShapeParamListRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RECTANGLE_RECTANGLE_LIST;
	paramListRectangleNode->ParamListRectangleNode = paramListRectangle;
	paramListRectangleNode->paramRectangleNode =paramRectangle;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamListRectangleNode * ParamRectangleAction(ParamRectangleNode* paramRectangle){
		LogDebug("\tParamShapeParamListRectangleAction");

	ParamListRectangleNode * paramListRectangleNode = 
	(ParamListRectangleNode*)calloc(1,sizeof(ParamListRectangleNode));

	paramListRectangleNode->paramListRectangleType = RECTANGLE;
	paramListRectangleNode->ParamListRectangleNode = NULL;
	paramListRectangleNode->paramRectangleNode =paramRectangle;
	paramListRectangleNode->ParamShapeNode = NULL;

	return paramListRectangleNode;
}

ParamListEllipseNode* EmptyParamListEllipseAction(){

	LogDebug("\tEmptyParamListEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = EMPTY;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamShapeParamListEllipseAction(ParamShapeNode* paramShape , ParamListEllipseNode* paramListEllipse){
	
	LogDebug("\tParamShapeParamListEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = SHAPE_ELLIPSE_LIST;
	paramListEllipseNode->ParamListEllipseNode = paramListEllipse;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = paramShape;

	return paramListEllipseNode;

}

ParamListEllipseNode* ParamShapeEllipseAction(ParamShapeNode* paramShape){
	LogDebug("\tParamShapeParamListEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = SHAPE;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = NULL;
	paramListEllipseNode->ParamShapeNode = paramShape;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamEllipseParamListEllipseAction(ParamEllipseNode* paramEllipse, ParamListEllipseNode*  paramListEllipse){
	
	LogDebug("\tParamShapeParamListEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = ELLIPSE_ELLIPSE_LIST;
	paramListEllipseNode->ParamListEllipseNode = paramListEllipse;
	paramListEllipseNode->paramEllipseNode = paramEllipse;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}

ParamListEllipseNode* ParamEllipseAction(ParamEllipseNode* paramEllipse){
		LogDebug("\tParamShapeParamListEllipseAction");

	ParamListEllipseNode * paramListEllipseNode = 
	(ParamListEllipseNode*)calloc(1,sizeof(ParamListEllipseNode));

	paramListEllipseNode->paramListEllipseType = ELLIPSE;
	paramListEllipseNode->ParamListEllipseNode = NULL;
	paramListEllipseNode->paramEllipseNode = paramEllipse;
	paramListEllipseNode->ParamShapeNode = NULL;

	return paramListEllipseNode;
}


ParamListTriangleNode* EmptyParamListTriangleAction(){

	LogDebug("\tEmptyParamListEllipseAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = EMPTY;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamShapeParamListTriangleAction(ParamShapeNode* paramShape , ParamListTriangleNode* paramListTriangle){
	
	LogDebug("\tParamShapeParamListTriangleAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = SHAPE_TRIANGLE_LIST;
	paramListTriangleNode->ParamListTriangleNode = paramListTriangle;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = paramShape;

	return paramListTriangleNode;

}

ParamListTriangleNode* ParamShapeTriangleAction(ParamShapeNode* paramShape){
	LogDebug("\tParamShapeParamListTriangleAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = SHAPE;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = NULL;
	paramListTriangleNode->ParamShapeNode = paramShape;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamTriangleParamListTriangleAction(ParamTriangleNode* paramTriangle, ParamListTriangleNode*  paramListTriangle){
	
	LogDebug("\tParamShapeParamListTriangleAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = TRIANGLE_TRIANGLE_LIST;
	paramListTriangleNode->ParamListTriangleNode = paramListTriangle;
	paramListTriangleNode->paramTriangleNode = paramTriangle;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}

ParamListTriangleNode* ParamTriangleAction(ParamTriangleNode* paramTriangle){
		LogDebug("\tParamShapeParamListTriangleAction");

	ParamListTriangleNode * paramListTriangleNode = 
	(ParamListTriangleNode*)calloc(1,sizeof(ParamListTriangleNode));

	paramListTriangleNode->paramListTriangleType = TRIANGLE;
	paramListTriangleNode->ParamListTriangleNode = NULL;
	paramListTriangleNode->paramTriangleNode = paramTriangle;
	paramListTriangleNode->ParamShapeNode = NULL;

	return paramListTriangleNode;
}


ParamRectangleNode * HeightParamRectangleAction(int height){
	
	LogDebug("\tHeightParamRectangleAction");

	ParamRectangleNode * paramRectangleNode = 
	(ParamRectangleNode*)calloc(1,sizeof(ParamRectangleNode));

	paramRectangleNode->height = height;
	paramRectangleNode->width = 0;

	return paramRectangleNode;
}

ParamRectangleNode * WidthParamRectangleAction(int width){
	
	LogDebug("\tHeightParamRectangleAction");

	ParamRectangleNode * paramRectangleNode = 
	(ParamRectangleNode*)calloc(1,sizeof(ParamRectangleNode));

	paramRectangleNode->height = 0;
	paramRectangleNode->width = width;

	return paramRectangleNode;
}

ParamEllipseNode * XAxisParamEllipseAction(int xaxis){
	
	LogDebug("\tXAxisParamEllipseAction");

	ParamEllipseNode * paramEllipseNode = 
	(ParamEllipseNode*)calloc(1,sizeof(ParamEllipseNode));

	paramEllipseNode->x_axis = xaxis;
	paramEllipseNode->y_axis = 0;

	return paramEllipseNode;
}

ParamEllipseNode * YAxisParamEllipseAction(int yaxis){
		
	LogDebug("\tYAxisParamEllipseAction");

	ParamEllipseNode * paramEllipseNode = 
	(ParamEllipseNode*)calloc(1,sizeof(ParamEllipseNode));

	paramEllipseNode->x_axis = 0;
	paramEllipseNode->y_axis = yaxis;

	return paramEllipseNode;
} 

ParamTriangleNode * HeightParamTriangleAction(int height){

	LogDebug("\tHeightParamTriangleAction");

	ParamTriangleNode * paramTriangleNode = 
	(ParamTriangleNode*)calloc(1,sizeof(ParamTriangleNode));

	paramTriangleNode->height = height;
	paramTriangleNode->base = 0;

	return paramTriangleNode;
}

ParamTriangleNode * BaseParamTriangleAction(int base){

	LogDebug("\tBaseParamTriangleAction");

	ParamTriangleNode * paramTriangleNode = 
	(ParamTriangleNode*)calloc(1,sizeof(ParamTriangleNode));

	paramTriangleNode->height = 0;
	paramTriangleNode->base = base;

	return paramTriangleNode;
}

ParamShapeNode * FillColorParamShapeAction(TypeColorNode * fillColor){
	
	LogDebug("\tFillColorParamShapeAction");

	ParamShapeNode * paramShapeNode = 
	(ParamShapeNode*)calloc(1,sizeof(ParamShapeNode));

	paramShapeNode->ParamShapeType = FILL_COLOR;
	paramShapeNode->fillColor = fillColor;
	paramShapeNode->borderColor = NULL;
	paramShapeNode->borderWith = 0;
	paramShapeNode->fillColor = 0;

	return paramShapeNode;
}

ParamShapeNode * BorderColorParamShapeAction(TypeColorNode * borderColor){
	
	LogDebug("\tBorderColorParamShapeAction");

	ParamShapeNode * paramShapeNode = 
	(ParamShapeNode*)calloc(1,sizeof(ParamShapeNode));

	paramShapeNode->ParamShapeType = BORDER_COLOR;
	paramShapeNode->fillColor = NULL;
	paramShapeNode->borderColor = borderColor;
	paramShapeNode->borderWith = 0;
	paramShapeNode->fillColor = 0;

	return paramShapeNode;
}

ParamShapeNode * BorderWidthParamShapeAction(int width){
	
	LogDebug("\tBorderWidthParamShapeAction");

	ParamShapeNode * paramShapeNode = 
	(ParamShapeNode*)calloc(1,sizeof(ParamShapeNode));

	paramShapeNode->ParamShapeType = FILL_COLOR;
	paramShapeNode->fillColor = NULL;
	paramShapeNode->borderColor = NULL;
	paramShapeNode->borderWith = width;
	paramShapeNode->fillColor = 0;

	return paramShapeNode;
}

ParamShapeNode * RotationParamShapeAction(int rotation){
	
	LogDebug("\tRotationParamShapeAction");

	ParamShapeNode * paramShapeNode = 
	(ParamShapeNode*)calloc(1,sizeof(ParamShapeNode));

	paramShapeNode->ParamShapeType = FILL_COLOR;
	paramShapeNode->fillColor = NULL;
	paramShapeNode->borderColor = NULL;
	paramShapeNode->borderWith = 0;
	paramShapeNode->fillColor = rotation;

	return paramShapeNode;
}

/* Image actions*/

ParamListImageNode * ParamListImageMultipleAction(ParamImageNode * paramImageNode, 
    ParamListImageNode * paramListImageNode){
	ParamListImageNode * paramListImageNode = (ParamListImageNode*)calloc(1,sizeof(ParamListImageNode));
	paramListImageNode->paramImageNode=paramImageNode;
	paramListImageNode->paramListImageNode = paramListImageNode;
	return paramListImageNode;
}

ParamListImageNode * ParamListImageAction(ParamImageNode * paramImageNode){
	ParamListImageNode * paramListImageNode = (ParamListImageNode*)calloc(1,sizeof(ParamListImageNode));
	paramListImageNode->paramImageNode=paramImageNode;
	paramListImageNode->paramListImageNode = NULL;
	return paramListImageNode;
}

ParamImageNode * ParamImageAction(char * typeUrl){
	ParamImageNode * paramImageNode = (ParamImageNode*)calloc(1,sizeof(ParamImageNode));
	paramImageNode->typeUrl = typeUrl;
	return paramImageNode;
}

/* Text parameters actions */

ParamListTextNode * ParamListTextMultipleAction(ParamTextNode * paramTextNode, 
	ParamListTextNode * paramListTextNode){
	ParamListTextNode * paramListTextNode = (ParamListTextNode*)calloc(1,sizeof(ParamListTextNode));
	paramListTextNode->paramTextNode = paramTextNode;
	paramListTextNode->paramListTextNode = paramListTextNode;
}
ParamListTextNode * ParamListTextAction(ParamTextNode * paramTextNode){
	ParamListTextNode * paramListTextNode = (ParamListTextNode*)calloc(1,sizeof(ParamListTextNode));
	paramListTextNode->paramTextNode = paramTextNode;
	paramListTextNode->paramListTextNode = NULL;
}

ParamTextNode * ParamFontWidthAction(int fontWidth){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = FONT_WIDTH;
	paramTextNode->fontWidth = fontWidth;
	paramTextNode->fontFamily = NULL;
	paramTextNode->fontWeight = NULL;
	paramTextNode->fontStyle = NULL;
	paramTextNode->textDecoration = NULL;
	paramTextNode->paramTypeColorNode = NULL;
	return paramTextNode;
}

ParamTextNode * ParamFontFamilyAction(fontfamily_t fontFamily){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = FONT_FAMILY;
	paramTextNode->fontWidth = NULL;
	paramTextNode->fontFamily = fontFamily;
	paramTextNode->fontWeight = NULL;
	paramTextNode->fontStyle = NULL;
	paramTextNode->textDecoration = NULL;
	paramTextNode->paramTypeColorNode = NULL;
	return paramTextNode;
}

ParamTextNode * ParamFontWeightAction(int fontWeight){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = FONT_WEIGHT;
	paramTextNode->fontWidth = NULL;
	paramTextNode->fontFamily = NULL;
	paramTextNode->fontWeight = fontWeight;
	paramTextNode->fontStyle = NULL;
	paramTextNode->textDecoration = NULL;
	paramTextNode->paramTypeColorNode = NULL;
	return paramTextNode;
}

ParamTextNode * ParamFontStyleAction(fontstyle_t fontStyle){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = FONT_STYLE;
	paramTextNode->fontWidth = NULL;
	paramTextNode->fontFamily = NULL;
	paramTextNode->fontWeight = NULL;
	paramTextNode->fontStyle = fontStyle;
	paramTextNode->textDecoration = NULL;
	paramTextNode->paramTypeColorNode = NULL;
	return paramTextNode;
}

ParamTextNode * ParamTextDecorationAction(textdeco_t textDecoration){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = TEXT_DECORATION;
	paramTextNode->fontWidth = NULL;
	paramTextNode->fontFamily = NULL;
	paramTextNode->fontWeight = NULL;
	paramTextNode->fontStyle = NULL;
	paramTextNode->textDecoration = textDecoration;
	paramTextNode->paramTypeColorNode = NULL;
	return paramTextNode;
}

ParamTextNode * ParamBackgroundColorAction(ParamTypeColorNode * paramTypeColorNode){
	ParamTextNode * paramTextNode = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	paramTextNode->type = BACKGROUND_COLOR;
	paramTextNode->fontWidth = NULL;
	paramTextNode->fontFamily = NULL;
	paramTextNode->fontWeight = NULL;
	paramTextNode->fontStyle = NULL;
	paramTextNode->textDecoration = NULL;
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
