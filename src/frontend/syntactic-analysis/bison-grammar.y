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
	int primitive;
	int compoundStatement;
	int paramAnimation;
	int paramListTranslate;
	int paramTranslate;
	int typeInteger;
	int typeBoolean;
	int typeShape;
	int typePrimitive;

	// Terminales.
	token token;
	int integer;
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
%token <token> EOL

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
%token <boolean> TYPE_BOOLEAN
%token <layout> TYPE_LAYOUT
%token <textdeco> TYPE_TEXT_DECORATION
%token <fontfamily> TYPE_FONT_FAMILY
%token <fontstyle> TYPE_FONT_STYLE

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program;
%type <expression> expression;
%type <assign> assign;
%type <primitive> primitive;
%type <compoundStatement> compoundStatement;
%type <paramListTranslate> paramListTranslate;
%type <paramAnimation> paramAnimation;
%type <paramTranslate> paramTranslate;
%type <typeInteger> typeInteger;
%type <typeBoolean> typeBoolean;
%type <typePrimitive> typePrimitive;
%type <typeShape> typeShape;

// El símbolo inicial de la gramatica.
%start program

%%

program: expression			{ $$ = ProgramGrammarAction(0); }

expression: /* empty */		{ $$ = Return0(); }
	| primitive				{ $$ = Return0(); }
	| assign				{ $$ = Return0(); }
	| VARNAME				{ $$ = Return0(); }

assign: typePrimitive VARNAME ASSIGN function 			{ $$ = Return0(); }
	| VARNAME ASSIGN expression 						{ $$ = Return0(); }

function: primitive

primitive: TRANSLATE_X OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS compoundStatement		{ $$ = Return0(); }

compoundStatement: /* empty */					{ $$ = Return0(); }
	| OPEN_CURLY expression CLOSE_CURLY			{ $$ = Return0(); }

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

paramTranslate: PARAM_END_VALUE COLON typeInteger			{ $$ = Return0(); }

/* Data types */
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

%%
