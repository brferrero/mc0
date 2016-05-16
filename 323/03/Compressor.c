/*
 * Autor: Bruno Ferrero  
 * n.USP: 3690142  Curso: BCC
 *
 * Data: 17/06/2010
 * gcc version 4.3.2 (Debian 4.3.2-1.1)
 *
 * Compressor.c
 */



#include <stdio.h>
#include <stdlib.h>
#include "BIT.h"
#include "Compressor.h"
#define BLOCK_SIZE 4096

/* Trie node*/
typedef struct TRIEnode {
    struct TRIEnode* pai;
    struct TRIEnode* filho[2];
    int index;
} node;

/* Block allocation for nodes
 */
node* new_node() {
    static node* bad_node = NULL;
    static node* cur_node = NULL;
    if (cur_node == bad_node) {
        cur_node = (node*) malloc (BLOCK_SIZE*sizeof (node));
        if (cur_node == NULL) {
            printf ("erro no malloc\n");
            exit (1);
        }
        bad_node = cur_node + BLOCK_SIZE;
    }
    return cur_node++;
}


/* 
 * Codifica
 */
void codifica () {
    int i;
    int ci = 0;   /* current index */
    int cl = 0;   /* number of bits to encode index */
    int v;        /* bit value */
    int bit = 0;
    
    node *q;
    node *root = new_node();
    node *p = root;
    
    root->pai = root->filho[0] = root->filho[1] = NULL;
    root->index = 0;
    p = root;

    while (1) {
        if (bit != -1) 
            bit = leBIT (1);
        v = bit & 1;
        q = p->filho[v];

        if (q == NULL) {
            q = new_node ();
            q->pai = p;
            q->index = ++ci;
            q->filho[0] = q->filho[1] = NULL;
            p->filho[v] = q;

            for (i = cl-1; i >= 0; i--) {
                imprimeBIT (((p->index) & (1<<i)) >> i, 0);
            }
            imprimeBIT (v,0);
            if (bit == -1) {
                for (i = 0; i < 7; i++)
                    imprimeBIT (1, 0);
                fflush (stdout);
                break;
            }
            if (ci >> cl) 
                cl++;
            p = root;
        }
        else p = q;
    }
}

/* 
 * Decodifica
 */
typedef struct _symbol {
    int pai;
    int bit;
} symbol;

int decode_symbol (symbol *s, int ci) {
    if (s[ci].bit == -1) 
        return 0;
    if (decode_symbol (s, s[ci].pai) == -1) 
        return -1;
    return imprimeBIT (s[ci].bit, 1);
}

void decodifica() {
    int table_size=1;
    int ci = 0;
    int pi = 0;
    int bi = 0;
    int cl = 0;
    int v;
    symbol *s = malloc (table_size*sizeof (symbol));

    s[0].pai = -1;
    s[0].bit = -1;
    while (1) {
        v = leBIT (0);
        if (bi >= cl) {
            ++ci;
            if (ci >= table_size) {
                table_size *= 2;
                s = realloc(s, table_size*sizeof (symbol));
                if (s == NULL) {
                    fprintf (stderr,"Out of memory\n");
                    exit (1);
                }
            }

            s[ci].pai = pi;
            s[ci].bit = v;
            if (decode_symbol (s,ci) == -1)
                return;
            if (ci >> cl) cl++;
            pi = 0;
            bi = 0;
        }
        else {    
            pi <<= 1;
            pi |= v;  /*OR*/
            bi++;
        }
    }
}

