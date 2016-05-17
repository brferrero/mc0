/* 0,1,..,v-1 */
#define Vertex int

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
Digraph DIGRAPHinit (int V);

/* aloca uma matrix r x c, com cada posicao contendo val */
int **MATRIXint (int r, int c, int val);
