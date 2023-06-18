#include "list-adt.h"
#include <stdlib.h>
#include <string.h>
#include "../backend/support/logger.h"
#include "../utils/wrapper-functions.h"

typedef struct TNode {
    char* elem;
    struct TNode* next;  // Apunta al siguiente elemento agregado (o a NULL si es le utlimo)
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

static TList addRec(TList curr, char* elem, listADT list) {
    if (curr == NULL) {
        // If its the end of the list, we add the new element
        TList new = _malloc(sizeof(TNode));
        new->next = NULL;

        int len = strlen(elem);
        new->elem = _calloc(len, sizeof(char));
        strcpy(new->elem, elem);

        list->size += 1;

        return new;
    }

    curr->next = addRec(curr->next, elem, list);
    return curr;
}

void add(listADT list, char* elem) {
    if (list->first == NULL) {
        // If its the first node, create node and initialize fields
        list->first = _calloc(1, sizeof(char*));

        int len = strlen(elem);
        list->first->elem = _calloc(len, sizeof(char));
        strcpy(list->first->elem, elem);

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

char* next(listADT list) {
    if (!hasNext(list)) {
        LogError("No such element exists, aborting...");
        exit(EXIT_FAILURE);
    }

    char* elem = list->current->elem;
    list->current = list->current->next;
    return elem;
}

static void freeListRec(TList list) {
    if (list == NULL)
        return;

    freeListRec(list->next);
    free(list->elem);
    free(list);
}

void freeList(listADT list) {
    freeListRec(list->first);
    free(list);
}
