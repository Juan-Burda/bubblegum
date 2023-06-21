#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

typedef enum {
    CENTER,
    TOP,
    BOTTOM,
    VERTICAL,
    HORIZONTAL,
    LEFT,
    RIGHT,
    STACK,
    GRID
} layout_t;

typedef enum {
    FALSE = 0,
    TRUE
} boolean_t;

typedef enum {
    NORMAL,
    ITALIC,
    OBLIQUE
} fontstyle_t;

typedef enum {
    ARIAL,
    HELVETICA,
    VERDANA,
    FANTASY,
    MONOSPACE
} fontfamily_t;

typedef enum {
    UNDERLINE,
    OVERLINE,
    LINE_THROUGH
} textdeco_t;

#define PARAM_IS_STRING(type) ((type) == PA_M_POINT || (type) == PS_S_BORDER_COLOR || (type) == PS_S_FILL_COLOR || (type) == PM_I_URL || (type) == PT_T_BACKGROUND_COLOR)

typedef enum {
    PA_A_ALTERNATE,
    PA_A_LOOP,
    PA_A_DURATION,
    PA_A_DELAY,
    PA_T_END_VALUE,
    PA_O_ALPHA,
    PA_R_ANGLE,
    PA_RE_SCALE,
    PA_M_POINT,
    PA_REC_END_COLOR,

    PS_S_FILL_COLOR,
    PS_S_BORDER_COLOR,
    PS_S_BORDER_WIDTH,
    PS_S_ROTATION,
    PS_R_HEIGHT,
    PS_R_WIDTH,
    PS_E_X_AXIS,
    PS_E_Y_AXIS,
    PS_T_HEIGHT,
    PS_T_BASE,

    PM_I_URL,

    PT_T_FONT_WIDTH,
    PT_T_FONT_FAMILY,
    PT_T_FONT_WEIGHT,
    PT_T_FONT_STYLE,
    PT_T_TEXT_DECORATION,
    PT_T_BACKGROUND_COLOR,
} parameter_t;

#endif  // DATA_TYPES_H_