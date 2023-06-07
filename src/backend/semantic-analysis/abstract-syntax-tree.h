#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../utils/data-types.h"
#include "../../utils/global-types.h"

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
    ExpressionNode* expression;
} Program;

/** Parameters */
/* Data type nodes */
typedef struct {
    char* string;
} ParamTypeColorNode;

struct ParamTypePointsNode {
    float floating;
    ParamTypePointsNode* nextPoint;
};

/* Animation nodes */
// Animation
typedef union {
    boolean_t boolean;
    int integer;
} ParamAnimationUnion;
typedef struct {
    ParameterType type;
    ParamAnimationUnion value;
} ParamAnimationNode;

// Translate
typedef union {
    int integer;
} ParamTranslateUnion;
typedef struct {
    ParameterType type;
    ParamTranslateUnion value;
} ParamTranslateNode;

typedef union {
    ParamAnimationNode* animationNode;
    ParamTranslateNode* translateNode;
} ParamListTranslateUnion;
struct ParamListTranslateNode {
    ListNodeType type;
    ParamListTranslateUnion value;
    ParamListTranslateNode* tail;
};

// Opacity
typedef union {
    float floating;
} ParamOpacityUnion;
typedef struct {
    ParameterType type;
    ParamOpacityUnion value;
} ParamOpacityNode;

typedef union {
    ParamAnimationNode* animationNode;
    ParamOpacityNode* opacityNode;
} ParamListOpacityUnion;
struct ParamListOpacityNode {
    ListNodeType type;
    ParamListOpacityUnion value;
    ParamListOpacityNode* tail;
};

// Rotate
typedef union {
    int integer;
} ParamRotateUnion;
typedef struct {
    ParameterType type;
    ParamRotateUnion value;
} ParamRotateNode;

typedef union {
    ParamAnimationNode* animationNode;
    ParamRotateNode* rotateNode;
} ParamListRotateUnion;
struct ParamListRotateNode {
    ListNodeType type;
    ParamListRotateUnion value;
    ParamListRotateNode* tail;
};

// Resize
typedef union {
    float floating;
} ParamResizeUnion;
typedef struct {
    ParameterType type;
    ParamResizeUnion value;
} ParamResizeNode;

typedef union {
    ParamAnimationNode* animationNode;
    ParamResizeNode* resizeNode;
} ParamListResizeUnion;
struct ParamListResizeNode {
    ListNodeType type;
    ParamListResizeUnion value;
    ParamListResizeNode* tail;
};

// Morph
typedef union {
    ParamTypePointsNode* points;
} ParamMorphUnion;
typedef struct {
    ParameterType type;
    ParamMorphUnion value;
} ParamMorphNode;

typedef union {
    ParamAnimationNode* animationNode;
    ParamMorphNode* morphNode;
} ParamListMorphUnion;
struct ParamListMorphNode {
    ListNodeType type;
    ParamListMorphUnion value;
    ParamListMorphNode* tail;
};

// Recolor
typedef union {
    ParamTypeColorNode* color;
} ParamRecolorUnion;
typedef struct {
    ParameterType type;
    ParamRecolorUnion value;
} ParamRecolorNode;

typedef enum {
    PLA_REC_EMPTY,
    PLA_REC_ANIMATION,
    PLA_REC_RECOLOR
} ParamListRecolorType;
typedef union {
    ParamAnimationNode* animationNode;
    ParamRecolorNode* morphNode;
} ParamListRecolorUnion;
struct ParamListRecolorNode {
    ParamListRecolorType type;
    ParamListRecolorUnion value;
    ParamListRecolorNode* tail;
};

/* Shape nodes */
// Shape
typedef union {
    ParamTypeColorNode* color;
    int integer;
} ParamShapeUnion;
typedef struct {
    ParameterType type;
    ParamShapeUnion value;
} ParamShapeNode;

// Rectangle
typedef union {
    int integer;
} ParamRectangleUnion;
typedef struct {
    ParameterType type;
    ParamRectangleUnion value;
} ParamRectangleNode;

