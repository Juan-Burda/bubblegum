#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"
#include "bison-actions.h"

MediaNode* MediaAction(MediaType type, ParamListMediaNode* paramList) {
    LogDebug("\tMediaNodeAction");

    MediaNode* result = (MediaNode*)_calloc(1, sizeof(MediaNode));
    result->type = type;

    ParameterMap* map = NULL;
    stAddParametersToMedia(&map, paramList);

    FREE_LIST(ParamListMediaNode, paramList);

    result->paramMap = map;

    return result;
}

/* Parameters */
ParamListMediaNode* ParamListMediaAddParamAction(boolean_t isEmpty, ParamListMediaNode* listNode, ParamMediaNode* value) {
    LogDebug("\tParamListImageAddParamAction");

    ParamListMediaNode* result = (ParamListMediaNode*)_calloc(1, sizeof(ParamListMediaNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}

ParamMediaNode* ParamMediaAction(parameter_t type, ParamMediaUnion value) {
    LogDebug("\tParamImageAction");

    ParamMediaNode* result = (ParamMediaNode*)_calloc(1, sizeof(ParamMediaNode));
    result->type = type;
    result->value = value;

    return result;
}