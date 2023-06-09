#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../utils/data-types.h"

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

typedef struct ParamListAnimationNode ParamListAnimationNode;
typedef struct ParamListShapeNode ParamListShapeNode;
typedef struct ParamListMediaNode ParamListMediaNode;
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
    float floating;
    ParamTypeColorNode* color;
    ParamTypePointsNode* points;
} ParamAnimationUnion;
typedef struct {
    parameter_t type;
    ParamAnimationUnion value;
} ParamAnimationNode;

struct ParamListAnimationNode {
    boolean_t isEmpty;
    ParamAnimationNode* parameter;
    ParamListAnimationNode* tail;
};

/* Shape nodes */
// Shape
typedef union {
    ParamTypeColorNode* color;
    int integer;
} ParamShapeUnion;
typedef struct {
    parameter_t type;
    ParamShapeUnion value;
} ParamShapeNode;

struct ParamListShapeNode {
    boolean_t isEmpty;
    ParamShapeNode* parameter;
    ParamListShapeNode* tail;
};

/* Media nodes */
// Images
typedef union {
    char* string;
} ParamMediaUnion;
typedef struct {
    parameter_t type;
    ParamMediaUnion value;
} ParamMediaNode;

struct ParamListMediaNode {
    boolean_t isEmpty;
    ParamMediaNode* parameter;
    ParamListMediaNode* tail;
};

/* Text Node */
typedef union {
    int integer;
    fontfamily_t fontFamily;
    fontstyle_t fontStyle;
    textdeco_t textDecoration;
    ParamTypeColorNode* color;
} ParamTextUnion;
typedef struct {
    parameter_t type;
    ParamTextUnion value;
} ParamTextNode;

struct ParamListTextNode {
    boolean_t isEmpty;
    ParamTextNode* parameter;
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
    ParamListAnimationNode* paramList;
    AnimationCompoundStatementNode* compoundStatement;
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
typedef enum {
    S_RECTANGLE,
    S_ELLIPSE,
    S_TRIANGLE
} ShapeType;
typedef struct {
    ShapeType type;
    ParamListShapeNode* paramList;
} ShapeNode;

/** Media */
typedef enum {
    M_IMAGE
} MediaType;
typedef struct {
    MediaType type;
    ParamListMediaNode* paramList;
} MediaNode;

/** Text */
typedef struct {
    ParamListTextNode* paramList;
} TextNode;

/** Others */
// Function
typedef union {
    AnimationNode* animationNode;
    LayoutNode* layoutNode;
    ShapeNode* shapeNode;
    MediaNode* mediaNode;
    TextNode* textNode;
} FunctionUnion;
typedef enum {
    F_ANIMATION,
    F_LAYOUT,
    F_SHAPE,
    F_MEDIA,
    F_TEXT
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
