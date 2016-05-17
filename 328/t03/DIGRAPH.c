#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VERTEX.h"
#include "DIGRAPH.h"

/* numero maximo de vertices no digrafo */
#define maxV 1024
#define MAXLN 1024 /* Tam. de uma linha */
#define MAXP 64    /* Tam. de uma palavra */

/* Variaveis */
static int vertexID = 0;
Digraph G;    

/* 
 * essa funcao le um MakeFile e conforme vai encontrando uma nova
 * target (vertice) adiciona o no digrafo G; as dependencias de cada
 * vertice forma um arco que também vai sendo adicionado conforme 
 * vao sendo encontradas durante a leitura do MakeFile
 *
 */
Digraph DIGRAPHconstroi (FILE *MakeFile) {
    char line[MAXLN];
    Vertex v, w;
    int contComandos;
    int terminou = 0;
    int inseriu;

    /* alocando um digrafo G */
    G = DIGRAPHinit();

    if (fgets (line, MAXLN, MakeFile) == NULL)
        terminou = 1;
    while (terminou == 0) {
        int tam;
        int posLine;
        char target[MAXP];
        char dependencia[MAXP];
        char comando[MAXLN];
        if (strlen (line) == 1) {
            if (fgets (line, MAXLN, MakeFile) == NULL)
                terminou = 1;
            continue;
        }
        sscanf (line, "%s %n", target, &tam);
        if (target[strlen(target)-1] != ':') {
            printf ("ERRO: Target inválida\n");
            exit (1);
        }  
        target[strlen(target)-1] = '\0';
        posLine = tam;
        
        /* achou uma target: cria vertice */
        v = NEWvertex (vertexID, target, "");
        /* insere o vertice criado no digrafo */
        inseriu = DIGRAPHinsertV (G, v);
        /*verfica se o vertice foi inserido*/
        if (inseriu == -1) 
            vertexID++;
        else  v = NEWvertex (inseriu, target, "");

        while (sscanf (line+posLine, "%s %n", dependencia, &tam) == 1) {
            /*dependencia*/
            w = NEWvertex (vertexID, dependencia, "");                        
            /*verifica se o vertice ja está em G; caso nao esteja, insere w*/  
            inseriu = DIGRAPHinsertV (G, w);
            if (inseriu == -1) 
                vertexID++;
            else  w = NEWvertex (inseriu, dependencia, ""); 

            /*insere arco target-dependencia*/
            DIGRAPHinsertA (G, v, w);
            posLine += tam;
        }

        if (fgets (line, MAXLN, MakeFile) == NULL)
            break;
        contComandos = 0;
        while (line[0] == '\t') {
            if (contComandos == 0) {
                /*comando para uma nova target*/
                strcpy (comando, line+1);
            }
            else strcat (comando, line + 1);  /*adiciona outro comando a lista de comandos*/
            contComandos++;
            if (fgets (line, MAXLN, MakeFile) == NULL) {
                terminou = 1;
                break;
            }
        }
        comando[strlen(comando)-1] = ';';
        v = G->adj[Key(v)]->w;
        /*adiciona o comando referente ao vertice v*/
        SETcomandos(v, comando);
    }
    G->V = vertexID;
    return G;
}

/* inicializa um digrafo com maxV vertices */
Digraph DIGRAPHinit (void) {
    int i;
    G = malloc (sizeof *G);
    G->V = maxV;
    G->A = 0;
    G->adj = malloc (maxV*sizeof (link));
    for (i = 0; i < maxV; i++)
        G->adj[i] = NULL;
    return G;
}

/* insere/inicializa um vertice v no digrafo G*/
int DIGRAPHinsertV (Digraph G , Vertex v) {
    link novo;
    link p;
    int i;
    /*verifica se o vertice ja foi inserido no digrafo*/
    for (i = 0; i < Key(v); i++) {
        p = G->adj[i];
        if (p != NULL) 
            if (VERTEXcompare (v, p->w)) 
                return Key (p->w);
    }
    novo = NEW (v);   /*cria um novo nó*/
    /*printf ("Vertice: %2d: %s \n",Key(v), novo->w->nome);*/
    G->adj[Key(v)] = novo;
    return -1;
}

/* insere arco v-w */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    link novo, p;
    novo = NEW (w);
    if (Key(v) == Key(w)) 
        return;
    p =  G->adj[Key(v)];

    while (p->next != NULL) {
        p = p->next;
    }
    /*insere no final*/
    p->next = novo;
    G->A++;
}

/* recebe um digrafo G com n vértices e o imprime na
 * saida arq 
 */
void DIGRAPHprint (Digraph G, FILE *arq) {
    int v;
    link p;
    for (v = 0; v < G->V; v++) {
	    p = G->adj[v];
	    if (p->next != NULL ) {
		    fprintf (arq, "%s:", (p->w)->nome);
		    for (p = p->next; p!= NULL; p = p->next)
			    fprintf (arq, " %s", (p->w)->nome);
		    fprintf (arq, "\n");
		    fprintf (arq, "\t");
		    fprintf (arq, "%s\n", G->adj[v]->w->comandos);
	    }
    }
}

/*imprime digrafo G na saida padrao*/
void DIGRAPHshow (Digraph G) {
    int v;
    link p;
    for (v = 0; v < G->V; v++) {
        p = G->adj[v];
        printf ("%s:", (p->w)->nome);
        for (p = p->next; p!= NULL; p = p->next)
            printf (" %s", (p->w)->nome);
        printf ("\n");
        printf ("%s\n", G->adj[v]->w->comandos);
    }
}

/*-------------------------------------------------------*/
