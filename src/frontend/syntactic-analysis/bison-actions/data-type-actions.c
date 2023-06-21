#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"
#include "bison-actions.h"

ParamTypeColorNode* ParamTypeColorAction(char* typeColor) {
    LogDebug("\tParamTypeColorAction: %s", typeColor);

    ParamTypeColorNode* result = (ParamTypeColorNode*)_calloc(1, sizeof(ParamTypeColorNode));
    result->string = typeColor;

    return result;
}

ParamTypePointsNode* ParamTypePointsAddPointAction(ParamTypePointsNode* pointsNode, float floating) {
    ParamTypePointsNode* result = (ParamTypePointsNode*)_calloc(1, sizeof(ParamTypePointsNode));
    result->nextPoint = pointsNode;
    result->floating = floating;

    return result;
}