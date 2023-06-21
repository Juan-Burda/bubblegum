#ifndef _PARAMETER_MAP_H_
#define _PARAMETER_MAP_H_

#include "../libs/uthash.h"
#include "data-types.h"

typedef union {
    boolean_t boolean;
    int integer;
    float floating;
    char* color;
    char* string;
    char* points;
} ParameterValue;
typedef struct {
    parameter_t type;  // key
    ParameterValue value;

    UT_hash_handle hh;  // make the struct hashable
} ParameterMap;

#endif  // _PARAMETER_MAP_H_