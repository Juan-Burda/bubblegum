#include "symbol-table.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../utils/error-codes.h"
#include "../../utils/wrapper-functions.h"
#include "logger.h"
#include "shared.h"

//
int stAddParametersToShapeRectangle(ParameterMap** map, ParamListRectangleNode* head);
int stAddParametersToShapeEllipse(ParameterMap** map, ParamListEllipseNode* head);
int stAddParametersToShapeTriangle(ParameterMap** map, ParamListTriangleNode* head);

int stAddParametersToAnimationTranslate(ParameterMap** map, ParamListTranslateNode* head);
int stAddParametersToAnimationOpacity(ParameterMap** map, ParamListOpacityNode* head);
int stAddParametersToAnimationRotate(ParameterMap** map, ParamListRotateNode* head);

void stDestroyParameters(ParameterMap* parameters);
//

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

// TODO: variables anonimas? tipo si no le asignas ningun valor a la variable que pasa
// TODO: no abortar por key duplicada
int stAddParametersToShape(ParameterMap** map, ShapeNode* node) {
    switch (node->type) {
        case S_RECTANGLE:
            stAddParametersToShapeRectangle(map, node->value.rectangleParamList);
            break;

        case S_ELLIPSE:
            stAddParametersToShapeEllipse(map, node->value.ellipseParamList);
            break;

        case S_TRIANGLE:
            stAddParametersToShapeTriangle(map, node->value.triangleParamList);
            break;

        default:
            LogError("Unknown shape type");
            exit(EXIT_FAILURE);
    }
    return 0;
}

int stAddParametersToAnimation(ParameterMap** map, AnimationNode* node) {
    switch (node->type) {
        case A_TRANSLATE_X:
        case A_TRANSLATE_Y:
            stAddParametersToAnimationTranslate(map, node->value.translateParamList);
            break;

        case A_OPACITY:
            stAddParametersToAnimationOpacity(map, node->value.opacityParamList);
            break;

        case A_ROTATE:
            stAddParametersToAnimationRotate(map, node->value.rotateParamList);
            break;

        default:
            break;
    }
}

