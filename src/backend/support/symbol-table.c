#include "symbol-table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/error-codes.h"
#include "../../utils/stringify.h"
#include "../../utils/wrapper-functions.h"
#include "logger.h"
#include "shared.h"

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
    LogDebug("Destroying symbol table...");

    HASH_ITER(hh, state.symbolTable, currSymbol, tmp) {
        HASH_DEL(state.symbolTable, currSymbol);
        free(currSymbol);
    }
    LogDebug("Memory freed...");
}

int stAddVariable(char* varname, FunctionNode* function) {
    LogDebug("\t\tSymbol Table: Add variable [%s]", varname);

    int len;
    if ((len = strlen(varname)) > VARNAME_MAX_LENGTH) {
        LogError("\t\tVariable name too long. Max length is: %d", VARNAME_MAX_LENGTH);
        LogError("\t\tAborting...");
        exit(EXIT_FAILURE);
    }

    SymbolTable* entry;
    HASH_FIND_STR(state.symbolTable, varname, entry);
    if (entry != NULL) {
        LogError("\t\tVariable [%s] redeclared, aborting...", varname);
        exit(EXIT_FAILURE);
    }

    entry = (SymbolTable*)_malloc(sizeof(SymbolTable));
    entry->id = (char*)_malloc((len + 1) * sizeof(char));  // Allocate memory for id
    strcpy(entry->id, varname);
    entry->function = function;

    HASH_ADD_STR(state.symbolTable, id, entry);

    LogDebug("\t\tSuccessfully added variable [%s]", varname);
    return 0;
}

// add params to symbol table for animations
int stAddParametersToAnimation(ParameterMap** map, ParamListAnimationNode* paramList) {
    LogDebug("\t\tAdding Animation parameters...");

    ParamListAnimationNode* head = paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tFound no parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListAnimationNode* currNode = head;

    parameter_t paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tCannot reassign parameters, aborting...");
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
                int len = strlen(currNode->parameter->value.color->string);
                char* color = (char*)_malloc(len + 1);
                strncpy(color, currNode->parameter->value.color->string, len);
                currParam->value.color = color;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.color);
                break;

            default:
                LogError("\t\tUnknown Animation type");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tAdded %d parameters", HASH_COUNT(*map));

    return 0;
}

// add params to symbol table for shapes
int stAddParametersToShape(ParameterMap** map, ParamListShapeNode* paramList) {
    LogDebug("\t\tAdding Shape parameters...");

    ParamListShapeNode* head = paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tFound no Shape parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListShapeNode* currNode = head;

    parameter_t paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tCannot reassign parameters, aborting...");
            exit(EXIT_FAILURE);
        }

        currParam = (ParameterMap*)_malloc(sizeof(ParameterMap));

        currParam->type = paramType;
        switch (currParam->type) {
            case PS_S_FILL_COLOR:
            case PS_S_BORDER_COLOR:
                int len = strlen(currNode->parameter->value.color->string);
                char* color = (char*)_malloc(len + 1);
                strncpy(color, currNode->parameter->value.color->string, len);
                currParam->value.color = color;
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
                LogError("\t\tUnknown Shape parameter");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tAdded %d parameters", HASH_COUNT(*map));

    return 0;
}

int stAddParametersToMedia(ParameterMap** map, ParamListMediaNode* paramList) {
    LogDebug("\t\tAdd Media parameters");

    ParamListMediaNode* head = paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tFound no Media parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListMediaNode* currNode = head;

    parameter_t paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tCannot reassign parameters, aborting...");
            exit(EXIT_FAILURE);
        }

        currParam = (ParameterMap*)_malloc(sizeof(ParameterMap));

        currParam->type = paramType;
        switch (currParam->type) {
            case PM_I_URL:
                int len = strlen(currNode->parameter->value.string);
                char* url = (char*)_malloc(len + 1);
                strncpy(url, currNode->parameter->value.string, len);
                currParam->value.string = url;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.string);
                break;

            default:
                LogError("\t\tUnkown Media parameter");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tAdded %d parameters", HASH_COUNT(*map));

    return 0;
}

int stAddParametersToText(ParameterMap** map, ParamListTextNode* paramList) {
    LogDebug("\t\tAdd Text parameters");

    ParamListTextNode* head = paramList;
    if (head == NULL || head->isEmpty) {
        LogDebug("\t\tFound no Text parameters");
        return 0;
    }

    ParameterMap* currParam;
    ParamListTextNode* currNode = head;

    parameter_t paramType;
    while (currNode != NULL) {
        paramType = currNode->parameter->type;

        HASH_FIND_INT(*map, &paramType, currParam);
        if (currParam != NULL) {
            LogError("\t\tCannot reassign parameters, aborting...");
            exit(EXIT_FAILURE);
        }

        currParam = (ParameterMap*)_malloc(sizeof(ParameterMap));

        currParam->type = paramType;
        int len = 0;
        char* aux;
        switch (currParam->type) {
            case PT_T_FONT_WEIGHT:
            case PT_T_FONT_WIDTH:
                currParam->value.integer = currNode->parameter->value.integer;

            case PT_T_BACKGROUND_COLOR:
                len = strlen(currNode->parameter->value.color->string);
                char* color = (char*)_malloc(len + 1);
                strncpy(color, currNode->parameter->value.color->string, len);
                currParam->value.color = color;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.color);
                break;

            case PT_T_FONT_FAMILY:
                aux = (char*)stringifyFontFamily(currNode->parameter->value.fontFamily);
                len = strlen(aux);
                char* family = (char*)_malloc(len + 1);
                strncpy(family, aux, len);
                currParam->value.string = family;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.string);
                break;

            case PT_T_FONT_STYLE:
                aux = (char*)stringifyFontStyle(currNode->parameter->value.fontStyle);
                len = strlen(aux);
                char* style = (char*)_malloc(len + 1);
                strncpy(style, aux, len);
                currParam->value.string = style;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.string);
                break;

            case PT_T_TEXT_DECORATION:
                aux = (char*)stringifyTextDecoration(currNode->parameter->value.textDecoration);
                len = strlen(aux);
                char* deco = (char*)_malloc(len + 1);
                strncpy(deco, aux, len);
                currParam->value.string = deco;
                LogDebug("\t\tAdded {%s, %s}", stringifyParameterType(currParam->type), currParam->value.string);
                break;

            default:
                LogError("\t\tUnknown Text parameter");
                free(currParam);
                exit(EXIT_FAILURE);
        }

        HASH_ADD_INT(*map, type, currParam);

        currNode = currNode->tail;
    }

    LogDebug("\t\tAdded %d parameters", HASH_COUNT(*map));

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