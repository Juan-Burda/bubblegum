#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

//TO-DO: check if this is correct
#include "../data-types.h"

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct Expression Expression;
typedef struct ParamListShapeNode ParamListShapeNode;
typedef struct ParamListRectangleNode ParamListRectangleNode;
typedef struct ParamListEllipseNode ParamListEllipseNode;
typedef struct ParamListTriangleNode ParamListTriangleNode; 

/**
* Para cada no-terminal se define una nueva estructura que representa su tipo
* de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
*/
typedef struct {
	int value;
} Constant;

/**
* En caso de que un no-terminal ("Factor" en este caso), posea más de una
* regla de producción asociada, se crea además de la estructura un enumerado
* que identitifque cada reducción posible (cada regla de producción). Luego,
* se agrega una instancia de este enumerado dentro del nodo del no-terminal.
*
* De este modo, al recorrer el AST, es posible determinar qué nodos hijos
* posee según el valor de este enumerado.
*/
typedef enum {
	EXPRESSION,
	CONSTANT
} FactorType;

typedef struct {
	FactorType type;
	Expression * expression;
} Factor;

typedef enum {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	FACTOR
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression * leftExpression;
	Expression * rightExpression;
};

typedef struct {
	Expression * expression;
} Program;

typedef struct{
	char * color;
} TypeColorNode;

typedef enum {
	FILL_COLOR,
	BORDER_COLOR,
	BORDER_WITH,
	ROTATION
} ParamShapeType;

typedef struct {
	ParamShapeType ParamShapeType;
	TypeColorNode * fillColor;
	TypeColorNode * borderColor;
	int borderWith;
	int rotation;
} ParamShapeNode;

typedef enum{
	EMPTY,
	SHAPE,
	RECTANGLE,
	SHAPE_RECTANGLE_LIST,
	RECTANGLE_RECTANGLE_LIST
} ParamListRectangleType;

typedef struct{
	int height;
	int width;
} ParamRectangleNode;

struct ParamListRectangleNode{
	ParamListRectangleType paramListRectangleType;
	ParamListRectangleNode * ParamListRectangleNode;
	ParamShapeNode * ParamShapeNode;
	ParamRectangleNode * paramRectangleNode;
};

typedef enum{
	EMPTY,
	SHAPE,
	ELLIPSE,
	SHAPE_ELLIPSE_LIST,
	ELLIPSE_ELLIPSE_LIST
} ParamListEllipseType;

typedef struct{
	int x_axis;
	int y_axis;
} ParamEllipseNode;

struct ParamListEllipseNode{
	ParamListEllipseType paramListEllipseType;
	ParamListEllipseNode * ParamListEllipseNode;
	ParamShapeNode * ParamShapeNode;
	ParamEllipseNode * paramEllipseNode;
};

typedef enum{
	EMPTY,
	SHAPE,
	TRIANGLE,
	SHAPE_TRIANGLE_LIST,
	TRIANGLE_TRIANGLE_LIST
} ParamListTriangleType;

typedef struct{
	int height;
	int base;
} ParamTriangleNode;

struct ParamListTriangleNode{
	ParamListTriangleType paramListTriangleType;
	ParamListTriangleNode * ParamListTriangleNode;
	ParamShapeNode * ParamShapeNode;
	ParamTriangleNode * paramTriangleNode;
};

/* Image node */

typedef struct{
	char * typeUrl
} ParamImageNode;

typedef struct{
	ParamImageNode * paramImageNode;
	ParamListImageNode * paramListImageNode;
} ParamListImageNode;

/* Text parameters nodes */

typedef enum {
	FONT_WIDTH,
	FONT_FAMILY,
	FONT_WEIGHT,
	FONT_STYLE,
	TEXT_DECORATION,
	BACKGROUND_COLOR
} ParamTextType; 

typedef struct{
	ParamTextType type;
	int fontWidth;
	fontfamily_t fontFamily;
	int fontWeight;
	fontstyle_t fontStyle;
	textdeco_t textDecoration;
	ParamTypeColorNode * paramTypeColorNode;
} ParamTextNode;

typedef struct {
	ParamTextNode * paramTextNode;
	ParamListTextNode * paramListTextNode;
} ParamListTextNode;

/* Data type nodes */

typedef struct {
	char * typeColor;
} ParamTypeColorNode;

typedef struct {
	float floating;
	ParamFloatNode paramFloatNode;
} ParamFloatNode;

#endif
