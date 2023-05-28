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
 * 		- CS: Compound Statement
 * 		- emtpy: in any other case
 * 	and is followed by the type: 
 * 		- A: animation
 * 		- S: shape
 * 		- V: vector
 * 	accordingly.
 * - <DISTINGUISHING_LETTERS_OF_SUBTYPE> contains the number of letters necesarry to identify 
 * said subtype from its peers in the same type. For example, we have many animation parameters
 * starting with R, so we do this:
 * 		- Rotate -> R
 * 		- Resize -> RE
 * 		- Recolor -> REC
 * to distinguish them. Note that as rotate is the first one we can use R, i.e. it dependes on the
 * order they are declared.
*/

// Self-referencing structs
typedef struct ExpressionNode ExpressionNode;
typedef struct FunctionListNode FunctionListNode;
typedef struct FunctionNode FunctionNode;

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
	ExpressionNode * expression;
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
	PA_A_ALTERNATE,
	PA_A_LOOP,
	PA_A_DURATION,
	PA_A_DELAY
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
	PA_T_END_VALUE
} ParamTranslateType;
typedef struct {
	ParamTranslateType type;
	ParamTranslateUnion value;
} ParamTranslateNode;

typedef enum {
	PLA_T_EMPTY,
	PLA_T_ANIMATION,
	PLA_T_TRANSLATE
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
	PA_O_ALPHA
} ParamOpacityType;
typedef struct {
	ParamOpacityType type;
	ParamOpacityUnion value;
} ParamOpacityNode;

typedef enum {
	PLA_O_EMPTY,
	PLA_O_ANIMATION,
	PLA_O_OPACITY
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
	PA_R_ANGLE
} ParamRotateType;
typedef struct {
	ParamRotateType type;
	ParamRotateUnion value;
} ParamRotateNode;

typedef enum {
	PLA_R_EMPTY,
	PLA_R_ANIMATION,
	PLA_R_ROTATE
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
	PA_RE_SCALE
} ParamResizeType;
typedef struct {
	ParamResizeType type;
	ParamResizeUnion value;
} ParamResizeNode;

typedef enum {
	PLA_RE_EMPTY,
	PLA_RE_ANIMATION,
	PLA_RE_RESIZE
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
	PA_M_POINT
} ParamMorphType;
typedef struct {
	ParamMorphType type;
	ParamMorphUnion value;
} ParamMorphNode;

typedef enum {
	PLA_M_EMPTY,
	PLA_M_ANIMATION,
	PLA_M_MORPH
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
	PA_REC_END_COLOR
} ParamRecolorType;
typedef struct {
	ParamRecolorType type;
	ParamRecolorUnion value;
} ParamRecolorNode;

typedef enum {
	PLA_REC_EMPTY,
	PLA_REC_ANIMATION,
	PLA_REC_RECOLOR
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
	PS_S_FILL_COLOR,
	PS_S_BORDER_COLOR,
	PS_S_BORDER_WIDTH,
	PS_S_ROTATION
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
	PS_R_HEIGHT,	// rectangle type height
	PS_R_WIDTH	// rectangle type width
} ParamRectangleType;
typedef struct {
	ParamRectangleType type;
	ParamRectangleUnion value;
} ParamRectangleNode;

typedef enum {
	PLS_R_EMPTY,
	PLS_R_SHAPE,
	PLS_R_RECTANGLE
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
	PS_E_X_AXIS,	// ellipse type x-axis
	PS_E_Y_AXIS	// ellipse type y-axis
} ParamEllipseType;
typedef struct {
	ParamEllipseType type;
	ParamEllipseUnion value;
} ParamEllipseNode;

typedef enum {
	PLS_E_EMPTY,
	PLS_E_SHAPE,
	PLS_E_ELLIPSE
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
	PS_T_HEIGHT,	// triangle type height
	PS_T_BASE		// triangle type base
} ParamTriangleType;
typedef struct{
	ParamTriangleType type;
	ParamTriangleUnion value;
} ParamTriangleNode;

