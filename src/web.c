#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include "utils/sb.h"
#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>

// Estado de la aplicación.
CompilerState state;

void set_input_string(const char *in);
void end_lexical_scan(void);

typedef struct Code {
    char *htmlCode;
    char *cssCode;
    char *jsCode;
} Code;

EMSCRIPTEN_KEEPALIVE
void freeCode(char *codePtr) {
    free(codePtr);
}

EMSCRIPTEN_KEEPALIVE
char *getCode(char *input) {
    state.program = NULL;
    state.result = 0;
    state.succeed = false;

    set_input_string(input);

    stInit();

    const int result = yyparse();
    Generator generator = generateProgram();

    StringBuilder *outputSb = sb_create();

    // HTML Boilerplate
    sb_append(outputSb, "<!DOCTYPE html>");
    sb_append(outputSb, "<html>");
    sb_append(outputSb, "<head>");
    sb_append(outputSb, "<meta charset=\"UTF-8\"/>");
    sb_append(outputSb, "<meta name=\"viewport\" content=\"width=device-width, "
                        "initial-scale=1.0\"/>");
    sb_append(outputSb, "<title>Bubblegum</title>");
    sb_append(outputSb, "</head>");
    sb_append(outputSb, "<body>");

    char *html = sb_concat(generator.htmlSb);
    sb_append(outputSb, html);
    free(html);

    sb_append(outputSb, "<style>");

    char *css = sb_concat(generator.cssSb);
    sb_append(outputSb, css);
    free(css);

    sb_append(outputSb, "</style>");

    sb_appendf(outputSb, "<script src=\"anime.min.js\"></script>");
    sb_append(outputSb, "<script>");

    char *js = sb_concat(generator.jsSb);
    sb_append(outputSb, js);
    free(js);

    sb_append(outputSb, "</script>");

    sb_append(outputSb, "</body>");
    sb_append(outputSb, "</html>");

    char *code = sb_concat(outputSb);

    sb_free(generator.htmlSb);
    sb_free(generator.cssSb);
    sb_free(generator.jsSb);
    sb_free(outputSb);

    stDestroy();

    return code;
}