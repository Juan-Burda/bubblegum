%{

#include "bison-actions/bison-actions.h"

%}

%code requires {
	#include "../../utils/data-types.h"
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
	MediaNode * media;
	TextNode * text;

	ParamAnimationNode * paramAnimation;
	ParamListAnimationNode * paramListAnimation;

	ParamShapeNode * paramShape;
	ParamListShapeNode* paramListShape;

	ParamTextNode * paramText;
	ParamListTextNode * paramListText;

	ParamMediaNode * paramMedia;
	ParamListMediaNode * paramListMedia;

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
%token <token> PARAM_FONT_SIZE
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
%type <media> media;
%type <text> text;

%type <paramAnimation> paramAnimation;
%type <paramListAnimation> paramListTranslate;
%type <paramAnimation> paramTranslate;
%type <paramListAnimation> paramListOpacity;
%type <paramAnimation> paramOpacity;
%type <paramListAnimation> paramListRotate;
%type <paramAnimation> paramRotate;
%type <paramListAnimation> paramListResize;
%type <paramAnimation> paramResize;
%type <paramListAnimation> paramListMorph;
%type <paramAnimation> paramMorph;
%type <paramListAnimation> paramListRecolor;
%type <paramAnimation> paramRecolor;

%type <paramShape> paramShape;
%type <paramListShape> paramListRectangle;
%type <paramShape> paramRectangle;
%type <paramListShape> paramListEllipse;
%type <paramShape> paramEllipse;
%type <paramListShape> paramListTriangle;
%type <paramShape> paramTriangle;

%type <paramText> paramText;
%type <paramListText> paramListText;
%type <paramMedia> paramImage;
%type <paramListMedia> paramListImage;

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
	| layout			{ $$ = FunctionAction(F_LAYOUT,		(FunctionUnion) { .layoutNode = $1	}); }
	| shape				{ $$ = FunctionAction(F_SHAPE,		(FunctionUnion) { .shapeNode = $1	}); }
	| media				{ $$ = FunctionAction(F_MEDIA,		(FunctionUnion) { .mediaNode = $1	}); }
	| text				{ $$ = FunctionAction(F_TEXT,		(FunctionUnion)	{ .textNode = $1	});	}

functionList: function COMMA functionList		{ $$ = FunctionListAction(FL_FUNCTION,	$3,		(FunctionListUnion) { .functionNode = $1 }); }
	| function									{ $$ = FunctionListAction(FL_FUNCTION,	NULL,	(FunctionListUnion) { .functionNode = $1 }); }
	| VARNAME COMMA functionList				{ $$ = FunctionListAction(FL_VARNAME,	$3,		(FunctionListUnion) { .varname = $1 }); }
	| VARNAME									{ $$ = FunctionListAction(FL_VARNAME,	NULL,	(FunctionListUnion) { .varname = $1 }); }

assign: VARNAME ASSIGN function 		{ $$ = AssignAction($1, $3); }

animation: TRANSLATE_X OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS animationCompoundStatement		{ $$ = AnimationAction(A_TRANSLATE_X,	$3,	$5); }
	| TRANSLATE_Y OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS animationCompoundStatement			{ $$ = AnimationAction(A_TRANSLATE_Y,	$3,	$5); }
	| OPACITY OPEN_PARENTHESIS paramListOpacity CLOSE_PARENTHESIS animationCompoundStatement				{ $$ = AnimationAction(A_OPACITY, 		$3,	$5); }
	| RECOLOR OPEN_PARENTHESIS paramListRecolor CLOSE_PARENTHESIS animationCompoundStatement				{ $$ = AnimationAction(A_RECOLOR, 		$3,	$5); }
	| ROTATE OPEN_PARENTHESIS paramListRotate CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_ROTATE, 		$3,	$5); }
	| RESIZE OPEN_PARENTHESIS paramListResize CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_RESIZE, 		$3,	$5); }
	| MORPH OPEN_PARENTHESIS paramListMorph CLOSE_PARENTHESIS animationCompoundStatement					{ $$ = AnimationAction(A_MORPH, 		$3,	$5); }

animationCompoundStatement: OPEN_CURLY function CLOSE_CURLY		{ $$ = AnimationCompoundStatementAction(CS_A_FUNCTION,	(AnimationCompoundStatementUnion) { .functionNode = $2}); }
	| OPEN_CURLY VARNAME CLOSE_CURLY 							{ $$ = AnimationCompoundStatementAction(CS_A_VARNAME,	(AnimationCompoundStatementUnion) { .varname = $2}); }

