%{

#include "bison-actions.h"

%}

%code requires {
	#include "../data-types.h"
}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	Program * program;
	ExpressionNode * expression;
	AssignNode * assign;
	FunctionNode * function;
	FunctionListNode * functionList;

	AnimationNode * animation;
	AnimationCompoundStatementNode * animationCompoundStatement;
	LayoutNode * layout;
	ShapeNode * shape;
	LayoutCompoundStatementNode * layoutCompoundStatement;
	VectorNode * vector;

	ParamAnimationNode * paramAnimation;
	ParamListTranslateNode * paramListTranslate;
	ParamTranslateNode * paramTranslate;
	ParamListOpacityNode * paramListOpacity;
	ParamOpacityNode * paramOpacity;
	ParamListRotateNode * paramListRotate;
	ParamRotateNode * paramRotate;
	ParamListResizeNode * paramListResize;
	ParamResizeNode * paramResize;
	ParamListMorphNode * paramListMorph;
	ParamMorphNode * paramMorph;
	ParamListRecolorNode * paramListRecolor;
	ParamRecolorNode * paramRecolor;

	ParamShapeNode * paramShape;
	ParamListRectangleNode * paramListRectangle;
	ParamRectangleNode * paramRectangle;
	ParamListEllipseNode * paramListEllipse;
	ParamEllipseNode * paramEllipse;
	ParamListTriangleNode * paramListTriangle;
	ParamTriangleNode * paramTriangle;

	ParamListTextNode * paramListText;
	ParamTextNode * paramText;
	ParamListImageNode * paramListImage;
	ParamImageNode * paramImage;

	ParamTypeColorNode * typeColor;
	ParamTypePointsNode * typePoints;

	// Terminales.
	token token;
	int integer;
	float floating;
	char * string;
	layout_t layoutType;
	boolean_t boolean;
	textdeco_t textdeco;
	fontfamily_t fontfamily;
	fontstyle_t fontstyle;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_CURLY
%token <token> CLOSE_CURLY
%token <token> COLON
%token <token> COMMA
%token <string> VARNAME
%token <token> ASSIGN
%token <token> DOUBLE_QUOTE

// Animation primitives
%token <token> OPACITY
%token <token> TRANSLATE_X
%token <token> TRANSLATE_Y
%token <token> RECOLOR
%token <token> ROTATE
%token <token> RESIZE
%token <token> MORPH
// Shapes
%token <token> ELLIPSE
%token <token> RECTANGLE
%token <token> TRIANGLE
// Objects
%token <token> IMAGE
%token <token> TEXT

/* Parameters */
// For animations
%token <token> PARAM_ALTERNATE
%token <token> PARAM_LOOP
%token <token> PARAM_DURATION
%token <token> PARAM_DELAY
%token <token> PARAM_END_VALUE
%token <token> PARAM_ALPHA
%token <token> PARAM_ANGLE
%token <token> PARAM_SCALE
%token <token> PARAM_POINTS
%token <token> PARAM_END_COLOR
// For shapes
%token <token> PARAM_FILL_COLOR
%token <token> PARAM_BORDER_COLOR
%token <token> PARAM_BORDER_WIDTH
%token <token> PARAM_ROTATION
%token <token> PARAM_WIDTH
%token <token> PARAM_HEIGHT
%token <token> PARAM_X_AXIS
%token <token> PARAM_Y_AXIS
%token <token> PARAM_BASE
// For text
%token <token> PARAM_FONT_WIDTH
%token <token> PARAM_FONT_FAMILY
%token <token> PARAM_FONT_WEIGHT
%token <token> PARAM_FONT_STYLE
%token <token> PARAM_TEXT_DECORATION
%token <token> PARAM_BACKGROUND_COLOR
// For image
%token <token> PARAM_SRC

/* Data types */
%token <integer> TYPE_INTEGER
%token <floating> TYPE_FLOAT
%token <boolean> TYPE_BOOLEAN
%token <layoutType> LAYOUT
%token <textdeco> TYPE_TEXT_DECORATION
%token <fontfamily> TYPE_FONT_FAMILY
%token <fontstyle> TYPE_FONT_STYLE
%token <string> TYPE_URL
%token <string> COLOR_HEX

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program;
%type <expression> expression;
%type <assign> assign;
%type <function> function;
%type <functionList> functionList;
%type <layoutCompoundStatement> layoutCompoundStatement;
%type <animationCompoundStatement> animationCompoundStatement;

