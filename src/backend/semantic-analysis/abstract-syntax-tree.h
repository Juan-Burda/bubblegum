#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

//TO-DO: check if this is correct
#include "../../frontend/data-types.h"

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct ParamListShapeNode ParamListShapeNode;
typedef struct ParamListRectangleNode ParamListRectangleNode;
typedef struct ParamListEllipseNode ParamListEllipseNode;
typedef struct ParamListTriangleNode ParamListTriangleNode; 

typedef struct ParamListImageNode ParamListImageNode; 
typedef struct ParamListTextNode ParamListTextNode; 
typedef struct ParamTypePointsNode ParamTypePointsNode; 

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
typedef struct {
	int changeme;
} Program;

/** Parameters */
/* Data type nodes */
typedef struct {
	char * typeColor;
} ParamTypeColorNode;

struct ParamTypePointsNode {
	float floating;
	ParamTypePointsNode * nextPoint;
};

/* Animation nodes */
// Animation
typedef union {
	boolean_t alternate;
	boolean_t loop;
	int duration;
	int delay;
} ParamAnimationUnion;

typedef enum {
	ALTERNATE,
	LOOP,
	DURATION,
	DELAY
} ParamAnimationType;
typedef struct {
	ParamAnimationType type;
	ParamAnimationUnion value;
} ParamAnimationNode;

// Translate
typedef union {
	int endValue;
} ParamTranslateUnion;

typedef enum {
	END_VALUE
} ParamTranslateType;
typedef struct {
	ParamTranslateType type;
	ParamTranslateUnion value;
} ParamTranslateNode;

// Opacity
typedef union {
	float alpha;
} ParamOpacityUnion;

typedef enum {
	ALPHA
} ParamOpacityType;
typedef struct {
	ParamOpacityType type;
	ParamOpacityUnion value;
} ParamOpacityNode;

// Rotate
typedef union {
	int angle;
} ParamRotateUnion;

typedef enum {
	ANGLE
} ParamRotateType;
typedef struct {
	ParamRotateType type;
	ParamRotateUnion value;
} ParamRotateNode;

// Resize
typedef union {
	float scale;
} ParamResizeUnion;

typedef enum {
	SCALE
} ParamResizeType;
typedef struct {
	ParamResizeType type;
	ParamResizeUnion value;
} ParamResizeNode;

// Morph
typedef union {
	ParamTypePointsNode * points;
} ParamMorphUnion;

typedef enum {
	POINT
} ParamMorphType;
typedef struct {
	ParamMorphType type;
	ParamMorphUnion value;
} ParamMorphNode;

// Recolor
typedef union {
	ParamTypeColorNode * endColor;
} ParamRecolorUnion;

typedef enum {
	END_COLOR
} ParamRecolorType;
typedef struct {
	ParamRecolorType type;
	ParamRecolorUnion value;
} ParamRecolorNode;

/* Shape nodes */ 
// Shape
typedef union {
	ParamTypeColorNode * fillColor;
	ParamTypeColorNode * borderColor;
	int borderWidth;
	int rotation;
} ParamShapeUnion;

typedef enum {
	FILL_COLOR,
	BORDER_COLOR,
	BORDER_WIDTH,
	ROTATION
} ParamShapeType;
typedef struct {
	ParamShapeType type;
	ParamShapeUnion value;
} ParamShapeNode;

// Rectangle
typedef union {
	int height;
	int width;
} ParamRectangleUnion;

typedef enum {
	RT_HEIGHT,	// rectangle type height
	RT_WIDTH	// rectangle type width
} ParamRectangleType;
typedef struct {
	ParamRectangleType type;
	ParamRectangleUnion value;
} ParamRectangleNode;

typedef enum {
	RL_EMPTY,
	RL_SHAPE_LIST,
	RL_SHAPE,
	RL_RECTANGLE_LIST,
	RL_RECTANGLE
} ParamListRectangleType;
struct ParamListRectangleNode{
	ParamListRectangleType paramListRectangleType;
	ParamListRectangleNode * ParamListRectangleNode;
	ParamShapeNode * ParamShapeNode;
	ParamRectangleNode * paramRectangleNode;
};

// Ellipse
typedef union {
	int xAxis;
	int yAxis;
} ParamEllipseUnion;

typedef enum {
	ET_X_AXIS,	// ellipse type x-axis
	ET_Y_AXIS	// ellipse type y-axis
} ParamEllipseType;
typedef struct {
	ParamEllipseType type;
	ParamEllipseUnion value;
} ParamEllipseNode;

typedef enum {
	EL_EMPTY,
	EL_SHAPE_LIST,
	EL_SHAPE,
	EL_ELLIPSE_LIST,
	EL_ELLIPSE
} ParamListEllipseType;
struct ParamListEllipseNode{
	ParamListEllipseType paramListEllipseType;
	ParamListEllipseNode * ParamListEllipseNode;
	ParamShapeNode * ParamShapeNode;
	ParamEllipseNode * paramEllipseNode;
};

// Triangle
typedef union {
	int height;
	int base;
} ParamTriangleUnion;

typedef enum {
	TT_HEIGHT,	// triangle type height
	TT_BASE		// triangle type base
} ParamTriangleType;
typedef struct{
	ParamTriangleType type;
	ParamTriangleUnion value;
} ParamTriangleNode;

typedef enum{
	TL_EMPTY,
	TL_SHAPE_LIST,
	TL_SHAPE,
	TL_TRIANGLE_LIST,
	TL_TRIANGLE
} ParamListTriangleType;
struct ParamListTriangleNode{
	ParamListTriangleType paramListTriangleType;
	ParamListTriangleNode * ParamListTriangleNode;
	ParamShapeNode * ParamShapeNode;
	ParamTriangleNode * paramTriangleNode;
};

/* Vector nodes */
// Images
typedef struct {
	char * typeUrl;
} ParamImageNode;

struct ParamListImageNode {
	ParamImageNode * paramImageNode;
	ParamListImageNode * paramListImageNode;
};

// Text
typedef union {
	int fontWidth;
	fontfamily_t fontFamily;
	int fontWeight;
	fontstyle_t fontStyle;
	textdeco_t textDecoration;
	ParamTypeColorNode * paramTypeColorNode;
} ParamTextUnion;

typedef enum {
	FONT_WIDTH,
	FONT_FAMILY,
	FONT_WEIGHT,
	FONT_STYLE,
	TEXT_DECORATION,
	BACKGROUND_COLOR
} ParamTextType; 
typedef struct {
	ParamTextType type;
	ParamTextUnion value;
} ParamTextNode;

struct ParamListTextNode {
	ParamTextNode * paramTextNode;
	ParamListTextNode * paramListTextNode;
};

#endif
