#ifndef _STRINGIFY_H_
#define _STRINGIFY_H_

#include "../backend/semantic-analysis/abstract-syntax-tree.h"

const char* stringifyAnimationType(AnimationType type);
const char* stringifyParameterType(parameter_t type);
const char* stringifyShapeType(ShapeType type);
const char* stringifyMediaType(MediaType type);
const char* stringifyFontStyle(fontstyle_t style);
const char* stringifyFontFamily(fontfamily_t family);
const char* stringifyTextDecoration(textdeco_t deco);

#endif