#include "media.h"

extern int elementId;
extern int htmlIdentWidth;
extern int jsIdentWidth;

void generateMedia(Generator generator, MediaNode *media) {
    switch (media->type) {
        case M_IMAGE:
            sb_appendf(generator.htmlSb, "%.*s<img id=\"id-%d\"></img>\n",
                       htmlIdentWidth, TABS, elementId);
            break;

        default:
            break;
    }

    generateMediaParams(generator, media);

    elementId++;
}

void generateMediaParams(Generator generator, MediaNode *media) {
    ParameterMap *paramMap = media->paramMap, *currParameter, *tmp;
    UT_hash_handle hh = media->paramMap->hh;

    if (HASH_COUNT(paramMap) == 0)
        return;

    sb_appendf(generator.cssSb, "#id-%d {\n", elementId);

    HASH_ITER(hh, paramMap, currParameter, tmp) {
        switch (currParameter->type) {
            case PM_I_URL:
                sb_appendf(generator.cssSb, "\tcontent: url(\"%s\");\n",
                           currParameter->value.string);
                break;

            default:
                break;
        }
    }

    sb_append(generator.cssSb, "}\n\n");
}