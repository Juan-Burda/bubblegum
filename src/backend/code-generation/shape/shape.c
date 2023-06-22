#include "shape.h"

extern int elementId;
extern int htmlIdentWidth;

void generateShape(Generator generator, ShapeNode *shape) {
    switch (shape->type) {
        case S_RECTANGLE:
            sb_appendf(generator.htmlSb,
                       "%.*s<div id=\"id-%d\" class=\"shape rectangle\"></div>\n",
                       htmlIdentWidth, TABS, elementId);
            break;
        case S_ELLIPSE:
            sb_appendf(generator.htmlSb,
                       "%.*s<div id=\"id-%d\" class=\"shape ellipse\"></div>\n",
                       htmlIdentWidth, TABS, elementId);
            break;
        case S_TRIANGLE:
            sb_appendf(generator.htmlSb,
                       "%.*s<div id=\"id-%d\" class=\"shape triangle\"></div>\n",
                       htmlIdentWidth, TABS, elementId);
            break;

        default:
            break;
    }

    generateShapeParams(generator, shape);

    elementId++;
}

void generateShapeParams(Generator generator, ShapeNode *shape) {
    ShapeType shapeType = shape->type;
    ParameterMap *paramMap = shape->paramMap, *currParameter, *tmp;
    UT_hash_handle hh = shape->paramMap->hh;

    if (HASH_COUNT(paramMap) == 0)
        return;

    sb_appendf(generator.cssSb, "#id-%d {\n", elementId);

    HASH_ITER(hh, paramMap, currParameter, tmp) {
        switch (currParameter->type) {
            case PS_S_FILL_COLOR:
                sb_appendf(generator.cssSb, "\tbackground-color: %s;\n",
                           currParameter->value.color);
                break;

            case PS_S_BORDER_COLOR:
                sb_appendf(generator.cssSb, "\tborder-color: %dpx;\n",
                           currParameter->value.integer);
                break;

            case PS_S_BORDER_WIDTH:
                sb_appendf(generator.cssSb,
                           "\tborder: solid;\nborder-color: %dpx;\n",
                           currParameter->value.integer);
                break;

            case PS_S_ROTATION:
                sb_appendf(generator.cssSb, "\ttransform: rotate(%ddeg);\n",
                           currParameter->value.integer);
                break;

            case PS_R_HEIGHT:
            case PS_E_Y_AXIS:
            case PS_T_HEIGHT:
                sb_appendf(generator.cssSb, "\theight: %dpx;\n",
                           currParameter->value.integer);
                break;

            case PS_R_WIDTH:
            case PS_E_X_AXIS:
            case PS_T_BASE:
                sb_appendf(generator.cssSb, "\twidth: %dpx;\n",
                           currParameter->value.integer);
                break;

            default:
                break;
        }
    }

    sb_append(generator.cssSb, "}\n\n");
}