#include "symbol-table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/error-codes.h"
#include "../../utils/stringify.h"
#include "../../utils/wrapper-functions.h"
#include "logger.h"
#include "shared.h"

// TODO: variables anonimas? tipo si no le asignas ningun valor a la variable que pasa
// TODO: no abortar por key duplicada

char* convertPointsToString(ParamTypePointsNode* head);
void stDestroyParameters(ParameterMap* parameters);

void stInit() { state.symbolTable = NULL; }

void stDestroyParameters(ParameterMap* parameters) {
    ParameterMap *currParameter, *tmp2;

    HASH_ITER(hh, parameters, currParameter, tmp2) {
        HASH_DEL(parameters, currParameter);
        // TODO: check for char* or list params tipo Points

        free(currParameter);
    }
}

void stDestroy() {
    SymbolTable *currSymbol, *tmp;

    HASH_ITER(hh, state.symbolTable, currSymbol, tmp) {
        HASH_DEL(state.symbolTable, currSymbol);
        stDestroyParameters(currSymbol->parameters);

        free(currSymbol);
    }
}

// add params to symbol table for animations
int stAddParametersToAnimation(ParameterMap** map, AnimationNode* node) {
    LogDebug("\t\tSymbol Table: Add Animation [%s] parameters", stringifyAnimationType(node->type));

    ParamListAnimationNode* head = node->paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tSymbol Table: Found no parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListAnimationNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tDuplicate key found, aborting...");
            exit(EXIT_FAILURE);
        }

        currParam = (ParameterMap*)_malloc(sizeof(ParameterMap));
        currParam->type = paramType;

        switch (currParam->type) {
            case PA_A_ALTERNATE:
            case PA_A_LOOP:
                currParam->value.boolean = currNode->parameter->value.boolean;
                LogDebug("\t\tAdded {%s, %d}", stringifyParameterType(currParam->type), currParam->value.boolean);
                break;

            case PA_A_DELAY:
            case PA_A_DURATION:
            case PA_T_END_VALUE:
            case PA_R_ANGLE:
                currParam->value.integer = currNode->parameter->value.integer;
                LogDebug("\t\tAdded {%s, %d}", stringifyParameterType(currParam->type), currParam->value.integer);
                break;

            case PA_O_ALPHA:
            case PA_RE_SCALE:
                currParam->value.floating = currNode->parameter->value.floating;
                LogDebug("\t\tAdded {%s, %f}", stringifyParameterType(currParam->type), currParam->value.floating);
                break;

            case PA_M_POINT:
                currParam->value.points = convertPointsToString(currNode->parameter->value.points);
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.points);
                break;

            case PA_REC_END_COLOR:
                char* hexColor = currNode->parameter->value.color->string;
                char* aux = (char*)_malloc(strlen(hexColor) + 1);
                strncpy(aux, hexColor, strlen(hexColor));
                currParam->value.color = aux;
                LogDebug("\t\tAdded {%d, %s}", currParam->type, currParam->value.color);
                break;

            default:
                LogError("\t\tUnknown Animation type");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tSymbol Table: Added %d parameters", HASH_COUNT(*map));

    return 0;
}

// add params to symbol table for shapes
int stAddParametersToShape(ParameterMap** map, ShapeNode* node) {
    LogDebug("\t\tSymbol Table: Add Shape [%s] parameters", stringifyShapeType(node->type));

    ParamListShapeNode* head = node->paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tSymbol Table: Found no Shape parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListShapeNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tDuplicate key found, aborting...");
            exit(EXIT_FAILURE);
        }

        currParam = (ParameterMap*)_malloc(sizeof(ParameterMap));

        currParam->type = paramType;
        switch (currParam->type) {
            case PS_S_FILL_COLOR:
            case PS_S_BORDER_COLOR:
                char* hexColor = currNode->parameter->value.color->string;
                char* aux = (char*)_malloc(strlen(hexColor) + 1);
                strncpy(aux, hexColor, strlen(hexColor));
                currParam->value.color = aux;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.color);
                break;

            case PS_S_BORDER_WIDTH:
            case PS_S_ROTATION:
            case PS_R_HEIGHT:
            case PS_R_WIDTH:
            case PS_E_X_AXIS:
            case PS_E_Y_AXIS:
            case PS_T_BASE:
            case PS_T_HEIGHT:
                currParam->value.integer = currNode->parameter->value.integer;
                LogDebug("\t\tAdded {%s, %d}", stringifyParameterType(currParam->type), currParam->value.integer);
                break;

            default:
                LogError("\t\tError unknown type D:");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tSymbol Table: Added %d parameters", HASH_COUNT(*map));

    return 0;
}

char* convertPointsToString(ParamTypePointsNode* head) {
    // Calculate the total length of the numbers
    int totalLength = 0;
    struct ParamTypePointsNode* current = head;
    while (current != NULL) {
        totalLength += snprintf(NULL, 0, "%.2f", current->floating);  // Get the length of each number
        if (current->nextPoint != NULL) {
            totalLength++;  // Add 1 for the space separator
        }
        current = current->nextPoint;
    }

    char* result = _malloc(totalLength + 1);  // Allocate memory for the result string

    // Build the string
    char* currentPosition = result;
    current = head;
    while (current != NULL) {
        int length = snprintf(currentPosition, totalLength + 1, "%.2f", current->floating);
        currentPosition += length;
        totalLength -= length;
        if (current->nextPoint != NULL) {
            *currentPosition = ' ';  // Add the space separator
            currentPosition++;
            totalLength--;
        }
        current = current->nextPoint;
    }

    *currentPosition = '\0';  // Add the null-terminator

    return result;
}