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
	int functionList;
	int layoutCompoundStatement;
	int primitiveCompoundStatement;

	int primitive;
	int shape;
	int vector;

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

	ParamShapeNode* paramShape;
	ParamListRectangleNode* paramListRectangle;
	ParamRectangleNode* paramRectangle;
	ParamListEllipseNode* paramListEllipse;
	ParamEllipseNode* paramEllipse;
	ParamListTriangleNode* paramListTriangle;
	ParamTriangleNode* paramTriangle;

	int paramListText;
	paramTextNode * paramText;
	int paramListImage;
	int paramImage;

	TypeColorNode* typeColor;
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
%token <layout> LAYOUT
%token <textdeco> TYPE_TEXT_DECORATION
%token <fontfamily> TYPE_FONT_FAMILY
%token <fontstyle> TYPE_FONT_STYLE
%token <token> TYPE_URL
%token <token> COLOR_HEX

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program;
%type <expression> expression;
%type <assign> assign;
%type <function> function;
%type <functionList> functionList;
%type <layoutCompoundStatement> layoutCompoundStatement;
%type <primitiveCompoundStatement> primitiveCompoundStatement;

%type <primitive> primitive;
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

program: expression			{ $$ = ProgramGrammarAction(0); }

expression: /* empty */		{ $$ = Return0(); }
	| function expression	{ $$ = Return0(); }
	| assign expression		{ $$ = Return0(); }

function: primitive		{ $$ = Return0(); }
	| layout			{ $$ = Return0(); }
	| shape				{ $$ = Return0(); }
	| vector			{ $$ = Return0(); }

assign: VARNAME ASSIGN function 		{ $$ = Return0(); }

primitive: TRANSLATE_X OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS primitiveCompoundStatement		{ $$ = Return0(); }
	| TRANSLATE_Y OPEN_PARENTHESIS paramListTranslate CLOSE_PARENTHESIS primitiveCompoundStatement			{ $$ = Return0(); }
	| OPACITY OPEN_PARENTHESIS paramListOpacity CLOSE_PARENTHESIS primitiveCompoundStatement				{ $$ = Return0(); }
	| RECOLOR OPEN_PARENTHESIS paramListRecolor CLOSE_PARENTHESIS primitiveCompoundStatement				{ $$ = Return0(); }
	| ROTATE OPEN_PARENTHESIS paramListRotate CLOSE_PARENTHESIS primitiveCompoundStatement					{ $$ = Return0(); }
	| RESIZE OPEN_PARENTHESIS paramListResize CLOSE_PARENTHESIS primitiveCompoundStatement					{ $$ = Return0(); }
	| MORPH OPEN_PARENTHESIS paramListMorph CLOSE_PARENTHESIS primitiveCompoundStatement					{ $$ = Return0(); }

primitiveCompoundStatement: OPEN_CURLY function CLOSE_CURLY		{ $$ = Return0(); }
	| OPEN_CURLY VARNAME CLOSE_CURLY 							{ $$ = Return0(); }

layout: LAYOUT OPEN_PARENTHESIS CLOSE_PARENTHESIS layoutCompoundStatement		{ $$ = Return0(); }

layoutCompoundStatement: OPEN_CURLY functionList CLOSE_CURLY	{ $$ = Return0(); }

functionList: function COMMA functionList		{ $$ = Return0(); }
	| function									{ $$ = Return0(); }
	| VARNAME COMMA functionList				{ $$ = Return0(); }
	| VARNAME									{ $$ = Return0(); }

shape: RECTANGLE OPEN_PARENTHESIS paramListRectangle CLOSE_PARENTHESIS 		{ $$ = Return0(); }
	| TRIANGLE OPEN_PARENTHESIS paramListTriangle CLOSE_PARENTHESIS 		{ $$ = Return0(); }
	| ELLIPSE OPEN_PARENTHESIS paramListEllipse CLOSE_PARENTHESIS 			{ $$ = Return0(); }

vector: IMAGE OPEN_PARENTHESIS paramListImage  CLOSE_PARENTHESIS		{ $$ = Return0(); }
	| TEXT OPEN_PARENTHESIS paramListText CLOSE_PARENTHESIS				{ $$ = Return0(); }

/* Parameters */
// For animations
paramAnimation: PARAM_ALTERNATE COLON TYPE_BOOLEAN	{ $$ = Return0(); }
	| PARAM_LOOP COLON TYPE_BOOLEAN					{ $$ = Return0(); }
	| PARAM_DURATION COLON TYPE_INTEGER				{ $$ = Return0(); }
	| PARAM_DELAY COLON TYPE_INTEGER					{ $$ = Return0(); }

