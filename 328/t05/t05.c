/*
    Nome Completo : Bruno Ferrero 
    NUSP : 3690142
*/

#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define maxV 101
#define minCST 0

typedef struct graph *Graph;
struct graph {
    int V;
    int A;
    double **adj;
};
/*matriz de custos*/
static double cst[maxV]; 

/*fila*/
typedef Vertex Item;
static Item *q;
static int inicio, fim;

/*FILA DE PRIORIDADE*/
void PQinit (int);
int PQempty (void);
void PQinsert (Item);
Item PQdelmax (void);
void PQfree (void);

/*GRAFOS*/
Graph GRAPHinit ();
void GRAPHinsertE (Graph, Vertex, Vertex, double);
void GRAPHreset (Graph, int);
void GRAPHfree (Graph);
void dijkstra (Graph, Vertex); 
double **MATRIXdouble (int, int); 

/*********************************************************/

int main () 
{
	int m, n;
    int a, b;
    double p;
	Graph G;
	G = GRAPHinit ();
    while ((scanf ("%d", &n)) && n != 0) {
        scanf("%d", &m);
        GRAPHreset (G, n);
        while (m--) {
            scanf ("%d %d %lf", &a, &b, &p);
            GRAPHinsertE (G, a, b, p);
        }
        dijkstra (G, 1);
        printf("%2.6f percent\n", cst[n]);
    }
    GRAPHfree (G);
    return 0;
}

/************* FUNCOES QUE MANIPULAM FILAS ****************/

/*baseadas nas funcoes dadas na aula 14*/
void PQinit (int N) {
    q = (Item*)malloc (N*sizeof (Item));
    inicio = 0;
    fim = 0;
}

int PQempty () {
    return (inicio == fim);
}

void PQinsert (Item item) {
    q[fim++] = item;
}

Item PQdelmax () {
    int i, j;
    Item x;
    i = inicio;
    for (j = i+1; j < fim; j++)
        if (cst[q[i]] < cst[q[j]])
            i = j;
    x = q[i];
    fim--;
    q[i] = q[fim];
    return x;
}

void PQfree (){
    free (q);
}

/************* FUNCOES QUE MANIPULAM GRAFOS ***************/

/*matriz de custos*/
double **MATRIXdouble (int r, int c) {
    Vertex v;
    double **m;
    m = malloc (r*sizeof (double *));
    for (v = 0; v < r; v++)
        m[v] = malloc (c*sizeof (double));
    /*for (v = 0; v < r; v++)
        for (w = 0; w < c; w++)
            m[v][w] = minCST;*/
    return m;
}

/*inicializa um grafo com maxV vertices*/
Graph GRAPHinit () {
    Graph G = malloc (sizeof (G));
    G->V = 0;
    G->A = 0;
    G->adj = MATRIXdouble (maxV ,maxV);
    return G;
}

/*insere v-w e w-v de custo cst no grafo G*/
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst) {
	if (v != w) {
        /*insere v-w*/
        if (G->adj[v][w] == minCST) {
		    G->adj[v][w] = cst;
		    G->A++;
	    }
        /*insere w-v*/
	    if (G->adj[w][v] == minCST) {
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
			G->adj[v][w] = minCST;
}

/*libera memoria*/
void GRAPHfree (Graph G)
{
	int v;
	for (v = 0; v < maxV; v++)
		free (G->adj[v]);
	free (G->adj);
	free (G);
}

/*baseado no algoritmo dado na aula 14*/
void dijkstra (Graph G, Vertex s) {
    Vertex v, w;
    for (v = 2; v <= G->V; v++)
        cst[v] = 0;
    PQinit (G->V);
    cst[s] = 100.0;
    PQinsert (s);
    while (!PQempty ()) {
        v = PQdelmax ();
        for (w = 1; w <= G->V; w++)
            if (G->adj[v][w] > minCST) {
                /*achou um custo melhor*/
                if (cst[w] == minCST) {
                    cst[w] = cst[v]*G->adj[v][w]/100;
                    if (w != G->V)
                        PQinsert (w);
                }
                else
                    if (cst[w] < cst[v]*G->adj[v][w]/100)
                        cst[w] = cst[v]*G->adj[v][w]/100;
            }
    }
    PQfree ();
}
