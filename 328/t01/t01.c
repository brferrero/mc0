/*
   Nome Completo : Bruno Ferrero 
   NUSP : 3690142
   MESA
 */

#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define maxV 101

typedef struct graph *Graph;
struct graph {
	int V;
	int E;
	int adj[maxV][maxV];
};

static int color[maxV];

/*FUNCOES*/
Graph GRAPHinit ();
void GRAPHinsertE (Graph, Vertex, Vertex);
void GRAPHreset (Graph, int);
void GRAPHfree (Graph);
int GRAPHtwocolor (Graph G); 
int dfsRclr (Graph G, Vertex v, int c); 

/*********************************************************/

int main () 
{
	int m, n;
	int a, b;
	int twocolor;
	int instancia = 0;
	Graph G;

	G = GRAPHinit ();
	while (scanf ("%d %d", &n , &m) == 2) {
		GRAPHreset (G, n);
		while (m--) {
			scanf ("%d %d", &a, &b);
			GRAPHinsertE (G, a, b);
		}
		twocolor = GRAPHtwocolor (G);
		instancia++;
		if (twocolor)
			printf("Instancia %d\n%s\n\n", instancia, "sim");
		else   
			printf("Instancia %d\n%s\n\n", instancia, "nao");  

	}
	GRAPHfree (G); 
	return 0;
}

/************* FUNCOES QUE MANIPULAM GRAFOS ***************/

/*inicializa um grafo com maxV vertices*/
Graph GRAPHinit () {
	Graph G = malloc (sizeof (G));
	G->V = 0;
	G->E = 0;
	return G;
}

/* zera matrix de custos e seta o numero de 
   vertices e arcos do grafo G
 */
void GRAPHreset (Graph G, int n) {
	Vertex v, w;
	G->V = n;
	G->E = 0;
	for (v = 1; v <= n; v++)
		for (w = 1; w <= n; w++)
			G->adj[v][w] = 0;
}

/*insere v-w e w-v de no grafo G*/
void GRAPHinsertE (Graph G, Vertex v, Vertex w) {
	if (v != w) 
		/*insere v-w e w-v*/
		if (G->adj[v][w] == 0) {
			G->adj[v][w] = 1;
			G->adj[w][v] = 1;
			G->E++;
		}
}

/*libera memoria*/
void GRAPHfree (Graph G) {
	free (G);
}


/*verifica se o grafo é bipartido - Busca em profundidade*/
int GRAPHtwocolor (Graph G) { 
	Vertex v;
	for (v = 1; v <= G->V; v++) 
		color[v] = -1;
	for (v = 1; v <= G->V; v++) {
		if (color[v] == -1) 
			if (dfsRclr(G, v, 0) == 0) 
				return 0;
	}
	return 1;
}

/*DFS*/
int dfsRclr (Graph G, Vertex v, int c) { 
	Vertex w; 
	color[v] = 1-c;
	for (w = 1; w <= G->V; w++)  
		if (G->adj[v][w] == 1) { 
			if (color[w] == -1) {
				if (dfsRclr(G, w, 1-c) == 0) 
					return 0; 
			}
			else if (color[w] == color[v]) 
				return 0;
		}
	return 1;
}
