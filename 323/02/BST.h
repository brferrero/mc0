/********************************************************************
 *  Nome : Bruno Ferrero                             N.USP 3690142
 *  Curso: BCC                                 Disciplina: MAC 323
 *  Data : 05/2010                                     EP2 - BST's
 *  gcc version 4.3.2 (Debian 4.3.2-1.1)
 *  *****************************************************************/

#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include "Item.h"

typedef struct STnode *link;

struct STnode {
    Item item;
    int N; /* # de elementos na arvore */
    link esq, dir;
};

/*PROTOTIPOS DAS FUNCOES*/
void STinit (void);
link STnew (Item x, link esq, link dir, int n);
int STcount (void);
Item STsearch (Key v);
void STinsert (Item x); 
#endif