%type <animation> animation;
%type <layout> layout;
%type <shape> shape;
%type <vector> vector;

%type <paramAnimation> paramAnimation;
%type <paramListTranslate> paramListTranslate;
%type <paramTranslate> paramTranslate;
%type <paramListOpacity> paramListOpacity;
%type <paramOpacity> paramOpacity;
%type <paramListRotate> paramListRotate;
%type <paramRotate> paramRotate;
%type <paramListResize> paramListResize;
%type <paramResize> paramResize;
%type <paramListMorph> paramListMorph;
%type <paramMorph> paramMorph;
%type <paramListRecolor> paramListRecolor;
%type <paramRecolor> paramRecolor;

%type <paramShape> paramShape;
%type <paramListRectangle> paramListRectangle;
%type <paramRectangle> paramRectangle;
%type <paramListEllipse> paramListEllipse;
%type <paramEllipse> paramEllipse;
%type <paramListTriangle> paramListTriangle;
%type <paramTriangle> paramTriangle;

%type <paramListText> paramListText;
%type <paramText> paramText;
%type <paramListImage> paramListImage;
%type <paramImage> paramImage;

%type <typeColor> typeColor;
%type <typePoints> typePoints;

// El símbolo inicial de la gramatica.
%start program

%%

program: expression			{ $$ = ProgramAction($1); }

expression: %empty			{ $$ = ExpressionAction(E_EMPTY,	(ExpressionUnion) { .functionNode = NULL }, NULL); }
	| function expression	{ $$ = ExpressionAction(E_FUNCTION,	(ExpressionUnion) { .functionNode = $1 }, $2); }
	| assign expression		{ $$ = ExpressionAction(E_ASSIGN,	(ExpressionUnion) { .assignNode = $1 }, $2); }

function: animation		{ $$ = FunctionAction(F_ANIMATION,	(FunctionUnion) { .animationNode = $1 }); }
	| layout			{ $$ = FunctionAction(F_LAYOUT,		(FunctionUnion) { .layoutNode = $1 }); }
	| shape				{ $$ = FunctionAction(F_SHAPE,		(FunctionUnion) { .shapeNode = $1 }); }
	| vector			{ $$ = FunctionAction(F_VECTOR,		(FunctionUnion) { .vectorNode = $1 }); }

functionList: function COMMA functionList		{ $$ = FunctionListAction(FL_FUNCTION,	$3,		(FunctionListUnion) { .functionNode = $1 }); }
	| function									{ $$ = FunctionListAction(FL_FUNCTION,	NULL,	(FunctionListUnion) { .functionNode = $1 }); }
	| VARNAME COMMA functionList				{ $$ = FunctionListAction(FL_VARNAME,	$3,		(FunctionListUnion) { .varname = $1 }); }
	| VARNAME									{ $$ = FunctionListAction(FL_VARNAME,	NULL,	(FunctionListUnion) { .varname = $1 }); }

assign: VARNAME ASSIGN function 		{ $$ = AssignAction($1, $3); }

animation: TRANSLATE_X OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS animationCompoundStatement		{ $$ = AnimationAction(A_TRANSLATE_X,	(AnimationUnion) { .translateParamList = $3 }); }
	| TRANSLATE_Y OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS animationCompoundStatement			{ $$ = AnimationAction(A_TRANSLATE_Y,	(AnimationUnion) { .translateParamList = $3 }); }
	| OPACITY OPEN_PARENTHESIS paramListOpacity CLOSE_PARENTHESIS animationCompoundStatement				{ $$ = AnimationAction(A_OPACITY, 		(AnimationUnion) { .opacityParamList = $3 }); }
	| RECOLOR OPEN_PARENTHESIS paramListRecolor CLOSE_PARENTHESIS animationCompoundStatement				{ $$ = AnimationAction(A_RECOLOR, 		(AnimationUnion) { .recolorParamList = $3 }); }
	| ROTATE OPEN_PARENTHESIS paramListRotate CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_ROTATE, 		(AnimationUnion) { .rotateParamList = $3 }); }
	| RESIZE OPEN_PARENTHESIS paramListResize CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_RESIZE, 		(AnimationUnion) { .resizeParamList = $3 }); }
	| MORPH OPEN_PARENTHESIS paramListMorph CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_MORPH, 		(AnimationUnion) { .morphParamList = $3 }); }

