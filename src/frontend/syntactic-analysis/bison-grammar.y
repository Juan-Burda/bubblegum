%{

#include "bison-actions.h"

%}

%code requires {
	#include "../data-types.h"
}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int assign;
	int function;
	int compoundStatement;

	int primitive;
	int shape;

	int paramAnimation;
	int paramListTranslate;
	int paramTranslate;
	int paramListOpacity;
	int paramOpacity;
	int paramListRotate;
	int paramRotate;
	int paramListResize;
	int paramResize;
	int paramListMorph;
	int paramMorph;
	int paramListRecolor;
	int paramRecolor;

	int paramShape;
	int paramListRectangle;
	int paramRectangle;
	int paramListEllipse;
	int paramEllipse;
	int paramListTriangle;
	int paramTriangle;

	int typeInteger;
	int typeBoolean;
	int typeShape;
	int typePrimitive;
	int typeColor;
	int typeFloat;
	int typePoints;

	// Terminales.
	token token;
	int integer;
	float floating;
	char * string;
	layout_t layout;
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
%token <token> VARNAME
%token <token> ASSIGN

// Layouts
%token <layout> LAYOUT
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
%token <layout> TYPE_LAYOUT
%token <textdeco> TYPE_TEXT_DECORATION
%token <fontfamily> TYPE_FONT_FAMILY
%token <fontstyle> TYPE_FONT_STYLE
%token <token> COLOR_HEX

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program;
%type <expression> expression;
%type <assign> assign;
%type <function> function;
%type <compoundStatement> compoundStatement;

%type <primitive> primitive;
%type <layout> layout;
%type <shape> shape;

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

%type <typeFloat> typeFloat;
%type <typeInteger> typeInteger;
%type <typeBoolean> typeBoolean;
%type <typePrimitive> typePrimitive;
%type <typeShape> typeShape;
%type <typeColor> typeColor;
%type <typePoints> typePoints;

// El símbolo inicial de la gramatica.
%start program

%%

program: expression			{ $$ = ProgramGrammarAction(0); }

expression: /* empty */		{ $$ = Return0(); }
	| primitive				{ $$ = Return0(); }
	| layout				{ $$ = Return0(); }
	| shape					{ $$ = Return0(); }
	| assign				{ $$ = Return0(); }
	| VARNAME				{ $$ = Return0(); }

assign: typePrimitive VARNAME ASSIGN function 		{ $$ = Return0(); }
	| typeShape VARNAME ASSIGN function				{ $$ = Return0(); }
	| VARNAME ASSIGN expression 					{ $$ = Return0(); }

function: primitive		{ $$ = Return0(); }
	| layout			{ $$ = Return0(); }
	| shape				{ $$ = Return0(); }

compoundStatement: /* empty */					{ $$ = Return0(); }
	| OPEN_CURLY expression CLOSE_CURLY			{ $$ = Return0(); }

primitive: TRANSLATE_X OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS compoundStatement		{ $$ = Return0(); }
	| TRANSLATE_Y OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS compoundStatement			{ $$ = Return0(); }
	| OPACITY OPEN_PARENTHESIS paramListOpacity CLOSE_PARENTHESIS compoundStatement					{ $$ = Return0(); }
	| RECOLOR OPEN_PARENTHESIS paramListRecolor CLOSE_PARENTHESIS compoundStatement					{ $$ = Return0(); }
	| ROTATE OPEN_PARENTHESIS paramListRotate CLOSE_PARENTHESIS compoundStatement					{ $$ = Return0(); }
	| RESIZE OPEN_PARENTHESIS paramListResize CLOSE_PARENTHESIS compoundStatement					{ $$ = Return0(); }
	| MORPH OPEN_PARENTHESIS paramListMorph CLOSE_PARENTHESIS compoundStatement						{ $$ = Return0(); }

layout: TYPE_LAYOUT OPEN_PARENTHESIS CLOSE_PARENTHESIS compoundStatement		{ $$ = Return0(); }

shape: RECTANGLE OPEN_PARENTHESIS paramListRectangle CLOSE_PARENTHESIS compoundStatement		{ $$ = Return0(); }
	| TRIANGLE OPEN_PARENTHESIS paramListTriangle CLOSE_PARENTHESIS compoundStatement			{ $$ = Return0(); }
	| ELLIPSE OPEN_PARENTHESIS paramListEllipse CLOSE_PARENTHESIS compoundStatement				{ $$ = Return0(); }

/* Parameters */
// For animations
paramAnimation: PARAM_ALTERNATE COLON typeBoolean	{ $$ = Return0(); }
	| PARAM_LOOP COLON typeBoolean					{ $$ = Return0(); }
	| PARAM_DURATION COLON typeInteger				{ $$ = Return0(); }
	| PARAM_DELAY COLON typeInteger					{ $$ = Return0(); }

