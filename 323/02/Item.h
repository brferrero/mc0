/********************************************************************
 *  Nome : Bruno Ferrero                             N.USP 3690142
 *  Curso: BCC                                 Disciplina: MAC 323
 *  Data : 05/2010                                     EP2 - BST's
 *  gcc version 4.3.2 (Debian 4.3.2-1.1)
 *  *****************************************************************/

#ifndef ITEM_H
#define ITEM_H
#define MAX_PALAVRA 90

#define compara(A,B) (strcmp(A,B))
#define Chave(A) (A->chave)

typedef char Key[MAX_PALAVRA];   /* palavra       */
typedef char Livro[MAX_PALAVRA]; /* nome do livro */

typedef struct ITEMnode *Item;
typedef struct INFOnode *Info;
typedef struct LINHAnode *Linhas;

typedef struct ITEMnode {
    Key chave;
    Info info;    /* ptr para sInfo  */
}sItem;           /* struct sItem    */

typedef struct INFOnode {
    Livro livro;  /* nome do livro   */
    Linhas linha; /* ptr para lista de linhas */ 
    Info next;    /* proxima celula  */
}sInfo;           /* struct sInfo    */

typedef struct LINHAnode {
    int linha;   /* linha numero: #  */
    Linhas next; /* proxima linha    */
}sLinhas;        /* struct sLinhas   */

/*PROTOTIPO DAS FUNCOES*/
Item newItem (Key v, Livro l, int n);
Item atualizaItem (Item x, Livro l, int n);
Linhas insertLinha (Linhas p, int n);
Info insertInfo (Info p, Livro l, int n);
Info buscaLivro (Info p, Livro l);
void insereLinha (int l, Linhas p);
void imprime (Info p);

#endif