animationCompoundStatement: OPEN_CURLY function CLOSE_CURLY		{ $$ = AnimationCompoundStatementAction(CS_A_FUNCTION,	(AnimationCompoundStatementUnion) { .functionNode = $2}); }
	| OPEN_CURLY VARNAME CLOSE_CURLY 							{ $$ = AnimationCompoundStatementAction(CS_A_VARNAME,	(AnimationCompoundStatementUnion) { .varname = $2}); }

layout: LAYOUT OPEN_PARENTHESIS CLOSE_PARENTHESIS layoutCompoundStatement		{ $$ = LayoutAction($1, $4); }

layoutCompoundStatement: OPEN_CURLY functionList CLOSE_CURLY	{ $$ = LayoutCompoundStatementAction($2); }

shape: RECTANGLE OPEN_PARENTHESIS paramListRectangle CLOSE_PARENTHESIS 		{ $$ = ShapeAction(S_RECTANGLE,	(ShapeUnion) { .rectangleParamList = $3 }); }
	| ELLIPSE OPEN_PARENTHESIS paramListEllipse CLOSE_PARENTHESIS 			{ $$ = ShapeAction(S_ELLIPSE,	(ShapeUnion) { .ellipseParamList = $3 }); }
	| TRIANGLE OPEN_PARENTHESIS paramListTriangle CLOSE_PARENTHESIS 		{ $$ = ShapeAction(S_TRIANGLE,	(ShapeUnion) { .triangleParamList = $3 }); }

vector: IMAGE OPEN_PARENTHESIS paramListImage  CLOSE_PARENTHESIS		{ $$ = VectorAction(V_IMAGE,	(VectorUnion) { .imageParamList = $3 }); }
	| TEXT OPEN_PARENTHESIS paramListText CLOSE_PARENTHESIS				{ $$ = VectorAction(V_TEXT,		(VectorUnion) { .textParamList = $3 }); }

/* Parameters */
// For animations
paramAnimation: PARAM_ALTERNATE COLON TYPE_BOOLEAN	{ $$ = ParamAnimationAction(PA_A_ALTERNATE,	(ParamAnimationUnion) { .alternate = $3 }); }
	| PARAM_LOOP COLON TYPE_BOOLEAN					{ $$ = ParamAnimationAction(PA_A_LOOP,		(ParamAnimationUnion) { .loop = $3 }); }
	| PARAM_DURATION COLON TYPE_INTEGER				{ $$ = ParamAnimationAction(PA_A_DURATION,	(ParamAnimationUnion) { .duration = $3 }); }
	| PARAM_DELAY COLON TYPE_INTEGER				{ $$ = ParamAnimationAction(PA_A_DELAY,		(ParamAnimationUnion) { .delay = $3 }); }

