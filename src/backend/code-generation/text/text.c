#include "text.h"

extern int elementId;
extern int htmlIdentWidth;

void generateText(Generator generator, TextNode *text) {
    sb_appendf(generator.htmlSb,
               "%.*s<div id=\"id-%d\" class=\"text\">TEXT</div>\n",
               htmlIdentWidth, TABS, elementId);

    generateTextParams(generator, text);

    elementId++;
}

void generateTextParams(Generator generator, TextNode *text) {
    ParameterMap *paramMap = text->paramMap, *currParameter, *tmp;
    UT_hash_handle hh = text->paramMap->hh;

    if (HASH_COUNT(paramMap) == 0)
        return;

    sb_appendf(generator.cssSb, "#id-%d {\n", elementId);

    HASH_ITER(hh, paramMap, currParameter, tmp) {
        switch (currParameter->type) {
            case PT_T_FONT_SIZE:
                sb_appendf(generator.cssSb, "\tfont-size: %dpx;\n",
                           currParameter->value.integer);
                break;
            case PT_T_FONT_FAMILY:
                sb_appendf(generator.cssSb, "\tfont-family: %s;\n",
                           currParameter->value.string);
                break;
            case PT_T_FONT_WEIGHT:
                sb_appendf(generator.cssSb, "\tfont-weight: %d;\n",
                           currParameter->value.integer);
                break;
            case PT_T_FONT_STYLE:
                sb_appendf(generator.cssSb, "\tfont-style: %s;\n",
                           currParameter->value.string);
                break;
            case PT_T_TEXT_DECORATION:
                sb_appendf(generator.cssSb, "\ttext-decoration: %s;\n",
                           currParameter->value.color);
                break;
            case PT_T_BACKGROUND_COLOR:
                sb_appendf(generator.cssSb, "\tcolor: %s;\n",
                           currParameter->value.color);
                break;
            default:
                break;
        }
    }

    sb_append(generator.cssSb, "}\n\n");
}