layout: LAYOUT OPEN_PARENTHESIS CLOSE_PARENTHESIS layoutCompoundStatement		{ $$ = LayoutAction($1, $4); }

layoutCompoundStatement: OPEN_CURLY functionList CLOSE_CURLY	{ $$ = LayoutCompoundStatementAction($2); }

shape: RECTANGLE OPEN_PARENTHESIS paramListRectangle CLOSE_PARENTHESIS 		{ $$ = ShapeAction(S_RECTANGLE,	$3); }
	| ELLIPSE OPEN_PARENTHESIS paramListEllipse CLOSE_PARENTHESIS 			{ $$ = ShapeAction(S_ELLIPSE,	$3); }
	| TRIANGLE OPEN_PARENTHESIS paramListTriangle CLOSE_PARENTHESIS 		{ $$ = ShapeAction(S_TRIANGLE,	$3); }

media: IMAGE OPEN_PARENTHESIS paramListImage  CLOSE_PARENTHESIS		{ $$ = MediaAction(M_IMAGE, $3); }

text: TEXT OPEN_PARENTHESIS paramListText CLOSE_PARENTHESIS			{ $$ = TextAction($3); }

/* Parameters */
// For animations
paramAnimation: PARAM_ALTERNATE COLON TYPE_BOOLEAN	{ $$ = ParamAnimationAction(PA_A_ALTERNATE,	(ParamAnimationUnion) { .boolean = $3 }); }
	| PARAM_LOOP COLON TYPE_BOOLEAN					{ $$ = ParamAnimationAction(PA_A_LOOP,		(ParamAnimationUnion) { .boolean = $3 }); }
	| PARAM_DURATION COLON TYPE_INTEGER				{ $$ = ParamAnimationAction(PA_A_DURATION,	(ParamAnimationUnion) { .integer = $3 }); }
	| PARAM_DELAY COLON TYPE_INTEGER				{ $$ = ParamAnimationAction(PA_A_DELAY,		(ParamAnimationUnion) { .integer = $3 }); }

paramListTranslate: %empty							{ $$ = ParamListAnimationAddParamAction(TRUE, 	NULL,	NULL); }
	| paramAnimation COMMA paramListTranslate		{ $$ = ParamListAnimationAddParamAction(FALSE, 	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE, 	NULL,	$1); }
	| paramTranslate COMMA paramListTranslate		{ $$ = ParamListAnimationAddParamAction(FALSE, $3, 	$1); }
	| paramTranslate								{ $$ = ParamListAnimationAddParamAction(FALSE, NULL,	$1); }

paramTranslate: PARAM_END_VALUE COLON TYPE_INTEGER	{ $$ = ParamAnimationAction(PA_T_END_VALUE, (ParamAnimationUnion) { .integer = $3 }); }

paramListOpacity: %empty							{ $$ = ParamListAnimationAddParamAction(TRUE, 	NULL,	NULL); }
	| paramAnimation COMMA paramListOpacity			{ $$ = ParamListAnimationAddParamAction(FALSE, 	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE, 	NULL,	$1); }
	| paramOpacity COMMA paramListOpacity			{ $$ = ParamListAnimationAddParamAction(FALSE, $3,		$1); }
	| paramOpacity									{ $$ = ParamListAnimationAddParamAction(FALSE, NULL,	$1); }

paramOpacity: PARAM_ALPHA COLON TYPE_FLOAT			{ $$ = ParamAnimationAction(PA_O_ALPHA, (ParamAnimationUnion) { .floating = $3 }); }

paramListRotate: %empty								{ $$ = ParamListAnimationAddParamAction(TRUE,	NULL,	NULL); }
	| paramAnimation COMMA paramListRotate			{ $$ = ParamListAnimationAddParamAction(FALSE,	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE,	NULL,	$1); }
	| paramRotate COMMA paramListRotate				{ $$ = ParamListAnimationAddParamAction(FALSE,	$3,		$1); }
	| paramRotate									{ $$ = ParamListAnimationAddParamAction(FALSE,	NULL,	$1); }

paramRotate: PARAM_ANGLE COLON TYPE_INTEGER			{ $$ = ParamAnimationAction(PA_R_ANGLE, (ParamAnimationUnion) { .integer = $3 }); }

