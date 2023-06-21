#include "list-adt.h"
#include <stdlib.h>
#include <string.h>
#include "../backend/support/logger.h"
#include "../utils/wrapper-functions.h"

typedef struct TNode {
    elemType elem;
    struct TNode* next;  // if NULL then last element
} TNode;

typedef TNode* TList;

typedef struct listCDT {
    TList first;
    TList current;
    int size;
} listCDT;

listADT newList(void) {
    return _calloc(1, sizeof(listCDT));
}

static TList addRec(TList curr, elemType elem, listADT list) {
    if (curr == NULL) {
        // If its the end of the list, we add the new element
        TList new = _calloc(1, sizeof(TNode));
        new->elem = elem;
        new->next = NULL;
        list->size += 1;

        return new;
    }

    curr->next = addRec(curr->next, elem, list);
    return curr;
}

void add(listADT list, elemType elem) {
    if (list->first == NULL) {
        // If its the first node, create node and initialize fields
        list->first = _calloc(1, sizeof(TNode));
        list->first->elem = elem;
        list->first->next = NULL;
        list->size += 1;

        return;
    }

    list->first = addRec(list->first, elem, list);

    return;
}

void toBegin(listADT list) {
    list->current = list->first;
}

int hasNext(listADT list) {
    return list->current != NULL;
}

elemType next(listADT list) {
    if (!hasNext(list)) {
        LogError("No such element exists, aborting...");
        exit(EXIT_FAILURE);
    }

    elemType elem = list->current->elem;
    list->current = list->current->next;
    return elem;
}

static void freeListRec(TList list) {
    if (list == NULL)
        return;

    freeListRec(list->next);
    free(list->elem->message);  // depending on elemType may be not necessary
    free(list->elem);           // depending on elemType may be not necessary
    free(list);
}

void freeList(listADT list) {
    freeListRec(list->first);
    free(list);
}

int getSize(listADT list) {
    return list->size;
}

// TODO: borrar!
void printList(listADT list, char* (*getFormat)(ProblemContext*)) {
    toBegin(list);
    while (hasNext(list)) {
        elemType curr = next(list);
        printf("%s", getFormat(curr));
    }
}