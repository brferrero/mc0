/*
    Nome Completo : Bruno Ferrero 
    NUSP : 3690142
*/

#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define maxV 101
#define INFINITO 999

typedef struct graph *Graph;
struct graph {
    int V;
    int A;
    int **adj;
};

/*GRAFOS*/
Graph GRAPHinit ();
void GRAPHinsertE (Graph, Vertex, Vertex, int);
void GRAPHreset (Graph, int);
void GRAPHfree (Graph);
void GRAPHmspP1 (Graph G, Vertex parnt[]);
int **MATRIXint (int, int); 

/*********************************************************/

int main () 
{
	int m, n;
    int a, b;
    int c;
    int testes = 1;
    Vertex parnt[maxV];

	Graph G;
	G = GRAPHinit ();
    while ((scanf ("%d", &n)) && n != 0) {
        scanf("%d", &m);
        GRAPHreset (G, n);
        while (m--) {
            scanf ("%d %d %d", &a, &b, &c);
            GRAPHinsertE (G, a, b, c);
        }
        printf ("Teste %d\n", testes++);
        GRAPHmspP1 (G, parnt); 
        printf ("\n");

    }
    GRAPHfree (G);
    return 0;
}

/************* FUNCOES QUE MANIPULAM GRAFOS ***************/

/*matriz de custos*/
int **MATRIXint (int r, int c) {
    Vertex v;
    int **m;
    m = malloc (r*sizeof (int *));
    for (v = 0; v < r; v++)
        m[v] = malloc (c*sizeof (int));
    return m;
}

/*inicializa um grafo com maxV vertices*/
Graph GRAPHinit () {
    Graph G = malloc (sizeof (G));
    G->V = 0;
    G->A = 0;
    G->adj = MATRIXint (maxV ,maxV);
    return G;
}

/*insere v-w e w-v de custo cst no grafo G*/
void GRAPHinsertE (Graph G, Vertex v, Vertex w, int cst) {
	if (v != w) {
        /*insere v-w*/
        if (G->adj[v][w] == INFINITO) {
		    G->adj[v][w] = cst;
		    G->A++;
	    }
        /*insere w-v*/
	    if (G->adj[w][v] == INFINITO) {
		    G->adj[w][v] = cst;
		    G->A++;
	    }
    }
}

/* zera matrix de custos e seta o numero de 
   vertices e arcos do grafo G
 */
void GRAPHreset (Graph G, int n) {
	Vertex v, w;
	G->V = n;
	G->A = 0;
	for (v = 1; v <= n; v++)
		for (w = 1; w <= n; w++)
			G->adj[v][w] = INFINITO;
}

/*libera memoria*/
void GRAPHfree (Graph G) {
	int v;
	for (v = 0; v < maxV; v++)
		free (G->adj[v]);
	free (G->adj);
	free (G);
}

/*algoritmo de Prim eficiente*/
/*algoritmo visto na aula 21*/
void GRAPHmspP1 (Graph G, Vertex parnt[]) {
    int cst[maxV]; 
    int mincst;
    Vertex v, w;
    Vertex fr[maxV];
    for (v = 1; v <= G->V; v++) {
        parnt[v] = -1;
        cst[v] = INFINITO;
    }
    v = 1;
    fr[v] = v;
    cst[v] = 0;
    while (1) {
        mincst = INFINITO;
        for (w = 1; w <= G->V; w++)
            if (parnt[w] == -1 && mincst > cst[w])
                mincst = cst[v=w];
        if (mincst == INFINITO) break;
        parnt[v] = fr[v];
        /*imprime arestas da mst*/
        if (parnt[v] != v) {
            if (parnt[v] < v)    
                printf("%d %d\n", parnt[v], v);
            else printf("%d %d\n", v, parnt[v]);
        }
        for (w = 1; w <= G->V; w++)
            if (parnt[w] == -1 && G->adj[v][w] < cst[w]) {
                cst[w] = G->adj[v][w];
                fr[w] = v;
            }
    }
}
