#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"

ShapeNode* ShapeAction(ShapeType type, ParamListShapeNode* paramList) {
    LogDebug("\tShapeNodeAction");

    ShapeNode* result = (ShapeNode*)_calloc(1, sizeof(ShapeNode));
    result->type = type;

    ParameterMap* map = NULL;
    stAddParametersToShape(&map, paramList);

    result->paramMap = map;

    return result;
}

/* Parameters */
ParamShapeNode* ParamShapeAction(parameter_t type, ParamShapeUnion value) {
    LogDebug("\tParamShapeAction");

    ParamShapeNode* result = (ParamShapeNode*)_calloc(1, sizeof(ParamShapeNode));
    result->type = type;
    result->value = value;

    return result;
}

ParamListShapeNode* ParamListShapeAddParamAction(boolean_t isEmpty, ParamListShapeNode* listNode, ParamShapeNode* value) {
    LogDebug("\tParamListShapeAddParamAction");

    ParamListShapeNode* result = (ParamListShapeNode*)_calloc(1, sizeof(ParamListShapeNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}