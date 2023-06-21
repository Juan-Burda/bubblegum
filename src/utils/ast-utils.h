#ifndef AST_UTILS_H_
#define AST_UTILS_H_

#include "../backend/semantic-analysis/abstract-syntax-tree.h"

void freeProgram(Program* program);
void freeExpression(ExpressionNode* node);
void freeAssign(AssignNode* node);
void freeFunction(FunctionNode* node);

void freeAnimation(AnimationNode* node);
void freeLayout(LayoutNode* node);
void freeShape(ShapeNode* node);
void freeMedia(MediaNode* node);
void freeText(TextNode* node);

void freeParameterMap(ParameterMap* parameters);

void freeColor(ParamTypeColorNode* node);

#endif  // AST_UTILS_H_