paramListResize: %empty								{ $$ = ParamListAnimationAddParamAction(TRUE, 	NULL,	NULL); }
	| paramAnimation COMMA paramListResize			{ $$ = ParamListAnimationAddParamAction(FALSE, 	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE, 	NULL,	$1); }
	| paramResize COMMA paramListResize				{ $$ = ParamListAnimationAddParamAction(FALSE, $3,		$1); }
	| paramResize									{ $$ = ParamListAnimationAddParamAction(FALSE, NULL,	$1); }

paramResize: PARAM_SCALE COLON TYPE_FLOAT			{ $$ = ParamAnimationAction(PA_RE_SCALE, (ParamAnimationUnion) { .floating = $3 }); }

paramListMorph: %empty								{ $$ = ParamListAnimationAddParamAction(TRUE, 	NULL,	NULL); }
	| paramAnimation COMMA paramListMorph			{ $$ = ParamListAnimationAddParamAction(FALSE, 	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE, 	NULL,	$1); }
	| paramMorph COMMA paramListMorph				{ $$ = ParamListAnimationAddParamAction(FALSE, $3,		$1); }
	| paramMorph									{ $$ = ParamListAnimationAddParamAction(FALSE, NULL,	$1); }

paramMorph: PARAM_POINTS COLON typePoints			{ $$ = ParamAnimationAction(PA_M_POINT, (ParamAnimationUnion) { .points = $3 }); }

paramListRecolor: %empty							{ $$ = ParamListAnimationAddParamAction(TRUE, 	NULL,	NULL); }
	| paramAnimation COMMA paramListRecolor			{ $$ = ParamListAnimationAddParamAction(FALSE, 	$3,		$1); }
	| paramAnimation								{ $$ = ParamListAnimationAddParamAction(FALSE, 	NULL,	$1); }
	| paramRecolor COMMA paramListRecolor			{ $$ = ParamListAnimationAddParamAction(FALSE,	$3,		$1); }
	| paramRecolor									{ $$ = ParamListAnimationAddParamAction(FALSE,	NULL,	$1); }

paramRecolor: PARAM_END_COLOR COLON typeColor		{ $$ = ParamAnimationAction(PA_REC_END_COLOR, (ParamAnimationUnion) { .color = $3 }); }

// For shapes
paramShape: PARAM_FILL_COLOR COLON typeColor		{ $$ = ParamShapeAction(PS_S_FILL_COLOR,	(ParamShapeUnion) { .color = $3 }); }
	| PARAM_BORDER_COLOR COLON typeColor			{ $$ = ParamShapeAction(PS_S_BORDER_COLOR,	(ParamShapeUnion) { .color = $3 }); }
	| PARAM_BORDER_WIDTH COLON TYPE_INTEGER			{ $$ = ParamShapeAction(PS_S_BORDER_WIDTH,	(ParamShapeUnion) { .integer = $3 }); }
	| PARAM_ROTATION COLON TYPE_INTEGER				{ $$ = ParamShapeAction(PS_S_ROTATION,		(ParamShapeUnion) { .integer = $3 }); }

paramListRectangle: %empty							{ $$ = ParamListShapeAddParamAction(TRUE, 	NULL,	NULL); }
	| paramShape COMMA paramListRectangle			{ $$ = ParamListShapeAddParamAction(FALSE, 	$3, 	$1); }
	| paramShape									{ $$ = ParamListShapeAddParamAction(FALSE, 	NULL,	$1); }
	| paramRectangle COMMA paramListRectangle		{ $$ = ParamListShapeAddParamAction(FALSE, $3,		$1); }
	| paramRectangle								{ $$ = ParamListShapeAddParamAction(FALSE,	NULL,	$1); }

paramRectangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = ParamShapeAction(PS_R_HEIGHT, 	(ParamShapeUnion) { .integer = $3 }); }
	| PARAM_WIDTH COLON TYPE_INTEGER				{ $$ = ParamShapeAction(PS_R_WIDTH, 	(ParamShapeUnion) { .integer = $3 }); }

