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
    TRUE,
    FALSE
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

#endif // DATA_TYPES_H_