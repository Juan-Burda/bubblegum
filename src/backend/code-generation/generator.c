#include "generator.h"
#include "animation/animation.h"
#include "layout/layout.h"
#include "shape/shape.h"
#include "media/media.h"
#include "text/text.h"
#include <errno.h>
#include <sys/stat.h>

int elementId = 0;
int htmlIdentWidth = 0;

void buildFiles(Generator generator) {
    mkdir("output", 0777);

    FILE *htmlFile, *cssFile, *jsFile;

    htmlFile = fopen("output/index.html", "w");
    if (htmlFile == NULL) {
        return;
    }

    char *html = NULL;
    html = sb_concat(generator.htmlSb);
    fputs(html, htmlFile);
    free(html);
    sb_free(generator.htmlSb);
    fclose(htmlFile);

    cssFile = fopen("output/index.css", "w");
    if (cssFile == NULL) {
        return;
    }

    char *css = NULL;
    css = sb_concat(generator.cssSb);
    fputs(css, cssFile);
    free(css);
    sb_free(generator.cssSb);
    fclose(cssFile);

    jsFile = fopen("output/index.js", "w");
    if (jsFile == NULL) {
        return;
    }

    char *js = NULL;
    js = sb_concat(generator.jsSb);
    fputs(js, jsFile);
    free(js);
    sb_free(generator.jsSb);

    fclose(jsFile);
}

void generateBoilerPlate(Generator generator, ExpressionNode *expression) {

    // CSS Boilerplate
    sb_append(generator.cssSb, "body {\n");
    sb_append(generator.cssSb, "\twidth: 100vw;\n\theight: 100vh;\n\tbackground: #0a0a0a;\n\toverflow: hidden;\n");
    sb_append(generator.cssSb, "}\n\n");

    sb_append(generator.cssSb, ".ellipse {\n");
    sb_append(generator.cssSb, "\tborder-radius: 50%;\n");
    sb_append(generator.cssSb, "}\n\n");

    sb_append(generator.cssSb, ".triangle {\n");
    sb_append(generator.cssSb,
              "\tclip-path: polygon(0% 100%, 50% 0%, 100% 100%);\n");
    sb_append(generator.cssSb, "}\n\n");

    // HTML Boilerplate
    sb_append(generator.htmlSb, "<!DOCTYPE html>");

    sb_appendf(generator.htmlSb, "%.*s<html>\n", htmlIdentWidth, TABS);
    htmlIdentWidth++;

    sb_appendf(generator.htmlSb, "%.*s<head>\n", htmlIdentWidth, TABS);
    htmlIdentWidth++;

    sb_appendf(generator.htmlSb, "%.*s<meta charset=\"UTF-8\"/>\n",
               htmlIdentWidth, TABS);
    sb_appendf(generator.htmlSb,
               "%.*s<meta name=\"viewport\" content=\"width=device-width, "
               "initial-scale=1.0\"/>\n",
               htmlIdentWidth, TABS);
    sb_appendf(generator.htmlSb, "%.*s<title>Bubblegum</title>\n",
               htmlIdentWidth, TABS);
    sb_appendf(generator.htmlSb,
               "%.*s<link rel=\"stylesheet\" href=\"index.css\"/>\n",
               htmlIdentWidth, TABS);

    htmlIdentWidth--;
    sb_appendf(generator.htmlSb, "%.*s</head>\n", htmlIdentWidth, TABS);

    sb_appendf(generator.htmlSb, "%.*s<body>\n", htmlIdentWidth, TABS);
    htmlIdentWidth++;

    // Animations generation
    generateExpression(generator, state.program->expression);

    // Script link
    sb_appendf(generator.htmlSb,
               "%.*s <script src=\"anime.min.js\"></script>\n", htmlIdentWidth,
               TABS);
    sb_appendf(generator.htmlSb, "%.*s<script src=\"index.js\"></script>\n",
               htmlIdentWidth, TABS);

    htmlIdentWidth--;
    sb_appendf(generator.htmlSb, "%.*s</body>\n", htmlIdentWidth, TABS);

    htmlIdentWidth--;
    sb_appendf(generator.htmlSb, "%.*s</html>\n", htmlIdentWidth, TABS);
}

void generateProgram() {
    if (state.program == NULL)
        return;

    Generator generator = {
        .htmlSb = sb_create(), .cssSb = sb_create(), .jsSb = sb_create()};

    if (generator.htmlSb == NULL || generator.cssSb == NULL ||
        generator.jsSb == NULL)
        return;

    generateBoilerPlate(generator, state.program->expression);

    buildFiles(generator);
}

void generateExpression(Generator generator, ExpressionNode *expression) {
    switch (expression->type) {
        case E_FUNCTION:
            generateFunction(generator, expression->value.functionNode);
            break;

        case E_ASSIGN:
        case E_EMPTY:
        default:
            break;
    }

    if (expression->nextExpression != NULL)
        generateExpression(generator, expression->nextExpression);
}


void generateVariable(Generator generator, char* varname) {
    SymbolTable* entry;
    HASH_FIND_STR(state.symbolTable, varname, entry);

    generateFunction(generator, entry->function);
}

void generateFunction(Generator generator, FunctionNode *function) {
    switch (function->type) {
        case F_SHAPE:
            generateShape(generator, function->value.shapeNode);
            break;

        case F_ANIMATION:
            generateAnimation(generator, function->value.animationNode);
            break;

        case F_LAYOUT:
            generateLayout(generator, function->value.layoutNode);
            break;

        case F_MEDIA:
            generateMedia(generator, function->value.mediaNode);
            break;

        case F_TEXT:
            generateText(generator, function->value.textNode);
            break;

        default:
            break;
    }
}

void generateFunctionList(Generator generator, FunctionListNode *functionList) {
    switch (functionList->type) {
        case FL_FUNCTION:
            generateFunction(generator, functionList->value.functionNode);
            break;

        case FL_VARNAME:
            generateVariable(generator, functionList->value.varname);
            break;

        default:
            break;
    }

    if (functionList->tail != NULL)
        generateFunctionList(generator, functionList->tail);
}
