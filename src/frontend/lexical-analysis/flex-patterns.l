%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
digit			[0-9]
endline			[(\r)?\n]
whitespace		[ \f\n\r\t\v]
letter          [a-zA-Z]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }
"{"											{ return OPEN_CURLY; }
"}"											{ return CLOSE_CURLY; }
":"											{ return COLON; }
","											{ return COMMA; }
"="											{ return ASSIGN; }
{endline}                                   { return EOL; }

"Center"									{ return LayoutPatternAction(yytext, CENTER); }
"Top"									    { return LayoutPatternAction(yytext, TOP); }
"Bottom"									{ return LayoutPatternAction(yytext, BOTTOM); }
"Vertical"									{ return LayoutPatternAction(yytext, VERTICAL); }
"Horizontal"								{ return LayoutPatternAction(yytext, HORIZONTAL); }
"Left"									    { return LayoutPatternAction(yytext, LEFT); }
"Right"						    			{ return LayoutPatternAction(yytext, RIGHT); }
"Stack"			    						{ return LayoutPatternAction(yytext, STACK); }
"Grid"	    								{ return LayoutPatternAction(yytext, GRID); }

"Opacity"	   								{ return AnimationOpacityPatternAction(yytext); }
"TranslateX"								{ return AnimationTranslateXPatternAction(yytext); }
"TranslateY"	    						{ return AnimationTranslateYPatternAction(yytext); }
"Recolor"	    							{ return AnimationRecolorPatternAction(yytext); }
"Rotate"	    							{ return AnimationRotatePatternAction(yytext); }
"Resize"	    							{ return AnimationResizePatternAction(yytext); }
"Morph"	    								{ return AnimationMorphPatternAction(yytext); }

"Rectangle"	    							{ return ShapeRectanglePatternAction(yytext); }
"Ellipse"	    							{ return ShapeEllipsePatternAction(yytext); }
"Triangle"	    							{ return ShapeTrianglePatternAction(yytext); }

"Image"	    							    { return ObjectImagePatternAction(yytext); }
"Text"	    							    { return ObjectTextPatternAction(yytext); }

"alternate"	    							{ return ParameterAlternatePatternAction(yytext); }
"loop"	    							    { return ParameterLoopPatternAction(yytext); }
"duration"	    							{ return ParameterDurationPatternAction(yytext); }
"delay"	    			    				{ return ParameterDelayPatternAction(yytext); }
"end-value"	    							{ return ParameterEndValuePatternAction(yytext); }
"alpha"	         							{ return ParameterAlphaPatternAction(yytext); }
"angle"	        							{ return ParameterAnglePatternAction(yytext); }
"scale" 	    							{ return ParameterScalePatternAction(yytext); }
"points"	    							{ return ParameterPointsPatternAction(yytext); }
"end-color" 	    						{ return ParameterEndColorPatternAction(yytext); }
"fill-color"	    						{ return ParameterFillColorPatternAction(yytext); }
"border-color"	    						{ return ParameterBorderColorPatternAction(yytext); }
"border-width"	    						{ return ParameterBorderWidthPatternAction(yytext); }
"rotation"	    							{ return ParameterRotationPatternAction(yytext); }
"width"	        							{ return ParameterWidthPatternAction(yytext); }
"height"	    							{ return ParameterHeightPatternAction(yytext); }
"x-axis"	    							{ return ParameterXAxisPatternAction(yytext); }
"y-axis"	    							{ return ParameterYAxisPatternAction(yytext); }
"base"  	    							{ return ParameterBasePatternAction(yytext); }
"font-width"  	    						{ return ParameterFontWidthPatternAction(yytext); }
"font-family"  	    						{ return ParameterFontFamilyPatternAction(yytext); }
"font-weight"  	    						{ return ParameterFontWeightPatternAction(yytext); }
"font-style"  	    						{ return ParameterFontStylePatternAction(yytext); }
"text-decoration"  	    					{ return ParameterTextDecorationPatternAction(yytext); }
"background-color"  	    				{ return ParameterBackgroundColorPatternAction(yytext); }
"src"  	    				                { return ParameterSrcPatternAction(yytext); }

"true"									    { return BooleanPatternAction(yytext, TRUE); }
"false"									    { return BooleanPatternAction(yytext, FALSE); }
"normal"									{ return FontStylePatternAction(yytext, NORMAL); }
"italic"									{ return FontStylePatternAction(yytext, ITALIC); }
"oblique"									{ return FontStylePatternAction(yytext, OBLIQUE); }
"arial"								        { return FontFamilyPatternAction(yytext, ARIAL); }
"helvetica"								    { return FontFamilyPatternAction(yytext, HELVETICA); }
"verdana"								    { return FontFamilyPatternAction(yytext, VERDANA); }
"fantasy"								    { return FontFamilyPatternAction(yytext, FANTASY); }
"monospace"								    { return FontFamilyPatternAction(yytext, MONOSPACE); }
"underline"								    { return TextDecoPatternAction(yytext, UNDERLINE); }
"overline"								    { return TextDecoPatternAction(yytext, OVERLINE); }
"line-through"								{ return TextDecoPatternAction(yytext, LINE_THROUGH); }
{digit}+									{ return IntegerPatternAction(yytext, yyleng); }
{letter}+									{ return VarnamePatternAction(yytext, yyleng); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
