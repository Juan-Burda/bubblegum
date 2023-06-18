#include "animation.h"

extern int elementId;
extern int htmlIdentWidth;

void generateAnimationCompoundStatement(
    Generator generator, AnimationCompoundStatementNode *compoundStatement) {

    switch (compoundStatement->type) {
        case CS_A_FUNCTION:
            generateFunction(generator, compoundStatement->value.functionNode);
            break;

        case CS_A_VARNAME:
            break;

        default:
            break;
    }
}

void generateAnimation(Generator generator, AnimationNode *animation) {
    sb_appendf(generator.jsSb, "anime({\n");

    generateAnimationParams(generator, animation);

    sb_appendf(generator.jsSb, "});\n\n");

    sb_appendf(generator.htmlSb, "%.*s<div id=\"id-%d\">\n", htmlIdentWidth,
               TABS, elementId);

    htmlIdentWidth++;
    elementId++;
    generateAnimationCompoundStatement(generator, animation->compoundStatement);

    htmlIdentWidth--;
    sb_appendf(generator.htmlSb, "%.*s</div>\n", htmlIdentWidth, TABS);
}

void generateAnimationParams(Generator generator, AnimationNode *animation) {
    AnimationType animationType = animation->type;
    ParameterMap *paramMap = animation->paramMap, *currParameter, *tmp;
    UT_hash_handle hh = animation->paramMap->hh;

    int targetChildShapes = 0;

    // Default params
    sb_appendf(generator.jsSb, "\teasing: 'easeInOutSine',\n");

    HASH_ITER(hh, paramMap, currParameter, tmp) {
        switch (currParameter->type) {
            case PA_A_ALTERNATE:
                sb_appendf(generator.jsSb, "\tdirection: '%s',\n",
                           currParameter->value.boolean ? "alternate"
                                                        : "normal");
                break;
            case PA_A_LOOP:
                sb_appendf(generator.jsSb, "\tloop: %s,\n",
                           currParameter->value.boolean ? "true" : "false");
                break;
            case PA_A_DURATION:
                sb_appendf(generator.jsSb, "\tduration: %d,\n",
                           currParameter->value.integer);
                break;
            case PA_A_DELAY:
                sb_appendf(generator.jsSb, "\tdelay: %d,\n",
                           currParameter->value.integer);
                break;
            case PA_T_END_VALUE:
                sb_appendf(generator.jsSb, "\t%s: %d,\n",
                           animationType == A_TRANSLATE_X ? "translateX"
                                                          : "translateY",
                           currParameter->value.integer);
                break;

            case PA_O_ALPHA:
                sb_appendf(generator.jsSb, "\topacity: %.2f,\n",
                           currParameter->value.floating);
                break;

            case PA_R_ANGLE:
                sb_appendf(generator.jsSb, "\trotate: %d,\n",
                           currParameter->value.integer);
                break;

            case PA_RE_SCALE:
                sb_appendf(generator.jsSb, "\tscale: %.2f,\n",
                           currParameter->value.floating);
                break;

            case PA_M_POINT:
                sb_appendf(generator.jsSb, "\tpoints: %s,\n",
                           currParameter->value.points);
                break;

            case PA_REC_END_COLOR:
                sb_appendf(generator.jsSb, "\tbackground: '%s',\n",
                           currParameter->value.color);
                targetChildShapes = 1;
                break;
        }
    }

    if (targetChildShapes)
        sb_appendf(generator.jsSb, "\ttargets: '#id-%d .shape',\n", elementId);
    else
        sb_appendf(generator.jsSb, "\ttargets: '#id-%d',\n", elementId);
}