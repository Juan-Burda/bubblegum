#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../frontend/data-types.h"

/**
 * In order to standarize enum names we follow the following pattern
 * <TYPE>_<DISTINGUISHING_LETTERS_OF_SUBTYPE>_<NAME>
 * where:
 * 	- <TYPE> can have the following prefixes:
 * 		- PL: Param list
 * 		- P: Param
 * 	and is followed by: 
 * 		- A: animation
 * 		- S: shape
 * 		- V: vector
 * 	accordingly
 * - <DISTINGUISHING_LETTERS_OF_SUBTYPE> contains the number of letters necesarry to identify
 * said subtype from its peers in the same type. For example, we have many animation parameters
 * starting with R, so we do this:
 * 		- Rotate -> R
 * 		- Resize -> RE
 * 		- Recolor -> REC
 * to distinguish them. Note that as rotate is the first one we can use R, i.e. it dependes on the
 * order they are declared.
*/

/**
* Se realiza este tipo de definiciones cuando el tipo de dato debe
* auto-referenciarse, como es el caso de una "Expression", que está compuesta
* de otras 2 expresiones.
*/
typedef struct ParamListTranslateNode ParamListTranslateNode;
typedef struct ParamListOpacityNode ParamListOpacityNode;
typedef struct ParamListRotateNode ParamListRotateNode;
typedef struct ParamListResizeNode ParamListResizeNode;
typedef struct ParamListMorphNode ParamListMorphNode;
typedef struct ParamListRecolorNode ParamListRecolorNode;

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

typedef enum {
	ATL_EMPTY,
	ATL_ANIMATION,
	ATL_TRANSLATE
} ParamListTranslateType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamTranslateNode * translateNode;
} ParamListTranslateUnion;
struct ParamListTranslateNode{
	ParamListTranslateType type;
	ParamListTranslateNode * listNode;
	ParamListTranslateUnion value;
};

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

typedef enum {
	AOL_EMPTY,
	AOL_ANIMATION,
	AOL_OPACITY
} ParamListOpacityType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamOpacityNode * opacityNode;
} ParamListOpacityUnion;
struct ParamListOpacityNode{
	ParamListOpacityType type;
	ParamListOpacityNode * listNode;
	ParamListOpacityUnion value;
};

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

typedef enum {
	ARL_EMPTY,
	ARL_ANIMATION,
	ARL_ROTATE
} ParamListRotateType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamRotateNode * rotateNode;
} ParamListRotateUnion;
struct ParamListRotateNode{
	ParamListRotateType type;
	ParamListRotateNode * listNode;
	ParamListRotateUnion value;
};

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

typedef enum {
	ARZL_EMPTY,
	ARZL_ANIMATION,
	ARZL_RESIZE
} ParamListResizeType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamResizeNode * resizeNode;
} ParamListResizeUnion;
struct ParamListResizeNode{
	ParamListResizeType type;
	ParamListResizeNode * listNode;
	ParamListResizeUnion value;
};

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

typedef enum {
	AML_EMPTY,
	AML_ANIMATION,
	AML_MORPH
} ParamListMorphType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamMorphNode * morphNode;
} ParamListMorphUnion;
struct ParamListMorphNode{
	ParamListMorphType type;
	ParamListMorphNode * listNode;
	ParamListMorphUnion value;
};

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

typedef enum {
	ARCL_EMPTY,
	ARCL_ANIMATION,
	ARCL_RECOLOR
} ParamListRecolorType;
typedef union {
	ParamAnimationNode * animationNode;
	ParamRecolorNode * morphNode;
} ParamListRecolorUnion;
struct ParamListRecolorNode{
	ParamListRecolorType type;
	ParamListRecolorNode * listNode;
	ParamListRecolorUnion value;
};

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
	RL_SHAPE,
	RL_RECTANGLE
} ParamListRectangleType;
typedef union {
	ParamShapeNode * shapeNode;
	ParamRectangleNode * rectangleNode;
} ParamListRectangleUnion;
struct ParamListRectangleNode{
	ParamListRectangleType type;
	ParamListRectangleNode * listNode;
	ParamListRectangleUnion value;
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
	EL_SHAPE,
	EL_ELLIPSE
} ParamListEllipseType;
typedef union {
	ParamShapeNode * shapeNode;
	ParamEllipseNode * ellipseNode;
} ParamListEllipseUnion;
struct ParamListEllipseNode{
	ParamListEllipseType type;
	ParamListEllipseNode * listNode;
	ParamListEllipseUnion value;
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
	TL_SHAPE,
	TL_TRIANGLE
} ParamListTriangleType;
typedef union {
	ParamShapeNode * shapeNode;
	ParamTriangleNode * triangleNode;
} ParamListTriangleUnion;
struct ParamListTriangleNode{
	ParamListTriangleType type;
	ParamListTriangleNode * listNode;
	ParamListTriangleUnion value;
};

/* Vector nodes */
// Images
typedef struct {
	char * typeUrl;
} ParamImageNode;

struct ParamListImageNode {
	ParamImageNode * paramImageNode;
	ParamListImageNode * listNode;
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
	ParamListTextNode * listNode;
};

#endif
