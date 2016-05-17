/* digrafo */
typedef struct digraph *Digraph;
struct digraph {
    int V;     /*numero de vertices */
    int A;     /*numero de arcos    */
    link *adj; /*vetor de listas    */
};

/* PROTOTIPO DAS FUNCOES */
Digraph DIGRAPHinit (void); /*inicializa um digrafo com maxV vertices*/
Digraph DIGRAPHconstroi (FILE *MakeFile); /*constroi um digrafo a partir de um MakeFile*/
int DIGRAPHinsertV (Digraph G , Vertex v); /* insere/inicializa um vertice v no digrafo G*/
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w); /*insere um arco v-w no digrafo G*/
void DIGRAPHprint (Digraph G, FILE *arq); /*imprime o digrafo na saida *arq*/
void DIGRAPHshow (Digraph G); /*imprime o digrafo na saida *arq*/
