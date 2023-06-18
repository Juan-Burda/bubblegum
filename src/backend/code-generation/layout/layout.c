#include "layout.h"

extern int elementId;
extern int htmlIdentWidth;

void generateLayoutCompoundStatement(
    Generator generator, LayoutCompoundStatementNode *layoutCompoundStatement) {
    generateFunctionList(generator, layoutCompoundStatement->functionList);
}

void generateLayout(Generator generator, LayoutNode *layout) {
    sb_appendf(generator.htmlSb, "%.*s<div id=\"id-%d\">\n", htmlIdentWidth,
               TABS, elementId);

    htmlIdentWidth++;

    switch (layout->layout) {
        case CENTER:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "center;\n\tjustify-content: center;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case TOP:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "flex-start;\njustify-content: center;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case BOTTOM:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "width: 100%%;\nheight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "flex-end;\n\tjustify-content: center;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case VERTICAL:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb, "\tdisplay: flex;\n\tflex-direction: "
                                        "column;\n\tgap: 8px;\n\talign-items: "
                                        "center;\n\tjustify-content: center;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case HORIZONTAL:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "center;\n\tjustify-content: center;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case LEFT:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "center;\n\tjustify-content: left;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case RIGHT:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb, "\twidth: 100%%;\n\theight: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\tdisplay: flex;\n\tgap: 8px;\n\talign-items: "
                       "center;\n\tjustify-content: right;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        case STACK:
            sb_appendf(generator.cssSb, "#id-%d {\n", elementId);
            sb_appendf(generator.cssSb,
                       "\tposition: relative;\n");
            sb_append(generator.cssSb, "}\n\n");

            sb_appendf(generator.cssSb, "#id-%d > * {\n", elementId);
            sb_appendf(generator.cssSb,
                       "\tposition: absolute;\n\tleft: 100%%;\n\ttop: 100%%;\n");
            sb_appendf(generator.cssSb,
                       "\ttranslate: -50%% -50%%;\n");
            sb_append(generator.cssSb, "}\n\n");
            break;

        default:
            break;
    }

    elementId++;

    generateLayoutCompoundStatement(generator, layout->compoundStatement);

    htmlIdentWidth--;
    sb_appendf(generator.htmlSb, "%.*s</div>\n", htmlIdentWidth, TABS);
}