paramListTranslate: %empty							{ $$ = ParamListTranslateAddParamAction(PLA_T_EMPTY, 		NULL,	(ParamListTranslateUnion) { .animationNode = NULL }); }
	| paramAnimation COMMA paramListTranslate		{ $$ = ParamListTranslateAddParamAction(PLA_T_ANIMATION, 	$3,		(ParamListTranslateUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListTranslateAddParamAction(PLA_T_ANIMATION, 	NULL,	(ParamListTranslateUnion) { .animationNode = $1 }); }
	| paramTranslate COMMA paramListTranslate		{ $$ = ParamListTranslateAddParamAction(PLA_T_TRANSLATE, 	$3, 	(ParamListTranslateUnion) { .translateNode = $1 }); }
	| paramTranslate								{ $$ = ParamListTranslateAddParamAction(PLA_T_TRANSLATE, 	NULL,	(ParamListTranslateUnion) { .translateNode = $1 }); }

paramTranslate: PARAM_END_VALUE COLON TYPE_INTEGER	{ $$ = ParamTranslateAction(PA_T_END_VALUE, (ParamTranslateUnion) { .endValue = $3 }); }

paramListOpacity: %empty							{ $$ = ParamListOpacityAddParamAction(PLA_O_EMPTY, 		NULL,	(ParamListOpacityUnion) { .animationNode = NULL }); }
	| paramAnimation COMMA paramListOpacity			{ $$ = ParamListOpacityAddParamAction(PLA_O_ANIMATION, 	NULL,	(ParamListOpacityUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListOpacityAddParamAction(PLA_O_ANIMATION, 	NULL,	(ParamListOpacityUnion) { .animationNode = $1 }); }
	| paramOpacity COMMA paramListOpacity			{ $$ = ParamListOpacityAddParamAction(PLA_O_OPACITY, 	NULL,	(ParamListOpacityUnion) { .opacityNode = $1 }); }
	| paramOpacity									{ $$ = ParamListOpacityAddParamAction(PLA_O_OPACITY, 	NULL,	(ParamListOpacityUnion) { .opacityNode = $1 }); }

paramOpacity: PARAM_ALPHA COLON TYPE_FLOAT			{ $$ = ParamOpacityAction(PA_O_ALPHA, (ParamOpacityUnion) { .alpha = $3 }); }

paramListRotate: %empty								{ $$ = ParamListRotateAddParamAction(PLA_R_EMPTY,		NULL,	(ParamListRotateUnion) { .animationNode = NULL }); }
	| paramAnimation COMMA paramListRotate			{ $$ = ParamListRotateAddParamAction(PLA_R_ANIMATION,	NULL,	(ParamListRotateUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListRotateAddParamAction(PLA_R_ANIMATION,	NULL,	(ParamListRotateUnion) { .animationNode = $1 }); }
	| paramRotate COMMA paramListRotate				{ $$ = ParamListRotateAddParamAction(PLA_R_ROTATE,		NULL,	(ParamListRotateUnion) { .rotateNode = $1 }); }
	| paramRotate									{ $$ = ParamListRotateAddParamAction(PLA_R_ROTATE,		NULL,	(ParamListRotateUnion) { .rotateNode = $1 }); }

paramRotate: PARAM_ANGLE COLON TYPE_INTEGER			{ $$ = ParamRotateAction(PA_R_ANGLE, (ParamRotateUnion) { .angle = $3 }); }

paramListResize: %empty								{ $$ = ParamListResizeAddParamAction(PLA_RE_EMPTY, 		NULL,	(ParamListResizeUnion) { .animationNode = NULL }); }
	| paramAnimation COMMA paramListResize			{ $$ = ParamListResizeAddParamAction(PLA_RE_ANIMATION, 	NULL,	(ParamListResizeUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListResizeAddParamAction(PLA_RE_ANIMATION, 	NULL,	(ParamListResizeUnion) { .animationNode = $1 }); }
	| paramResize COMMA paramListResize				{ $$ = ParamListResizeAddParamAction(PLA_RE_RESIZE, 	NULL,	(ParamListResizeUnion) { .resizeNode = $1 }); }
	| paramResize									{ $$ = ParamListResizeAddParamAction(PLA_RE_RESIZE, 	NULL,	(ParamListResizeUnion) { .resizeNode = $1 }); }

paramResize: PARAM_SCALE COLON TYPE_FLOAT			{ $$ = ParamResizeAction(PA_RE_SCALE, (ParamResizeUnion) { .scale = $3 }); }

paramListMorph: %empty								{ $$ = ParamListMorphAddParamAction(PLA_M_EMPTY, 		NULL,	(ParamListMorphUnion) { .animationNode = NULL}); }
	| paramAnimation COMMA paramListMorph			{ $$ = ParamListMorphAddParamAction(PLA_M_ANIMATION, 	NULL,	(ParamListMorphUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListMorphAddParamAction(PLA_M_ANIMATION, 	NULL,	(ParamListMorphUnion) { .animationNode = $1 }); }
	| paramMorph COMMA paramListMorph				{ $$ = ParamListMorphAddParamAction(PLA_M_MORPH, 		NULL,	(ParamListMorphUnion) { .morphNode = $1 }); }
	| paramMorph									{ $$ = ParamListMorphAddParamAction(PLA_M_MORPH, 		NULL,	(ParamListMorphUnion) { .morphNode = $1 }); }

paramMorph: PARAM_POINTS COLON typePoints			{ $$ = ParamMorphAction(PA_M_POINT, (ParamMorphUnion) { .points = $3 }); }

paramListRecolor: %empty							{ $$ = ParamListRecolorAddParamAction(PLA_REC_EMPTY, 		NULL,	(ParamListRecolorUnion) { .animationNode = NULL }); }
	| paramAnimation COMMA paramListRecolor			{ $$ = ParamListRecolorAddParamAction(PLA_REC_ANIMATION, 	NULL,	(ParamListRecolorUnion) { .animationNode = $1 }); }
	| paramAnimation								{ $$ = ParamListRecolorAddParamAction(PLA_REC_ANIMATION, 	NULL,	(ParamListRecolorUnion) { .animationNode = $1 }); }
	| paramRecolor COMMA paramListRecolor			{ $$ = ParamListRecolorAddParamAction(PLA_REC_RECOLOR,		NULL,	(ParamListRecolorUnion) { .morphNode = $1 }); }
	| paramRecolor									{ $$ = ParamListRecolorAddParamAction(PLA_REC_RECOLOR,		NULL,	(ParamListRecolorUnion) { .morphNode = $1 }); }

paramRecolor: PARAM_END_COLOR COLON typeColor		{ $$ = ParamRecolorAction(PA_REC_END_COLOR, (ParamRecolorUnion) { .endColor = $3 }); }

// For shapes
paramShape: PARAM_FILL_COLOR COLON typeColor		{ $$ = ParamShapeAction(PS_S_FILL_COLOR,	(ParamShapeUnion) { .fillColor = $3 }); }
	| PARAM_BORDER_COLOR COLON typeColor			{ $$ = ParamShapeAction(PS_S_BORDER_COLOR, (ParamShapeUnion) { .borderColor = $3 }); }
	| PARAM_BORDER_WIDTH COLON TYPE_INTEGER			{ $$ = ParamShapeAction(PS_S_BORDER_WIDTH, (ParamShapeUnion) { .borderWidth = $3 }); }
	| PARAM_ROTATION COLON TYPE_INTEGER				{ $$ = ParamShapeAction(PS_S_ROTATION, (ParamShapeUnion) { .rotation = $3 }); }

paramListRectangle: %empty							{ $$ = ParamListRectangleAddParamAction(PLS_R_EMPTY, 		NULL, 	(ParamListRectangleUnion) { .shapeNode = NULL }); }
	| paramShape COMMA paramListRectangle			{ $$ = ParamListRectangleAddParamAction(PLS_R_SHAPE, 		$3, 	(ParamListRectangleUnion) { .shapeNode = $1 }); }
	| paramShape									{ $$ = ParamListRectangleAddParamAction(PLS_R_SHAPE, 		NULL,	(ParamListRectangleUnion) { .shapeNode = $1 }); }
	| paramRectangle COMMA paramListRectangle		{ $$ = ParamListRectangleAddParamAction(PLS_R_RECTANGLE, 	$3,		(ParamListRectangleUnion) { .rectangleNode = $1 }); }
	| paramRectangle								{ $$ = ParamListRectangleAddParamAction(PLS_R_RECTANGLE, 	NULL,	(ParamListRectangleUnion) { .rectangleNode = $1 }); }

paramRectangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = ParamRectangleAction(PS_R_HEIGHT, 	(ParamRectangleUnion) { .height = $3 }); }
	| PARAM_WIDTH COLON TYPE_INTEGER				{ $$ = ParamRectangleAction(PS_R_WIDTH, 	(ParamRectangleUnion) { .width = $3 }); }

paramListEllipse: %empty							{ $$ = ParamListEllipseAddParamAction(PLS_E_EMPTY,		NULL, 	(ParamListEllipseUnion) { .shapeNode = NULL }); }
	| paramShape COMMA paramListEllipse				{ $$ = ParamListEllipseAddParamAction(PLS_E_SHAPE,		$3, 	(ParamListEllipseUnion)	{ .shapeNode = $1 }); }
	| paramShape									{ $$ = ParamListEllipseAddParamAction(PLS_E_SHAPE,		NULL,	(ParamListEllipseUnion)	{ .shapeNode = $1 }); }
	| paramEllipse COMMA paramListEllipse			{ $$ = ParamListEllipseAddParamAction(PLS_E_ELLIPSE, 	$3,		(ParamListEllipseUnion) { .ellipseNode = $1 }); }
	| paramEllipse									{ $$ = ParamListEllipseAddParamAction(PLS_E_ELLIPSE, 	NULL,	(ParamListEllipseUnion) { .ellipseNode = $1 }); }

paramEllipse: PARAM_X_AXIS COLON TYPE_INTEGER		{ $$ = ParamEllipseAction(PS_E_X_AXIS, (ParamEllipseUnion) { .xAxis = $3 }); }
	| PARAM_Y_AXIS COLON TYPE_INTEGER				{ $$ = ParamEllipseAction(PS_E_Y_AXIS, (ParamEllipseUnion) { .yAxis = $3 }); }

paramListTriangle: %empty							{ $$ = ParamListTriangleAddParamAction(PLS_T_EMPTY, 	NULL, 	(ParamListTriangleUnion) { .shapeNode = NULL }); }
	| paramShape COMMA paramListTriangle			{ $$ = ParamListTriangleAddParamAction(PLS_T_SHAPE, 	$3, 	(ParamListTriangleUnion) { .shapeNode = $1 }); }
	| paramShape									{ $$ = ParamListTriangleAddParamAction(PLS_T_SHAPE,		NULL,	(ParamListTriangleUnion) { .shapeNode = $1 }); }
	| paramTriangle COMMA paramListTriangle			{ $$ = ParamListTriangleAddParamAction(PLS_T_TRIANGLE,	$3,		(ParamListTriangleUnion) { .triangleNode = $1 }); }
	| paramTriangle									{ $$ = ParamListTriangleAddParamAction(PLS_T_TRIANGLE,	NULL,	(ParamListTriangleUnion) { .triangleNode = $1 }); }

paramTriangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = ParamTriangleAction(PS_T_HEIGHT, (ParamTriangleUnion) { .height = $3 }); }
	| PARAM_BASE COLON TYPE_INTEGER					{ $$ = ParamTriangleAction(PS_T_BASE,	(ParamTriangleUnion) { .base = $3 }); }

// For vectors
paramListImage: %empty						{ $$ = ParamListImageAddParamAction(NULL, 	NULL); }
	| paramImage COMMA paramListImage		{ $$ = ParamListImageAddParamAction($3, 	$1); }
	| paramImage							{ $$ = ParamListImageAddParamAction(NULL, 	$1); }

paramImage: PARAM_SRC COLON DOUBLE_QUOTE TYPE_URL DOUBLE_QUOTE 	{ $$ = ParamImageAction($4); }

paramListText: %empty						{ $$ = ParamListTextAddParamAction(NULL, 	NULL); }
	| paramText COMMA paramListText			{ $$ = ParamListTextAddParamAction($3, 		$1); }
	| paramText								{ $$ = ParamListTextAddParamAction(NULL, 	$1); }

paramText: PARAM_FONT_WIDTH COLON TYPE_INTEGER 				{ $$ = ParamTextAction(PV_T_FONT_WIDTH, 		(ParamTextUnion) { .fontWidth = $3 }); }
	| PARAM_FONT_FAMILY COLON TYPE_FONT_FAMILY 				{ $$ = ParamTextAction(PV_T_FONT_FAMILY,		(ParamTextUnion) { .fontFamily = $3 }); }
	| PARAM_FONT_WEIGHT COLON TYPE_INTEGER 					{ $$ = ParamTextAction(PV_T_FONT_WEIGHT,		(ParamTextUnion) { .fontWeight = $3 }); }
	| PARAM_FONT_STYLE COLON TYPE_FONT_STYLE 				{ $$ = ParamTextAction(PV_T_FONT_STYLE, 		(ParamTextUnion) { .fontStyle = $3 }); }
	| PARAM_TEXT_DECORATION COLON TYPE_TEXT_DECORATION 		{ $$ = ParamTextAction(PV_T_TEXT_DECORATION, 	(ParamTextUnion) { .textDecoration = $3 }); }
	| PARAM_BACKGROUND_COLOR COLON typeColor 				{ $$ = ParamTextAction(PV_T_BACKGROUND_COLOR, 	(ParamTextUnion) { .paramTypeColorNode = $3 }); }

/* Data types */
typeColor: COLOR_HEX			{ $$ = ParamTypeColorAction($1); }

typePoints: TYPE_FLOAT typePoints 		{ $$ = ParamTypePointsAddPointAction($2, 	$1); }
	| TYPE_FLOAT 						{ $$ = ParamTypePointsAddPointAction(NULL, 	$1); }

%%