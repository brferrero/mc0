/********************************************************************
 *  Nome : Bruno Ferrero                             N.USP 3690142
 *  Curso: BCC                                 Disciplina: MAC 323
 *  Data : 05/2010                                     EP2 - BST's
 *  gcc version 4.3.2 (Debian 4.3.2-1.1)
 *  *****************************************************************/

#include <string.h>
#include <stdio.h>
#include "BST.h"

static link root; /*minha BST*/

void STinit (void) {
    root = NULL;
}

/* recebe um Item e devolve um *STNode */
link STnew (Item x, link esq, link dir, int n) {
    link aux;
    aux = malloc (sizeof (struct STnode));
    aux->item = x;
    aux->N = n;
    aux->esq = esq;
    aux->dir = dir;
    return aux;
}

int STcount (void) {
    if (root == NULL)
        return 0;
    else return root->N;
}

/* busca uma chave v recursivamente */
static Item STsearchR (Key v, link r) {
    if (r == NULL)
        return NULL;
    else 
        if (compara(v, r->item->chave) == 0) /*(v == r->item->chave)*/
            return r->item;
        else
            if (compara(v, r->item->chave) < 0) /*(v < r->item->chave)*/
                return STsearchR (v, r->esq);
            else 
                return STsearchR (v, r->dir);
}

/* busca uma chave v; versao nao recursiva */
Item STsearchI (Key v) {
    link p = root;
    while (compara(v, Chave(p->item)) != 0 && p != NULL) {
        if (compara(v, Chave(p->item)) < 0)
            p = p->esq;
        else p = p->dir;
    }
    if (p == NULL)
        return NULL;
    else return p->item;
}

/* busca chave v; essa é a funcao que a passada ao cliente */
Item STsearch (Key v) {
    return STsearchR (v, root);
}

/* insercao recursiva com balanceamento */
link STinsertR (link r, Item x) {
    if (r == NULL)
        r = STnew (x, NULL, NULL, 1);
    if (1.0*rand()/RAND_MAX < 1.0/((r->N)+1))
        return STinsertR (r, x);
    else {
        Item t = r->item;
        if (compara(Chave(x),Chave(t)) < 0)
            r->esq = STinsertR (r->esq, x);
        else r->dir = STinsertR (r->dir, x);
    }
    return r;
}

/* insercao iterativa */
static void STinsertI (Item x) {
    link p, f;
    Key v;
    strcpy (v, Chave(x));
    if (root == NULL)
        root = STnew (x, NULL, NULL, 1);
    else {
        f = root;
        while (f != NULL) {
            p = f;
            if (compara(v,Chave(f->item)) < 0)
                f = f->esq;
            else f = f->dir;
            (p->N)++;
        }
        f = STnew (x, NULL, NULL, 1);
        if (compara(v,Chave(p->item)) < 0)
            p->esq = f;
        else p->dir = f;
    }
}

/* insercao; essa é a função que é passada ao cliente */
void STinsert (Item x) {
    STinsertI (x);
}