paramListTranslate: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListTranslate		{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramTranslate COMMA paramListTranslate		{ $$ = Return0(); }
	| paramTranslate								{ $$ = Return0(); }

paramTranslate: PARAM_END_VALUE COLON TYPE_INTEGER	{ $$ = Return0(); }

paramListOpacity: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListOpacity			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramOpacity COMMA paramListOpacity			{ $$ = Return0(); }
	| paramOpacity									{ $$ = Return0(); }

paramOpacity: PARAM_ALPHA COLON TYPE_FLOAT			{ $$ = Return0(); }
	| PARAM_ALPHA COLON TYPE_INTEGER				{ $$ = Return0(); }

paramListRotate: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListRotate			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramRotate COMMA paramListRotate				{ $$ = Return0(); }
	| paramRotate									{ $$ = Return0(); }

paramRotate: PARAM_ANGLE COLON TYPE_INTEGER			{ $$ = Return0(); }

paramListResize: /* empty */						{ $$ = Return0(); }
	| paramAnimation COMMA paramListResize			{ $$ = Return0(); }
	| paramAnimation								{ $$ = Return0(); }
	| paramResize COMMA paramListResize				{ $$ = Return0(); }
	| paramResize									{ $$ = Return0(); }

paramResize: PARAM_SCALE COLON TYPE_FLOAT			{ $$ = Return0(); }

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
paramShape: PARAM_FILL_COLOR COLON typeColor		{ $$ = FillColorParamShapeAction($3); }
	| PARAM_BORDER_COLOR COLON typeColor			{ $$ = BorderColorParamShapeAction($3); }
	| PARAM_BORDER_WIDTH COLON TYPE_INTEGER			{ $$ = BorderWidthParamShapeAction($3); }
	| PARAM_ROTATION COLON TYPE_INTEGER				{ $$ = RotationParamShapeAction($3); }

paramListRectangle: /* empty */						{ $$ = EmptyParamListRectangleAction(); }
	| paramShape COMMA paramListRectangle			{ $$ = ParamShapeParamListRectangleAction($1,$3); }
	| paramShape									{ $$ = ParamShapeRectangleAction($1); }
	| paramRectangle COMMA paramListRectangle		{ $$ = ParamRectangleParamListRectangleAction($1,$3);; }
	| paramRectangle								{ $$ = ParamRectangleAction($1); }

paramRectangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = HeightParamRectangleAction($3); }
	| PARAM_WIDTH COLON TYPE_INTEGER				{ $$ = WidthParamRectangleAction($3); }

paramListEllipse: /* empty */						{ $$ = EmptyParamListEllipseAction(); }
	| paramShape COMMA paramListEllipse				{ $$ = ParamShapeParamListEllipseAction($1,$3);}
	| paramShape									{ $$ = ParamShapeEllipseAction($1); }
	| paramEllipse COMMA paramListEllipse			{ $$ = ParamEllipseParamListEllipseAction($1,$3); }
	| paramEllipse									{ $$ = ParamEllipseAction($1); }

paramEllipse: PARAM_X_AXIS COLON TYPE_INTEGER		{ $$ = XAxisParamEllipseAction($3); }
	| PARAM_Y_AXIS COLON TYPE_INTEGER				{ $$ = YAxisParamEllipseAction($3); }

paramListTriangle: /* empty */						{ $$ = EmptyParamListTriangleAction(); }
	| paramShape COMMA paramListTriangle			{ $$ = ParamShapeParamListTriangleAction($1,$3); }
	| paramShape									{ $$ = ParamShapeTriangleAction($1); }
	| paramTriangle COMMA paramListTriangle			{ $$ = ParamTriangleParamListTriangleAction($1,$3); }
	| paramTriangle									{ $$ = ParamTriangleAction($1); }

paramTriangle: PARAM_HEIGHT COLON TYPE_INTEGER		{ $$ = HeightParamTriangleAction($3); }
	| PARAM_BASE COLON TYPE_INTEGER					{ $$ = BaseParamTriangleAction($3); }

// For vectors
paramListImage: /* empty */					{ $$ = Return0(); }
	| paramImage COMMA paramListImage		{ $$ = ParamListImageMultipleAction($1, $3); }
	| paramImage							{ $$ = ParamListImageAction($1); }

paramImage: PARAM_SRC COLON DOUBLE_QUOTE TYPE_URL DOUBLE_QUOTE { $$ = ParamImageAction($4); }

paramListText: /* empty */					{ $$ = Return0(); }
	| paramText COMMA paramListText			{ $$ = ParamListTextMultipleAction($1, $3); }
	| paramText								{ $$ = ParamListTextAction($1); }

paramText: PARAM_FONT_WIDTH COLON TYPE_INTEGER 				{ $$ = ParamFontWidthAction($3); }
	| PARAM_FONT_FAMILY COLON TYPE_FONT_FAMILY 				{ $$ = ParamFontFamilyAction($3); }
	| PARAM_FONT_WEIGHT COLON TYPE_INTEGER 					{ $$ = ParamFontWeightAction($3); }
	| PARAM_FONT_STYLE COLON TYPE_FONT_STYLE 				{ $$ = ParamFontStyleAction($3); }
	| PARAM_TEXT_DECORATION COLON TYPE_TEXT_DECORATION 		{ $$ = ParamTextDecorationAction($3); }
	| PARAM_BACKGROUND_COLOR COLON typeColor 				{ $$ = ParamBackgroundColorAction($3); }

/* Data types */
typeColor: COLOR_HEX			{ $$ = ParamTypeColorAction($1); }

typePoints: TYPE_FLOAT typePoints 		{ $$ = ParamTypeFloatMultipleAction($1, $2); }
	| TYPE_FLOAT 						{ $$ = ParamTypeFloatAction($1); }

%%