paramListEllipse: %empty							{ $$ = ParamListShapeAddParamAction(TRUE,		NULL, 	NULL); }
	| paramShape COMMA paramListEllipse				{ $$ = ParamListShapeAddParamAction(FALSE,		$3, 	$1); }
	| paramShape									{ $$ = ParamListShapeAddParamAction(FALSE,		NULL,	$1); }
	| paramEllipse COMMA paramListEllipse			{ $$ = ParamListShapeAddParamAction(FALSE, 	$3,		$1); }
	| paramEllipse									{ $$ = ParamListShapeAddParamAction(FALSE, 	NULL,	$1); }

paramEllipse: PARAM_X_AXIS COLON TYPE_INTEGER		{ $$ = ParamShapeAction(PS_E_X_AXIS,	(ParamShapeUnion) { .integer = $3 }); }
	| PARAM_Y_AXIS COLON TYPE_INTEGER				{ $$ = ParamShapeAction(PS_E_Y_AXIS,	(ParamShapeUnion) { .integer = $3 }); }

paramListTriangle: %empty							{ $$ = ParamListShapeAddParamAction(TRUE, 	NULL, 	NULL); }
	| paramShape COMMA paramListTriangle			{ $$ = ParamListShapeAddParamAction(FALSE, 	$3, 	$1); }
	| paramShape									{ $$ = ParamListShapeAddParamAction(FALSE,	NULL,	$1); }
	| paramTriangle COMMA paramListTriangle			{ $$ = ParamListShapeAddParamAction(FALSE,	$3,		$1); }
	| paramTriangle									{ $$ = ParamListShapeAddParamAction(FALSE,	NULL,	$1); }

paramTriangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = ParamShapeAction(PS_T_HEIGHT,	(ParamShapeUnion) { .integer = $3 }); }
	| PARAM_BASE COLON TYPE_INTEGER					{ $$ = ParamShapeAction(PS_T_BASE,		(ParamShapeUnion) { .integer = $3 }); }

// For vectors
paramListImage: %empty						{ $$ = ParamListMediaAddParamAction(TRUE,	NULL, 	NULL); }
	| paramImage COMMA paramListImage		{ $$ = ParamListMediaAddParamAction(FALSE,	$3, 	$1); }
	| paramImage							{ $$ = ParamListMediaAddParamAction(FALSE,	NULL, 	$1); }

paramImage: PARAM_SRC COLON DOUBLE_QUOTE TYPE_URL DOUBLE_QUOTE 	{ $$ = ParamMediaAction(PM_I_URL, (ParamMediaUnion) { .string = $4 }); }

paramListText: %empty						{ $$ = ParamListTextAddParamAction(TRUE,	NULL,	NULL); }
	| paramText COMMA paramListText			{ $$ = ParamListTextAddParamAction(FALSE,	$3,		$1); }
	| paramText								{ $$ = ParamListTextAddParamAction(FALSE,	NULL,	$1); }

paramText: PARAM_FONT_SIZE COLON TYPE_INTEGER 				{ $$ = ParamTextAction(PT_T_FONT_SIZE, 			(ParamTextUnion) { .integer = $3 }); }
	| PARAM_FONT_FAMILY COLON TYPE_FONT_FAMILY 				{ $$ = ParamTextAction(PT_T_FONT_FAMILY,		(ParamTextUnion) { .fontFamily = $3 }); }
	| PARAM_FONT_WEIGHT COLON TYPE_INTEGER 					{ $$ = ParamTextAction(PT_T_FONT_WEIGHT,		(ParamTextUnion) { .integer = $3 }); }
	| PARAM_FONT_STYLE COLON TYPE_FONT_STYLE 				{ $$ = ParamTextAction(PT_T_FONT_STYLE, 		(ParamTextUnion) { .fontStyle = $3 }); }
	| PARAM_TEXT_DECORATION COLON TYPE_TEXT_DECORATION 		{ $$ = ParamTextAction(PT_T_TEXT_DECORATION, 	(ParamTextUnion) { .textDecoration = $3 }); }
	| PARAM_BACKGROUND_COLOR COLON typeColor 				{ $$ = ParamTextAction(PT_T_BACKGROUND_COLOR, 	(ParamTextUnion) { .color = $3 }); }

/* Data types */
typeColor: COLOR_HEX			{ $$ = ParamTypeColorAction($1); }

typePoints: TYPE_FLOAT typePoints 		{ $$ = ParamTypePointsAddPointAction($2, 	$1); }
	| TYPE_FLOAT 						{ $$ = ParamTypePointsAddPointAction(NULL, 	$1); }

%%