// add parameters to specific animations
int stAddParametersToAnimationTranslate(ParameterMap** map, ParamListTranslateNode* head) {
    if (head == NULL || head->type == PLA_T_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Animation parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Animation parameters");
    ParameterMap* currParam;
    ParamListTranslateNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLA_T_ANIMATION ? currNode->value.animationNode->type : currNode->value.translateNode->type;

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
                currParam->value.boolean = currNode->value.animationNode->value.loop;
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.boolean);
                break;

            case PA_A_DELAY:
            case PA_A_DURATION:
            case PA_T_END_VALUE:
                currParam->value.integer = (currNode->type == PLA_T_ANIMATION ? currNode->value.animationNode->value.delay : currNode->value.translateNode->value.endValue);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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

int stAddParametersToAnimationOpacity(ParameterMap** map, ParamListOpacityNode* head) {
    if (head == NULL || head->type == PLA_O_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Animation parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Animation parameters");
    ParameterMap* currParam;
    ParamListOpacityNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLA_O_ANIMATION ? currNode->value.animationNode->type : currNode->value.opacityNode->type;

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
                currParam->value.boolean = currNode->value.animationNode->value.loop;
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.boolean);
                break;

            case PA_A_DELAY:
            case PA_A_DURATION:
            case PA_O_ALPHA:
                currParam->value.integer = (currNode->type == PLA_T_ANIMATION ? currNode->value.animationNode->value.delay : currNode->value.opacityNode->value.alpha);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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

int stAddParametersToAnimationRotate(ParameterMap** map, ParamListRotateNode* head) {
    if (head == NULL || head->type == PLA_R_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Animation parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Animation parameters");
    ParameterMap* currParam;
    ParamListRotateNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLA_R_ANIMATION ? currNode->value.animationNode->type : currNode->value.rotateNode->type;

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
                currParam->value.boolean = currNode->value.animationNode->value.loop;
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.boolean);
                break;

            case PA_A_DELAY:
            case PA_A_DURATION:
            case PA_R_ANGLE:
                currParam->value.integer = (currNode->type == PLA_T_ANIMATION ? currNode->value.animationNode->value.delay : currNode->value.rotateNode->value.angle);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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

// add parameters to specific shapes
int stAddParametersToShapeRectangle(ParameterMap** map, ParamListRectangleNode* head) {
    if (head == NULL || head->type == PLS_R_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Rectangle parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Rectangle parameters");
    ParameterMap* currParam;
    ParamListRectangleNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLS_R_SHAPE ? currNode->value.shapeNode->type : currNode->value.rectangleNode->type;

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
                char* hexColor = currNode->value.shapeNode->value.borderColor->typeColor;
                char* aux = (char*)_malloc(strlen(hexColor) + 1);
                strncpy(aux, hexColor, strlen(hexColor));
                currParam->value.color = aux;
                LogDebug("\t\tAdded {%d, %s}", currParam->type, currParam->value.color);
                break;

            case PS_S_BORDER_WIDTH:
            case PS_S_ROTATION:
            case PS_R_HEIGHT:
            case PS_R_WIDTH:
                currParam->value.integer = (currNode->type == PLS_R_SHAPE ? currNode->value.shapeNode->value.rotation : currNode->value.rectangleNode->value.height);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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

int stAddParametersToShapeEllipse(ParameterMap** map, ParamListEllipseNode* head) {
    if (head == NULL || head->type == PLS_E_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Ellipse parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Ellipse parameters");
    ParameterMap* currParam;
    ParamListEllipseNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLS_E_SHAPE ? currNode->value.shapeNode->type : currNode->value.ellipseNode->type;
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
                char* hexColor = currNode->value.shapeNode->value.borderColor->typeColor;
                char* aux = (char*)_malloc(strlen(hexColor) + 1);
                strncpy(aux, hexColor, strlen(hexColor));
                currParam->value.color = aux;
                LogDebug("\t\tAdded {%d, %s}", currParam->type, currParam->value.color);
                break;

            case PS_S_BORDER_WIDTH:
            case PS_S_ROTATION:
            case PS_E_X_AXIS:
            case PS_E_Y_AXIS:
                currParam->value.integer = (currNode->type == PLS_E_SHAPE ? currNode->value.shapeNode->value.rotation : currNode->value.ellipseNode->value.xAxis);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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

int stAddParametersToShapeTriangle(ParameterMap** map, ParamListTriangleNode* head) {
    if (head == NULL || head->type == PLS_T_EMPTY) {
        LogDebug("\t\tSymbol Table: Found no Triangle parameters");
        return 0;
    }

    LogDebug("\t\tSymbol Table: Add Triangle parameters");
    ParameterMap* currParam;
    ParamListTriangleNode* currNode = head;

    ParameterType paramType;
    while (currNode != NULL) {
        paramType = currNode->type == PLS_T_SHAPE ? currNode->value.shapeNode->type : currNode->value.triangleNode->type;
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
                char* hexColor = currNode->value.shapeNode->value.borderColor->typeColor;
                char* aux = (char*)_malloc(strlen(hexColor) + 1);
                strncpy(aux, hexColor, strlen(hexColor));
                currParam->value.color = aux;
                LogDebug("\t\tAdded {%d, %s}", currParam->type, currParam->value.color);
                break;

            case PS_S_BORDER_WIDTH:
            case PS_S_ROTATION:
            case PS_T_BASE:
            case PS_T_HEIGHT:
                currParam->value.integer = (currNode->type == PLS_T_SHAPE ? currNode->value.shapeNode->value.rotation : currNode->value.triangleNode->value.base);
                LogDebug("\t\tAdded {%d, %d}", currParam->type, currParam->value.integer);
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