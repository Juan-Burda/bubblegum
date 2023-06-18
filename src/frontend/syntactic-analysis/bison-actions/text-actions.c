#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"
#include "bison-actions.h"

TextNode* TextAction(ParamListTextNode* paramList) {
    LogDebug("\tTextNodeAction");

    TextNode* result = (TextNode*)_calloc(1, sizeof(TextNode));

    ParameterMap* map = NULL;
    stAddParametersToText(&map, paramList);

    FREE_LIST(ParamListTextNode, paramList);

    result->paramMap = map;

    return result;
}

/* Parameters */
ParamListTextNode* ParamListTextAddParamAction(boolean_t isEmpty, ParamListTextNode* listNode, ParamTextNode* value) {
    LogDebug("\tParamListTextMultipleAction");

    ParamListTextNode* result = (ParamListTextNode*)_calloc(1, sizeof(ParamListTextNode));
    result->isEmpty = isEmpty;
    result->tail = listNode;
    result->parameter = value;

    return result;
}

ParamTextNode* ParamTextAction(parameter_t type, ParamTextUnion value) {
    LogDebug("\tParamTextAction");

    ParamTextNode* result = (ParamTextNode*)_calloc(1, sizeof(ParamTextNode));
    result->type = type;
    result->value = value;

    return result;
}