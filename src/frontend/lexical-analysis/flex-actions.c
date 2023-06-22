#include "flex-actions.h"
#include "../../backend/support/logger.h"
#include "../../utils/wrapper-functions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
    LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
    LogDebug("EndCommentPatternAction.");
}

/* Layouts */
token LayoutPatternAction(const char *lexeme, const layout_t layoutType) {
    LogDebug("LayoutPatternAction: '%s' ", lexeme);
    yylval.layoutType = layoutType;

    return LAYOUT;
}

/* Animation primitives */
token AnimationOpacityPatternAction(const char *lexeme) {
    LogDebug("AnimationOpacityPatternAction: '%s' ", lexeme);
    yylval.token = OPACITY;

    return OPACITY;
}

token AnimationTranslateXPatternAction(const char *lexeme) {
    LogDebug("AnimationTranslateYPatternAction: '%s' ", lexeme);
    yylval.token = TRANSLATE_X;

    return TRANSLATE_X;
}

token AnimationTranslateYPatternAction(const char *lexeme) {
    LogDebug("AnimationTranslateYPatternAction: '%s' ", lexeme);
    yylval.token = TRANSLATE_Y;

    return TRANSLATE_Y;
}

token AnimationRecolorPatternAction(const char *lexeme) {
    LogDebug("AnimationRecolorPatternAction: '%s' ", lexeme);
    yylval.token = RECOLOR;

    return RECOLOR;
}

token AnimationRotatePatternAction(const char *lexeme) {
    LogDebug("AnimationRotatePatternAction: '%s' ", lexeme);
    yylval.token = ROTATE;

    return ROTATE;
}

token AnimationResizePatternAction(const char *lexeme) {
    LogDebug("AnimationResizePatternAction: '%s' ", lexeme);
    yylval.token = RESIZE;

    return RESIZE;
}

token AnimationMorphPatternAction(const char *lexeme) {
    LogDebug("AnimationMorphPatternAction: '%s' ", lexeme);
    yylval.token = MORPH;

    return MORPH;
}

/* Shapes */
token ShapeRectanglePatternAction(const char *lexeme) {
    LogDebug("ShapeRectanglePatternAction: '%s' ", lexeme);
    yylval.token = ROTATE;

    return RECTANGLE;
}

token ShapeEllipsePatternAction(const char *lexeme) {
    LogDebug("ShapeEllipsePatternAction: '%s' ", lexeme);
    yylval.token = ELLIPSE;

    return ELLIPSE;
}

token ShapeTrianglePatternAction(const char *lexeme) {
    LogDebug("ShapeTrianglePatternAction: '%s' ", lexeme);
    yylval.token = TRIANGLE;

    return TRIANGLE;
}

/* Vectors */
token VectorImagePatternAction(const char *lexeme) {
    LogDebug("ObjectImagePatternAction: '%s' ", lexeme);
    yylval.token = IMAGE;

    return IMAGE;
}

token VectorTextPatternAction(const char *lexeme) {
    LogDebug("ObjectTextPatternAction: '%s' ", lexeme);
    yylval.token = TEXT;

    return TEXT;
}