typedef enum{
	PLS_T_EMPTY,
	PLS_T_SHAPE,
	PLS_T_TRIANGLE
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
	PV_T_FONT_WIDTH,
	PV_T_FONT_FAMILY,
	PV_T_FONT_WEIGHT,
	PV_T_FONT_STYLE,
	PV_T_TEXT_DECORATION,
	PV_T_BACKGROUND_COLOR
} ParamTextType; 
typedef struct {
	ParamTextType type;
	ParamTextUnion value;
} ParamTextNode;

struct ParamListTextNode {
	ParamTextNode * paramTextNode;
	ParamListTextNode * listNode;
};

/** Animations */
typedef enum {
	CS_A_FUNCTION,
	CS_A_VARNAME
} AnimationCompoundStatementType;
typedef union {
	FunctionNode * functionNode;
	char * varname;
} AnimationCompoundStatementUnion;
typedef struct {
	AnimationCompoundStatementType type;
	AnimationCompoundStatementUnion value;
} AnimationCompoundStatementNode;

typedef union {
	ParamListTranslateNode * translateParamList;
	ParamListOpacityNode * opacityParamList;
	ParamListRecolorNode * recolorParamList;
	ParamListRotateNode * rotateParamList;
	ParamListResizeNode * resizeParamList;
	ParamListMorphNode * morphParamList;
} AnimationUnion;
typedef enum {
	A_TRANSLATE_X,
	A_TRANSLATE_Y,
	A_OPACITY,
	A_RECOLOR,
	A_ROTATE,
	A_RESIZE,
	A_MORPH
} AnimationType;
typedef struct {
	AnimationType type;
	AnimationUnion value;
} AnimationNode;

/** Layouts */
typedef struct {
	FunctionListNode * functionList;
} LayoutCompoundStatementNode;

typedef struct {
	layout_t layout;
	LayoutCompoundStatementNode * compoundStatement;
} LayoutNode;

/** Shapes */
typedef union {
	ParamListRectangleNode * rectangleParamList;
	ParamListEllipseNode * ellipseParamList;
	ParamListTriangleNode * triangleParamList;
} ShapeUnion;
typedef enum {
	S_RECTANGLE,
	S_ELLIPSE,
	S_TRIANGLE
} ShapeType;
typedef struct {
	ShapeType type;
	ShapeUnion value;
} ShapeNode;

/** Vectors */
typedef union {
	ParamListTextNode * textParamList;
	ParamListImageNode * imageParamList;
} VectorUnion;
typedef enum {
	V_TEXT,
	V_IMAGE
} VectorType;
typedef struct {
	VectorType type;
	VectorUnion value;
} VectorNode;

/** Others */
// Function
typedef union {
	AnimationNode * animationNode;
	LayoutNode * layoutNode;
	ShapeNode * shapeNode;
	VectorNode * vectorNode;
} FunctionUnion;
typedef enum {
	F_ANIMATION,
	F_LAYOUT,
	F_SHAPE,
	F_VECTOR
} FunctionType;
struct FunctionNode {
	FunctionType type;
	FunctionUnion value;
};

typedef union {
	FunctionNode * functionNode;
	char * varname;
} FunctionListUnion;
typedef enum {
	FL_FUNCTION,
	FL_VARNAME
} FunctionListType;
struct FunctionListNode{
	FunctionListType type;
	FunctionListUnion value;
	FunctionListNode * listNode;
};

// Assign 
typedef struct {
	char * varname;
	FunctionNode * function;
} AssignNode;

// Expression
typedef union {
	FunctionNode * functionNode;
	AssignNode * assignNode;
} ExpressionUnion;
typedef enum {
	E_EMPTY,
	E_FUNCTION,
	E_ASSIGN
} ExpressionType;
struct ExpressionNode {
	ExpressionType type;
	ExpressionUnion value;
	ExpressionNode * nextExpression;
};

#endif
