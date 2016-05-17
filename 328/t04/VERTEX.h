#define maxPAL 64
#define maxLN 1024
#define Key(A) (A->id)

typedef char Target[maxPAL];
typedef char Comando[maxLN];

/* meu vértice */
typedef struct vertex *Vertex;
struct vertex {
    int id;           /*identificador do vertice      */
    Target nome;      /*string contendo o campo target*/
    Comando comandos; /*string contendo os comandos   */
};

typedef struct node *link;
struct node {
    Vertex w;
    link next;
};

/* FUNCOES */
link NEW (Vertex w); /* cria um novo no */
Vertex NEWvertex (int id, Target nome, Comando comandos); /* cria um vertice com os campos passados pelos parametros */
int VERTEXcompare (Vertex v, Vertex w);
void SETcomandos (Vertex v, Comando comandos);
