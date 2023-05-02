#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"
#include "../data-types.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

// Patrones terminales del lenguaje diseñado.
/* Layouts */
token LayoutPatternAction(const char * lexeme, const layout_t layout);
/* Animation primitives */
token AnimationOpacityPatternAction(const char * lexeme);
token AnimationTranslateXPatternAction(const char * lexeme);
token AnimationTranslateYPatternAction(const char * lexeme);
token AnimationRecolorPatternAction(const char * lexeme);
token AnimationRotatePatternAction(const char * lexeme);
token AnimationResizePatternAction(const char * lexeme);
token AnimationMorphPatternAction(const char * lexeme);
/* Shapes */
token ShapeRectanglePatternAction(const char * lexeme);
token ShapeEllipsePatternAction(const char * lexeme);
token ShapeTrianglePatternAction(const char * lexeme);
/* Vectors */
token VectorImagePatternAction(const char * lexeme);
token VectorTextPatternAction(const char * lexeme);
/* Parameters */
token ParameterAlternatePatternAction(const char * lexeme);
token ParameterLoopPatternAction(const char * lexeme);
token ParameterDurationPatternAction(const char * lexeme);
token ParameterDelayPatternAction(const char * lexeme);
token ParameterEndValuePatternAction(const char * lexeme);
token ParameterAlphaPatternAction(const char * lexeme);
token ParameterAnglePatternAction(const char * lexeme);
token ParameterScalePatternAction(const char * lexeme);
token ParameterPointsPatternAction(const char * lexeme);
token ParameterEndColorPatternAction(const char * lexeme);
token ParameterFillColorPatternAction(const char * lexeme);
token ParameterBorderColorPatternAction(const char * lexeme);
token ParameterBorderWidthPatternAction(const char * lexeme);
token ParameterRotationPatternAction(const char * lexeme);
token ParameterWidthPatternAction(const char * lexeme);
token ParameterHeightPatternAction(const char * lexeme);
token ParameterXAxisPatternAction(const char * lexeme);
token ParameterYAxisPatternAction(const char * lexeme);
token ParameterBasePatternAction(const char * lexeme);
token ParameterFontWidthPatternAction(const char * lexeme);
token ParameterFontFamilyPatternAction(const char * lexeme);
token ParameterFontWeightPatternAction(const char * lexeme);
token ParameterFontStylePatternAction(const char * lexeme);
token ParameterTextDecorationPatternAction(const char * lexeme);
token ParameterBackgroundColorPatternAction(const char * lexeme);
token ParameterSrcPatternAction(const char * lexeme);
/* Type values */
token BooleanPatternAction(const char * lexeme, const boolean_t boolean);
token FontStylePatternAction(const char * lexeme, const fontstyle_t fontstyle);
token FontFamilyPatternAction(const char * lexeme, const fontfamily_t fontfamily);
token TextDecoPatternAction(const char * lexeme, const textdeco_t textdeco);
token FloatPatternAction(const char * lexeme, const int length);
token IntegerPatternAction(const char * lexeme, const int length);
token ColorHexPatternAction(const char * lexeme);
token UrlPatternAction(const char * lexeme, const int length);

/* Others */
token VarnamePatternAction(const char * lexeme, const int length);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

#endif
