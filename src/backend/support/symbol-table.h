#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "../../libs/uthash.h"
#include "../../utils/data-types.h"
#include "../../utils/parameter-map.h"
#include "../semantic-analysis/abstract-syntax-tree.h"

#define VARNAME_MAX_LENGTH 64

// we know the type bc of the enum, so now we want to know how to read it
typedef union {
    AnimationType animationType;
    MediaType mediaType;
    char textType;
    ShapeType shapeType;
    layout_t layoutType;
} VariableType;

typedef struct {
    char* id;  // key
    FunctionNode* function;

    UT_hash_handle hh;  // make the struct hashable
} SymbolTable;

void stInit();
void stDestroy();

int stAddVariable(char* varname, FunctionNode* function);
int stAddParametersToAnimation(ParameterMap** map, ParamListAnimationNode* paramList);
int stAddParametersToShape(ParameterMap** map, ParamListShapeNode* paramList);
int stAddParametersToMedia(ParameterMap** map, ParamListMediaNode* paramList);
int stAddParametersToText(ParameterMap** map, ParamListTextNode* paramList);

#endif  // _SYMBOL_TABLE_H_