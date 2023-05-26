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

/** Parameters */
/**
 * For parameters we always have the same pattern:
 * 	- We need to save a certain parameter's value -> this is done in Param<sth>Node
 * 	- We need to add a new paramter -> this is done in ParamList<sth>Node
*/
/* Animation */
ParamAnimationNode * ParamAnimationAction(ParamAnimationType type, ParamAnimationUnion value) {
	LogDebug("\tParamAnimationAction");

	ParamAnimationNode * result = (ParamAnimationNode*) calloc(1, sizeof(ParamAnimationNode));
	result->type = type;
	result->value = value;

	return result;
}

// For translate
ParamListTranslateNode * ParamListTranslateAddParamAction(ParamListTranslateType type, ParamListTranslateNode* listNode, ParamListTranslateUnion value) {
	LogDebug("\tParamListTranslateAddParamAction");

	ParamListTranslateNode * result = (ParamListTranslateNode*) calloc(1, sizeof(ParamListTranslateNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamTranslateNode * ParamTranslateAction(ParamTranslateType type, ParamTranslateUnion value) {
	LogDebug("\tParamTranslateAction");

	ParamTranslateNode * result = (ParamTranslateNode*) calloc(1, sizeof(ParamTranslateNode));
	result->type = type;
	result->value = value;

	return result;
}

// For opacity
ParamListOpacityNode * ParamListOpacityAddParamAction(ParamListOpacityType type, ParamListOpacityNode* listNode, ParamListOpacityUnion value) {
	LogDebug("\tParamListOpacityAddParamAction");

	ParamListOpacityNode * result = (ParamListOpacityNode*) calloc(1, sizeof(ParamListOpacityNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamOpacityNode * ParamOpacityAction(ParamOpacityType type, ParamOpacityUnion value) {
	LogDebug("\tParamOpacityAction");

	ParamOpacityNode * result = (ParamOpacityNode*) calloc(1, sizeof(ParamOpacityNode));
	result->type = type;
	result->value = value;

	return result;
}

// For rotate
ParamListRotateNode * ParamListRotateAddParamAction(ParamListRotateType type, ParamListRotateNode* listNode, ParamListRotateUnion value) {
	LogDebug("\tParamListRotateAddParamAction");

	ParamListRotateNode * result = (ParamListRotateNode*) calloc(1, sizeof(ParamListRotateNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamRotateNode * ParamRotateAction(ParamRotateType type, ParamRotateUnion value) {
	LogDebug("\tParamRotateAction");

	ParamRotateNode * result = (ParamRotateNode*) calloc(1, sizeof(ParamRotateNode));
	result->type = type;
	result->value = value;

	return result;
}

// For resize
ParamListResizeNode * ParamListResizeAddParamAction(ParamListResizeType type, ParamListResizeNode* listNode, ParamListResizeUnion value) {
	LogDebug("\tParamListResizeAddParamAction");

	ParamListResizeNode * result = (ParamListResizeNode*) calloc(1, sizeof(ParamListResizeNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamResizeNode * ParamResizeAction(ParamResizeType type, ParamResizeUnion value) {
	LogDebug("\tParamResizeAction");

	ParamResizeNode * result = (ParamResizeNode*) calloc(1, sizeof(ParamResizeNode));
	result->type = type;
	result->value = value;

	return result;
}

// For morph
ParamListMorphNode * ParamListMorphAddParamAction(ParamListMorphType type, ParamListMorphNode* listNode, ParamListMorphUnion value) {
	LogDebug("\tParamListMorphAddParamAction");

	ParamListMorphNode * result = (ParamListMorphNode*) calloc(1, sizeof(ParamListMorphNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamMorphNode * ParamMorphAction(ParamMorphType type, ParamMorphUnion value) {
	LogDebug("\tParamMorphAction");

	ParamMorphNode * result = (ParamMorphNode*) calloc(1, sizeof(ParamMorphNode));
	result->type = type;
	result->value = value;

	return result;
}

// For recolor
ParamListRecolorNode * ParamListRecolorAddParamAction(ParamListRecolorType type, ParamListRecolorNode* listNode, ParamListRecolorUnion value) {
	LogDebug("\tParamListRecolorAddParamAction");

	ParamListRecolorNode * result = (ParamListRecolorNode*) calloc(1, sizeof(ParamListRecolorNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamRecolorNode * ParamRecolorAction(ParamRecolorType type, ParamRecolorUnion value) {
	LogDebug("\tParamRecolorAction");

	ParamRecolorNode * result = (ParamRecolorNode*) calloc(1, sizeof(ParamRecolorNode));
	result->type = type;
	result->value = value;

	return result;
}

/* Shapes */
ParamShapeNode * ParamShapeAction(ParamShapeType type, ParamShapeUnion value) {
	LogDebug("\tParamShapeAction");

	ParamShapeNode * result = (ParamShapeNode*) calloc(1, sizeof(ParamShapeNode));
	result->type = type;
	result->value = value;

	return result;
}

// For rectangles
ParamListRectangleNode * ParamListRectangleAddParamAction(ParamListRectangleType type, ParamListRectangleNode* listNode, ParamListRectangleUnion value) {
	LogDebug("\tParamListRectangleAddParamAction");

	ParamListRectangleNode * result = (ParamListRectangleNode*) calloc(1, sizeof(ParamListRectangleNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamRectangleNode * ParamRectangleAction(ParamRectangleType type, ParamRectangleUnion value) {
	LogDebug("\tParamRectangleAction");

	ParamRectangleNode * result = (ParamRectangleNode*) calloc(1, sizeof(ParamRectangleNode));
	result->type = type;
	result->value = value;

	return result;
}

// For ellipse
ParamListEllipseNode * ParamListEllipseAddParamAction(ParamListEllipseType type, ParamListEllipseNode* listNode, ParamListEllipseUnion value) {
	LogDebug("\tParamListEllipseAddParamAction");

	ParamListEllipseNode * result = (ParamListEllipseNode*) calloc(1, sizeof(ParamListEllipseNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamEllipseNode * ParamEllipseAction(ParamEllipseType type, ParamEllipseUnion value) {
	LogDebug("\tParamEllipseAction");

	ParamEllipseNode * result = (ParamEllipseNode*)calloc(1,sizeof(ParamEllipseNode));
	result->type = type;
	result->value = value;

	return result;
}

// For triangle
ParamListTriangleNode * ParamListTriangleAddParamAction(ParamListTriangleType type, ParamListTriangleNode* listNode, ParamListTriangleUnion value) {
	LogDebug("\tParamListTriangleAddParamShapeAction");

	ParamListTriangleNode * result = (ParamListTriangleNode*) calloc(1, sizeof(ParamListTriangleNode));
	result->type = type;
	result->listNode = listNode;
	result->value = value;

	return result;
}

ParamTriangleNode * ParamTriangleAction(ParamTriangleType type, ParamTriangleUnion value) {
	LogDebug("\tParamTriangleAction");

	ParamTriangleNode * result = (ParamTriangleNode*)calloc(1,sizeof(ParamTriangleNode));

	result->type = type;
	result->value = value;

	return result;
}


/* Vectors */
// For images
ParamListImageNode * ParamListImageAddParamAction(ParamListImageNode * listNode, ParamImageNode * imageNode) {
	LogDebug("\tParamListImageMultipleAction");

	ParamListImageNode * result = (ParamListImageNode *) calloc(1, sizeof(ParamListImageNode));
	result->listNode = listNode;
	result->paramImageNode = imageNode;

	return result;
}

ParamImageNode * ParamImageAction(char * typeUrl) {
	LogDebug("\t ParamImageAction");

	ParamImageNode * result = (ParamImageNode*) calloc(1, sizeof(ParamImageNode));
	result->typeUrl = typeUrl;

	return result;
}

// For text
ParamListTextNode * ParamListTextAddParamAction(ParamListTextNode * listNode, ParamTextNode * textNode) {
	LogDebug("\t ParamListTextMultipleAction");

	ParamListTextNode * result = (ParamListTextNode*)calloc(1,sizeof(ParamListTextNode));
	result->listNode = listNode;
	result->paramTextNode = textNode;

	return result;
}

ParamTextNode * ParamTextAction(ParamTextType type, ParamTextUnion value) {
	LogDebug("\t ParamTextAction");

	ParamTextNode * result = (ParamTextNode*)calloc(1,sizeof(ParamTextNode));
	result->type = type;
	result->value = value;

	return result;
}

/* Data types actions*/
ParamTypeColorNode * ParamTypeColorAction(char * typeColor){
	ParamTypeColorNode * result = (ParamTypeColorNode*) calloc(1, sizeof(ParamTypeColorNode));
	result->typeColor = typeColor;

	return result;
}

ParamTypePointsNode * ParamTypePointsAddPointAction(ParamTypePointsNode * pointsNode, float floating) {
	ParamTypePointsNode * result = (ParamTypePointsNode*) calloc(1, sizeof(ParamTypePointsNode));
	result->nextPoint = pointsNode;
	result->floating = floating;

	return result;
}