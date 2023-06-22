#include "stringify.h"

#define STRINGIFY_ENUM_CASE(x) \
    case x:                    \
        return #x;

#define UNKNOWN "Unknown"

const char* stringifyAnimationType(AnimationType type) {
    switch (type) {
        STRINGIFY_ENUM_CASE(A_TRANSLATE_X)
        STRINGIFY_ENUM_CASE(A_TRANSLATE_Y)
        STRINGIFY_ENUM_CASE(A_OPACITY)
        STRINGIFY_ENUM_CASE(A_RECOLOR)
        STRINGIFY_ENUM_CASE(A_ROTATE)
        STRINGIFY_ENUM_CASE(A_RESIZE)
        STRINGIFY_ENUM_CASE(A_MORPH)

        default:
            return UNKNOWN;
    }
}

const char* stringifyShapeType(ShapeType type) {
    switch (type) {
        STRINGIFY_ENUM_CASE(S_RECTANGLE)
        STRINGIFY_ENUM_CASE(S_ELLIPSE)
        STRINGIFY_ENUM_CASE(S_TRIANGLE)

        default:
            return UNKNOWN;
    }
}

const char* stringifyParameterType(parameter_t type) {
    switch (type) {
        STRINGIFY_ENUM_CASE(PA_A_ALTERNATE)
        STRINGIFY_ENUM_CASE(PA_A_LOOP)
        STRINGIFY_ENUM_CASE(PA_A_DURATION)
        STRINGIFY_ENUM_CASE(PA_A_DELAY)
        STRINGIFY_ENUM_CASE(PA_T_END_VALUE)
        STRINGIFY_ENUM_CASE(PA_O_ALPHA)
        STRINGIFY_ENUM_CASE(PA_R_ANGLE)
        STRINGIFY_ENUM_CASE(PA_RE_SCALE)
        STRINGIFY_ENUM_CASE(PA_M_POINT)
        STRINGIFY_ENUM_CASE(PA_REC_END_COLOR)
        STRINGIFY_ENUM_CASE(PS_S_FILL_COLOR)
        STRINGIFY_ENUM_CASE(PS_S_BORDER_COLOR)
        STRINGIFY_ENUM_CASE(PS_S_BORDER_WIDTH)
        STRINGIFY_ENUM_CASE(PS_S_ROTATION)
        STRINGIFY_ENUM_CASE(PS_R_HEIGHT)
        STRINGIFY_ENUM_CASE(PS_R_WIDTH)
        STRINGIFY_ENUM_CASE(PS_E_X_AXIS)
        STRINGIFY_ENUM_CASE(PS_E_Y_AXIS)
        STRINGIFY_ENUM_CASE(PS_T_HEIGHT)
        STRINGIFY_ENUM_CASE(PS_T_BASE)
        STRINGIFY_ENUM_CASE(PM_I_URL)
        STRINGIFY_ENUM_CASE(PT_T_FONT_SIZE)
        STRINGIFY_ENUM_CASE(PT_T_FONT_FAMILY)
        STRINGIFY_ENUM_CASE(PT_T_FONT_WEIGHT)
        STRINGIFY_ENUM_CASE(PT_T_FONT_STYLE)
        STRINGIFY_ENUM_CASE(PT_T_TEXT_DECORATION)
        STRINGIFY_ENUM_CASE(PT_T_BACKGROUND_COLOR)

        default:
            return UNKNOWN;
    }
}

const char* stringifyMediaType(MediaType type) {
    switch (type) {
        STRINGIFY_ENUM_CASE(M_IMAGE)

        default:
            return UNKNOWN;
    }
}

const char* stringifyFontStyle(fontstyle_t style) {
    switch (style) {
        STRINGIFY_ENUM_CASE(NORMAL)
        STRINGIFY_ENUM_CASE(ITALIC)
        STRINGIFY_ENUM_CASE(OBLIQUE)

        default:
            return UNKNOWN;
    }
}

const char* stringifyFontFamily(fontfamily_t family) {
    switch (family) {
        STRINGIFY_ENUM_CASE(ARIAL)
        STRINGIFY_ENUM_CASE(HELVETICA)
        STRINGIFY_ENUM_CASE(VERDANA)
        STRINGIFY_ENUM_CASE(FANTASY)
        STRINGIFY_ENUM_CASE(MONOSPACE)

        default:
            return UNKNOWN;
    }
}

const char* stringifyTextDecoration(textdeco_t deco) {
    switch (deco) {
        STRINGIFY_ENUM_CASE(UNDERLINE)
        STRINGIFY_ENUM_CASE(OVERLINE)
        case LINE_THROUGH:
            return "LINE-THROUGH";

        default:
            return UNKNOWN;
    }
}

const char* stringifyProblemType(ProblemType problem) {
    switch (problem) {
        STRINGIFY_ENUM_CASE(WARNING);
        STRINGIFY_ENUM_CASE(ERROR);

        default:
            return UNKNOWN;
    }
}