/* Parameters */
// For animations
token ParameterAlternatePatternAction(const char *lexeme) {
    LogDebug("ParameterAlternatePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_ALTERNATE;

    return PARAM_ALTERNATE;
}

token ParameterLoopPatternAction(const char *lexeme) {
    LogDebug("ParameterLoopPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_LOOP;

    return PARAM_LOOP;
}

token ParameterDurationPatternAction(const char *lexeme) {
    LogDebug("ParameterDurationPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_DURATION;

    return PARAM_DURATION;
}

token ParameterDelayPatternAction(const char *lexeme) {
    LogDebug("ParameterDelayPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_DELAY;

    return PARAM_DELAY;
}

token ParameterEndValuePatternAction(const char *lexeme) {
    LogDebug("ParameterEndValuePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_END_VALUE;

    return PARAM_END_VALUE;
}

token ParameterAlphaPatternAction(const char *lexeme) {
    LogDebug("ParameterAlphaPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_ALPHA;

    return PARAM_ALPHA;
}

token ParameterAnglePatternAction(const char *lexeme) {
    LogDebug("ParameterAnglePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_ANGLE;

    return PARAM_ANGLE;
}

token ParameterScalePatternAction(const char *lexeme) {
    LogDebug("ParameterScalePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_SCALE;

    return PARAM_SCALE;
}

token ParameterPointsPatternAction(const char *lexeme) {
    LogDebug("ParameterLoopPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_POINTS;

    return PARAM_POINTS;
}

token ParameterEndColorPatternAction(const char *lexeme) {
    LogDebug("ParameterEndColorPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_END_COLOR;

    return PARAM_END_COLOR;
}

// For shapes
token ParameterFillColorPatternAction(const char *lexeme) {
    LogDebug("ParameterFillColorPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_FILL_COLOR;

    return PARAM_FILL_COLOR;
}

token ParameterBorderColorPatternAction(const char *lexeme) {
    LogDebug("ParameterBorderColorPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_BORDER_COLOR;

    return PARAM_BORDER_COLOR;
}

token ParameterBorderWidthPatternAction(const char *lexeme) {
    LogDebug("ParameterBorderWidthPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_BORDER_WIDTH;

    return PARAM_BORDER_WIDTH;
}

token ParameterRotationPatternAction(const char *lexeme) {
    LogDebug("ParameterRotationPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_ROTATION;

    return PARAM_ROTATION;
}

token ParameterWidthPatternAction(const char *lexeme) {
    LogDebug("ParameterWidthPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_WIDTH;

    return PARAM_WIDTH;
}

token ParameterHeightPatternAction(const char *lexeme) {
    LogDebug("ParameterHeightPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_HEIGHT;

    return PARAM_HEIGHT;
}

token ParameterXAxisPatternAction(const char *lexeme) {
    LogDebug("ParameterXAxisPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_X_AXIS;

    return PARAM_X_AXIS;
}

token ParameterYAxisPatternAction(const char *lexeme) {
    LogDebug("ParameterYAxisPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_Y_AXIS;

    return PARAM_Y_AXIS;
}

token ParameterBasePatternAction(const char *lexeme) {
    LogDebug("ParameterBasePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_BASE;

    return PARAM_BASE;
}

// For text
token ParameterFontSizePatternAction(const char *lexeme) {
    LogDebug("ParameterFontSizePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_FONT_SIZE;

    return PARAM_FONT_SIZE;
}

token ParameterFontFamilyPatternAction(const char *lexeme) {
    LogDebug("ParameterFontFamilyPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_FONT_FAMILY;

    return PARAM_FONT_FAMILY;
}

token ParameterFontWeightPatternAction(const char *lexeme) {
    LogDebug("ParameterFontWeightPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_FONT_WEIGHT;

    return PARAM_FONT_WEIGHT;
}

token ParameterFontStylePatternAction(const char *lexeme) {
    LogDebug("ParameterFontStylePatternAction: '%s' ", lexeme);
    yylval.token = PARAM_FONT_STYLE;

    return PARAM_FONT_STYLE;
}

token ParameterTextDecorationPatternAction(const char *lexeme) {
    LogDebug("ParameterTextDecorationPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_TEXT_DECORATION;

    return PARAM_TEXT_DECORATION;
}

token ParameterBackgroundColorPatternAction(const char *lexeme) {
    LogDebug("ParameterTextDecorationPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_BACKGROUND_COLOR;

    return PARAM_BACKGROUND_COLOR;
}

// For images
token ParameterSrcPatternAction(const char *lexeme) {
    LogDebug("ParameterSrcPatternAction: '%s' ", lexeme);
    yylval.token = PARAM_SRC;

    return PARAM_SRC;
}

/* Type values */
token FontStylePatternAction(const char *lexeme, const fontstyle_t fontstyle) {
    LogDebug("FontStylePatternAction: '%s' ", lexeme);
    yylval.fontstyle = fontstyle;

    return TYPE_FONT_STYLE;
}

token FontFamilyPatternAction(const char *lexeme,
                              const fontfamily_t fontfamily) {
    LogDebug("FontFamilyPatternAction: '%s' ", lexeme);
    yylval.fontfamily = fontfamily;

    return TYPE_FONT_FAMILY;
}

token TextDecoPatternAction(const char *lexeme, const textdeco_t textdeco) {
    LogDebug("TextDecoPatternAction: '%s' ", lexeme);
    yylval.textdeco = textdeco;

    return TYPE_TEXT_DECORATION;
}

token BooleanPatternAction(const char *lexeme, const boolean_t boolean) {
    LogDebug("BooleanPatternAction: '%s' ", lexeme);
    yylval.boolean = boolean;

    return TYPE_BOOLEAN;
}

token FloatPatternAction(const char *lexeme, const int length) {
    LogDebug("FloatPatternAction: '%s' (length = %d).", lexeme, length);
    yylval.floating = atof(lexeme);

    return TYPE_FLOAT;
}

token IntegerPatternAction(const char *lexeme, const int length) {
    LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
    yylval.integer = atoi(lexeme);

    return TYPE_INTEGER;
}

#define HEX_LENGTH 7

token ColorHexPatternAction(const char *lexeme) {
    LogDebug("ColorHexPatternAction: '%s' ", lexeme);
    char *aux = (char *)_calloc(HEX_LENGTH + 1, sizeof(char));
    strncpy(aux, lexeme, HEX_LENGTH);
    yylval.string = aux;

    return COLOR_HEX;
}

/* Others */
token UrlPatternAction(const char *lexeme, const int length) {
    LogDebug("UrlPatternAction: '%s' (length = %d).", lexeme, length);
    char *url = (char *)_calloc(length + 1, sizeof(char));
    strncpy(url, lexeme, length);
    yylval.string = url;

    return TYPE_URL;
}

token VarnamePatternAction(const char *lexeme, const int length) {
    LogDebug("VarnamePatternAction: '%s' (length = %d).", lexeme, length);
    char *varname = (char *)_calloc(length + 1, sizeof(char));
    strncpy(varname, lexeme, length);
    yylval.string = varname;

    return VARNAME;
}

token UnknownPatternAction(const char *lexeme, const int length) {
    LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
    yylval.token = YYUNDEF;
    // Al emitir este token, el compilador aborta la ejecución.

    return YYUNDEF;
}

void IgnoredPatternAction(const char *lexeme, const int length) {
    LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
    // Como no debe hacer nada con el patrón, solo se loguea en consola.
}
