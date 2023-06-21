#ifndef _LIST_ADT_
#define _LIST_ADT_

#include "../utils/errors/problem-context.h"

// change accordingly
typedef ProblemContext* elemType;

typedef struct listCDT* listADT;

/* Retorna una lista vacía.
 */
listADT newList();

/* Agrega un elemento. Si ya estaba no lo agrega */
void add(listADT list, elemType elem);

/* Resetea el iterador que recorre la lista en el orden de inserción */
void toBegin(listADT list);

/* Retorna 1 si hay un elemento siguiente en el iterador que
** recorre la lista en el orden de inserción. Sino retorna 0 */
int hasNext(listADT list);

elemType next(listADT list);

void freeList(listADT list);

int getSize(listADT list);

// FIXME: borrar!!
void printList(listADT list, char* (*getFormat)(ProblemContext*));

#endif