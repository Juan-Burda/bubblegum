#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"
#include "bison-actions.h"

AnimationNode* AnimationAction(AnimationType type, ParamListAnimationNode* paramList, AnimationCompoundStatementNode* compoundStatement) {
    LogDebug("\tAnimationNodeAction");

    AnimationNode* result = (AnimationNode*)_calloc(1, sizeof(AnimationNode));
    result->type = type;
    result->compoundStatement = compoundStatement;

    ParameterMap* map = NULL;
    stAddParametersToAnimation(&map, paramList);

    FREE_LIST(ParamListAnimationNode, paramList);

    result->paramMap = map;

    return result;
}

AnimationCompoundStatementNode* AnimationCompoundStatementAction(AnimationCompoundStatementType type, AnimationCompoundStatementUnion value) {
    LogDebug("\tAnimationCompoundStatementNodeAction");

    AnimationCompoundStatementNode* result = (AnimationCompoundStatementNode*)_calloc(1, sizeof(AnimationCompoundStatementNode));
    result->type = type;
    result->value = value;

    return result;
}

/* Parameters */
ParamAnimationNode* ParamAnimationAction(parameter_t type, ParamAnimationUnion value) {
    LogDebug("\tParamAnimationAction");

    ParamAnimationNode* result = (ParamAnimationNode*)_calloc(1, sizeof(ParamAnimationNode));
    result->type = type;
    result->value = value;

    return result;
}

ParamListAnimationNode* ParamListAnimationAddParamAction(boolean_t isEmpty, ParamListAnimationNode* listNode, ParamAnimationNode* value) {
    LogDebug("\tParamListAnimationAddParamAction");

    ParamListAnimationNode* result = (ParamListAnimationNode*)_calloc(1, sizeof(ParamListAnimationNode));
    result->isEmpty = isEmpty;
    result->parameter = value;
    result->tail = listNode;

    return result;
}