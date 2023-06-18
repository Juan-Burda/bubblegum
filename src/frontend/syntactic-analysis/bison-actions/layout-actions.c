#include "../../../backend/support/logger.h"
#include "../../../backend/support/symbol-table.h"
#include "../../../utils/wrapper-functions.h"

LayoutNode* LayoutAction(layout_t layout, LayoutCompoundStatementNode* compoundStatement) {
    LogDebug("\tLayoutAction");

    LayoutNode* result = (LayoutNode*)_calloc(1, sizeof(LayoutNode));
    result->layout = layout;
    result->compoundStatement = compoundStatement;

    return result;
}

LayoutCompoundStatementNode* LayoutCompoundStatementAction(FunctionListNode* tail) {
    LogDebug("\tLayoutCompoundStatementNodeAction");

    LayoutCompoundStatementNode* result = (LayoutCompoundStatementNode*)_calloc(1, sizeof(LayoutCompoundStatementNode));
    result->functionList = tail;

    return result;
}
