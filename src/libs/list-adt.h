#ifndef _LIST_ADT_
#define _LIST_ADT_

typedef char* elemType;

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

char* next(listADT list);

void freeList(listADT list);

#endif