paramListTranslate: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListTranslate		{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramTranslate COMMA paramListTranslate		{ $$ = Return0(); }
	| paramTranslate								{ $$ = Return0(); }

paramTranslate: PARAM_END_VALUE COLON typeInteger	{ $$ = Return0(); }

paramListOpacity: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListOpacity			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramOpacity COMMA paramListOpacity			{ $$ = Return0(); }
	| paramOpacity									{ $$ = Return0(); }

paramOpacity: PARAM_ALPHA COLON typeFloat			{ $$ = Return0(); }

paramListRotate: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListRotate			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramRotate COMMA paramListRotate				{ $$ = Return0(); }
	| paramRotate									{ $$ = Return0(); }

paramRotate: PARAM_ANGLE COLON typeInteger			{ $$ = Return0(); }

paramListResize: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListResize			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramResize COMMA paramListResize				{ $$ = Return0(); }
	| paramResize									{ $$ = Return0(); }

paramResize: PARAM_SCALE COLON typeFloat			{ $$ = Return0(); }

paramListMorph: /* empty */							{ $$ = Return0(); }
	| paramAnimation COMMA paramListMorph			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramMorph COMMA paramListMorph				{ $$ = Return0(); }
	| paramMorph									{ $$ = Return0(); }

paramMorph: PARAM_POINTS COLON typePoints			{ $$ = Return0(); }

paramListRecolor: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListRecolor			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramRecolor COMMA paramListRecolor			{ $$ = Return0(); }
	| paramRecolor									{ $$ = Return0(); }

paramRecolor: PARAM_END_COLOR COLON typeColor		{ $$ = Return0(); }

// For shapes
paramShape: PARAM_FILL_COLOR COLON typeColor		{ $$ = Return0(); }
	| PARAM_BORDER_COLOR COLON typeColor			{ $$ = Return0(); }
	| PARAM_BORDER_WIDTH COLON typeInteger			{ $$ = Return0(); }
	| PARAM_ROTATION COLON typeInteger				{ $$ = Return0(); }

paramListRectangle: /* empty */						{ $$ = Return0(); }
	| paramShape COMMA paramListRectangle			{ $$ = Return0(); }
	| paramShape									{ $$ = Return0(); }
	| paramRectangle COMMA paramListRectangle		{ $$ = Return0(); }
	| paramRectangle								{ $$ = Return0(); }

paramRectangle: PARAM_HEIGHT COLON typeInteger		{ $$ = Return0(); }
	| PARAM_WIDTH COLON typeInteger					{ $$ = Return0(); }

paramListEllipse: /* empty */						{ $$ = Return0(); }
	| paramShape COMMA paramListEllipse				{ $$ = Return0(); }
	| paramShape									{ $$ = Return0(); }
	| paramEllipse COMMA paramListEllipse			{ $$ = Return0(); }
	| paramEllipse									{ $$ = Return0(); }

paramEllipse: PARAM_X_AXIS COLON typeInteger		{ $$ = Return0(); }
	| PARAM_Y_AXIS COLON typeInteger				{ $$ = Return0(); }

paramListTriangle: /* empty */						{ $$ = Return0(); }
	| paramShape COMMA paramListTriangle			{ $$ = Return0(); }
	| paramShape									{ $$ = Return0(); }
	| paramTriangle COMMA paramListTriangle			{ $$ = Return0(); }
	| paramTriangle									{ $$ = Return0(); }

paramTriangle: PARAM_HEIGHT COLON typeInteger		{ $$ = Return0(); }
	| PARAM_BASE COLON typeInteger					{ $$ = Return0(); }


/* Data types */
typeFloat: TYPE_FLOAT			{ $$ = Return0(); }

typeInteger: TYPE_INTEGER		{ $$ = Return0(); }

typeBoolean: TYPE_BOOLEAN		{ $$ = Return0(); }

typePrimitive: TRANSLATE_X 		{ $$ = Return0(); }
	| TRANSLATE_Y 				{ $$ = Return0(); }
	| OPACITY 					{ $$ = Return0(); }
	| RECOLOR 					{ $$ = Return0(); }
	| ROTATE 					{ $$ = Return0(); }
	| RESIZE 					{ $$ = Return0(); }
	| MORPH						{ $$ = Return0(); }

typeShape: ELLIPSE 				{ $$ = Return0(); }
	| RECTANGLE 				{ $$ = Return0(); }
	| TRIANGLE 					{ $$ = Return0(); }

typeColor: COLOR_HEX			{ $$ = Return0(); }

typePoints: typeFloat typePoints 		{ $$ = Return0(); }
	| typeFloat 						{ $$ = Return0(); }

%%
