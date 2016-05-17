/*
  Nome Completo : Bruno Ferrero 
  NUSP : 3690142
*/
#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define maxV 100

int adj[maxV][maxV];
Vertex E;
int L;
static int conta, lbl[maxV];

/* ponta inicial em v e ponta final em w */
typedef struct {
    Vertex v;
    Vertex w;
} Arc;

/* representa um digrafo; V contem o numero de vertices e A contem o numero de arcos; adj e' um ponteiro para a matriz de adjacencia*/
struct digraph {
    int V;
    int A;
    int **adj;
};

typedef struct digraph *Digraph;

/* recebe dois vertices v e w e devolve um arco v-w */
Arc ARC (Vertex v, Vertex w);
/* Esta funcao devolve o endereco de um novo digrafo com 0,1,..V-1 vertices e nenhum arco*/
Digraph DIGRAPHinit (Vertex V);
/* aloca uma matrix r x c, com cada posicao contendo val */
int **MATRIXint (int r, int c, int val);
void DIGRAPHinsert (Digraph G, Vertex v, Vertex w);
void DIGRAPHshow (Digraph G);
void DIGRAPHdfs (Digraph G);
void dfsR (Digraph G, Vertex v);

int main () {
    int i;
    Vertex v, w;
    while ((scanf ("%d%d", &E, &L) == 2) && (E != 0 && L != 0)) {
        Digraph G = DIGRAPHinit (E);
        DIGRAPHshow (G); 
        printf ("  : E= %d; L=%d\n",E,L);

        for (i = 0; i < L; i++) {
            scanf ("%d%d",&v, &w);
            DIGRAPHinsert (G, v-1, w-1);
            /*printf ("%2d : %d , %d\n",i+1, v, w);*/
        }
        DIGRAPHshow (G); 
        DIGRAPHdfs (G);
        printf ("\nconta : %d\n",conta);
        for (i=0;i<E;i++)
            printf ("%d : ", lbl[i]);
        printf("\n");
        free(G);
    }
    return 0;
}


Arc ARC (Vertex v, Vertex w) {
    Arc e;
    e.v = v;
    e.w = w;
    return e;
}

Digraph DIGRAPHinit (int V) {
    Digraph G = malloc (sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint (V, V, 0);
    return G;
}

int **MATRIXint (int r, int c, int val) {
    Vertex i, j;
    int **m = malloc (r * sizeof (int *));
    for (i = 0; i < r; i++)
        m[i] = malloc (c * sizeof (int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j] = val;
    return m;
}

/* insere um arco no digrafo G */
void DIGRAPHinsert (Digraph G, Vertex v, Vertex w) { 
   if (v != w && G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++;
   }
}

void DIGRAPHdfs (Digraph G) { 
   Vertex v;
   conta = 0;
   for (v = 0; v < G->V; v++) 
      lbl[v] = -1;
   for (v = 0; v < G->V; v++)
      if (lbl[v] == -1) 
         dfsR(G, v);
}

void dfsR (Digraph G, Vertex v) { 
   Vertex w;
   int i;
    for (i=0;i<E;i++)
            printf ("%d : ", lbl[i]);
        printf("\n");

   lbl[v] = conta++; 
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] != 0) 
         if (lbl[w] == -1)
            dfsR(G, w); 
}


void DIGRAPHshow (Digraph G) { 
   Vertex v, w; 
   for (v = 0; v < G->V; v++) {
      printf("%2d:", v+1);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1) 
            printf(" %2d", w+1);
      printf("\n");
   }
}


