#ifndef _STRINGIFY_H_
#define _STRINGIFY_H_

#include "../backend/semantic-analysis/abstract-syntax-tree.h"

const char* stringifyAnimationType(AnimationType type);
const char* stringifyParameterType(ParameterType type);
const char* stringifyShapeType(ShapeType type);

#endif