typedef union {
    ParamShapeNode* shapeNode;
    ParamRectangleNode* rectangleNode;
} ParamListRectangleUnion;
struct ParamListRectangleNode {
    ListNodeType type;
    ParamListRectangleUnion value;
    ParamListRectangleNode* tail;
};

// Ellipse
typedef union {
    int integer;
} ParamEllipseUnion;
typedef struct {
    ParameterType type;
    ParamEllipseUnion value;
} ParamEllipseNode;

typedef union {
    ParamShapeNode* shapeNode;
    ParamEllipseNode* ellipseNode;
} ParamListEllipseUnion;
struct ParamListEllipseNode {
    ListNodeType type;
    ParamListEllipseUnion value;
    ParamListEllipseNode* tail;
};

// Triangle
typedef union {
    int integer;
} ParamTriangleUnion;
typedef struct {
    ParameterType type;
    ParamTriangleUnion value;
} ParamTriangleNode;

typedef union {
    ParamShapeNode* shapeNode;
    ParamTriangleNode* triangleNode;
} ParamListTriangleUnion;
struct ParamListTriangleNode {
    ListNodeType type;
    ParamListTriangleUnion value;
    ParamListTriangleNode* tail;
};

/* Vector nodes */
// Images
typedef struct {
    char* string;
} ParamImageNode;

struct ParamListImageNode {
    ParamImageNode* paramImageNode;
    ParamListImageNode* tail;
};

// Text
typedef union {
    int integer;
    fontfamily_t fontFamily;
    fontstyle_t fontStyle;
    textdeco_t textDecoration;
    ParamTypeColorNode* color;
} ParamTextUnion;
typedef struct {
    ParameterType type;
    ParamTextUnion value;
} ParamTextNode;

struct ParamListTextNode {
    ParamTextNode* paramTextNode;
    ParamListTextNode* tail;
};

/** Animations */
typedef enum {
    CS_A_FUNCTION,
    CS_A_VARNAME
} AnimationCompoundStatementType;
typedef union {
    FunctionNode* functionNode;
    char* varname;
} AnimationCompoundStatementUnion;
typedef struct {
    AnimationCompoundStatementType type;
    AnimationCompoundStatementUnion value;
} AnimationCompoundStatementNode;

typedef union {
    ParamListTranslateNode* translateParamList;
    ParamListOpacityNode* opacityParamList;
    ParamListRecolorNode* recolorParamList;
    ParamListRotateNode* rotateParamList;
    ParamListResizeNode* resizeParamList;
    ParamListMorphNode* morphParamList;
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
    FunctionListNode* functionList;
} LayoutCompoundStatementNode;

typedef struct {
    layout_t layout;
    LayoutCompoundStatementNode* compoundStatement;
} LayoutNode;

/** Shapes */
typedef union {
    ParamListRectangleNode* rectangleParamList;
    ParamListEllipseNode* ellipseParamList;
    ParamListTriangleNode* triangleParamList;
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
    ParamListTextNode* textParamList;
    ParamListImageNode* imageParamList;
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
    AnimationNode* animationNode;
    LayoutNode* layoutNode;
    ShapeNode* shapeNode;
    VectorNode* vectorNode;
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
    FunctionNode* functionNode;
    char* varname;
} FunctionListUnion;
typedef enum {
    FL_FUNCTION,
    FL_VARNAME
} FunctionListType;
struct FunctionListNode {
    FunctionListType type;
    FunctionListUnion value;
    FunctionListNode* tail;
};

// Assign
typedef struct {
    char* varname;
    FunctionNode* function;
} AssignNode;

// Expression
typedef union {
    FunctionNode* functionNode;
    AssignNode* assignNode;
} ExpressionUnion;
typedef enum {
    E_EMPTY,
    E_FUNCTION,
    E_ASSIGN
} ExpressionType;
struct ExpressionNode {
    ExpressionType type;
    ExpressionUnion value;
    ExpressionNode* nextExpression;
};

#endif
