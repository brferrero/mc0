/* 
   Problema do ratinho: Dada um labirinto e duas posi��es especiais do
   labirinto, uma do ratinho e uma do queijo, queremos determinar o 
   caminho mais curto no labirinto (se houver um) para o ratinho chegar 
   ao queijo. 

   O labirinto � dado por uma matriz com 0's e -1's. Os -1's representam 
   posi��es pretas do labirinto, por onde n�o se pode andar, e os 0's, 
   posi��es livres. Tanto a posi��o inicial do ratinho quanto a posi��o 
   do queijo devem ser posi��es livres do labirinto.

   A sa�da deste programa � um caminho m�nimo no labirinto do ratinho 
   at� o queijo (ou seja, uma seq��ncia de posi��es livres do labirinto 
   que descreve um tal caminho). 
*/

#include <stdio.h>

#define max 100

#define false 0
#define true 1

#define boolean int

typedef struct {
  int x, y;
} posicao;

/* Declara��o dos tipos da fila */

typedef posicao elemento;

typedef struct {
  elemento f[max];
  int inicio, fim;
} fila;

/* Fun��es de manipula��o da fila */

void cria_fila (fila *F) {
  /* Inicializa F como uma fila vazia */
  F->inicio = 0;
  F->fim = 0;
}

boolean fila_vazia (fila *F) {
  /* Verifica se a fila F est� ou n�o vazia */
  return (F->inicio == F->fim);
}

boolean fila_cheia (fila *F) {
  /* Verifica se a fila F est� ou n�o cheia */
  return (F->inicio == (F->fim + 1) % max);
}

void insere_fila (fila *F, elemento x) {
  /* Insere x no fim da fila F, caso est� j� n�o esteja cheia */
  if (fila_cheia(F)) {
    printf("Erro: overflow!\n");
    exit(1);
  }
  else {
    F->fim = (F->fim + 1) % max;
    F->f[F->fim] = x;
  }
}

void remove_fila (fila *F) {
  /* Remove o primeiro da fila F, caso F n�o esteja vazia */
  if (fila_vazia(F)) {
    printf("Erro: underflow!\n");
    exit(2);
  }
  else 
    F->inicio = (F->inicio + 1) % max;
}

elemento primeiro_fila (fila *F) {
  /* Retorna o primeiro da fila F, caso F n�o esteja vazia */
  if (fila_vazia(F)) {
    printf("Erro: underflow!\n");
    exit(2);
  }
  else 
    return (F->f[(F->inicio + 1) % max]);
}

void imprime_labirinto(int L[][max], int m, int n) {
  int i, j;

  printf("\n");
  for (i=1; i<=m; i++) {
    for (j=1; j<=n; j++)
      if (L[i][j] == -1)
	printf("    ");
      else 
	printf("%3d ", L[i][j]);
	/*
      if (L[i][j] == -1)
	printf(" x ");
      else
	printf(" . ");
	*/
    printf("\n");
  }
  printf("\n");
}

void marca_vizinhos(int L[][max], posicao p, fila *F) {
  /* Marca cada um dos vizinhos da posi��o p que ainda 
     � livre com um a mais que o r�tulo da posi��o p.  */
  posicao aux;

  if (L[p.x+1][p.y] == -2) {
    /* Se a posi��o � livre e n�o est� marcada,
       marca e insere no fim da fila. */
    L[p.x+1][p.y] = L[p.x][p.y] + 1;
    aux.x = p.x+1;
    aux.y = p.y;
    insere_fila(F, aux);
  } 
  if (L[p.x-1][p.y] == -2) {
    L[p.x-1][p.y] = L[p.x][p.y] + 1;
    aux.x = p.x-1;
    aux.y = p.y;
    insere_fila(F, aux);
  } 
  if (L[p.x][p.y+1] == -2) {
    L[p.x][p.y+1] = L[p.x][p.y] + 1;
    aux.x = p.x;
    aux.y = p.y+1;
    insere_fila(F, aux);
  } 
  if (L[p.x][p.y-1] == -2) { 
    L[p.x][p.y-1] = L[p.x][p.y] + 1;
    aux.x = p.x;
    aux.y = p.y-1;
    insere_fila(F, aux);
  } 
}

void limpa_labirinto(int L[][max], int m, int n) {
  /* Coloca -2 em todas as posi��es livre, 
     significando que nenhuma delas est� marcada. */
  int i, j;

  for (i=1; i<=m; i++) 
    for (j=1; j<=n; j++)
      if (L[i][j] != -1)
	L[i][j] = -2;
}

void marca_labirinto(int L[][max], int m, int n, posicao p) {
  /* Marca o labirinto com a dist�ncia m�nima para 
     chegar a cada posi��o a partir da posi��o p   */
  fila F;
  posicao q;
  
  cria_fila(&F);
  limpa_labirinto(L, m, n);

  /* Come�a da posi��o p */
  L[p.x][p.y] = 0;
  insere_fila(&F, p);

  while (!fila_vazia(&F)) {
    q = primeiro_fila(&F);
    marca_vizinhos(L, q, &F);
    remove_fila(&F);
  }
}

posicao anterior(int L[][max], posicao p) {
  posicao aux;

  if (L[p.x+1][p.y] == L[p.x][p.y] - 1) {
    aux.x = p.x+1;
    aux.y = p.y;
  }
  else if (L[p.x-1][p.y] == L[p.x][p.y] - 1) {
    aux.x = p.x-1;
    aux.y = p.y;
  } 
  if (L[p.x][p.y+1] == L[p.x][p.y] - 1) {
    aux.x = p.x;
    aux.y = p.y+1;
  } 
  if (L[p.x][p.y-1] == L[p.x][p.y] - 1) { 
    aux.x = p.x;
    aux.y = p.y-1;
  } 
  return (aux);
}

void determina_caminho(int L[][max], int m, int n, posicao p) {
  /* Dado um labirinto marcado com as dist�ncias m�nimas a partir 
     de uma posi��o inicial (determinada por ter dist�ncia m�nima 
     zero), determina o caminho m�nino de p � posi��o inicial  */
  posicao q;

  if (L[p.x][p.y] == -2)
    printf("N�o h� caminho.\n\n");
  else {
    q = p;
    printf("\nCaminho:\n");
    while (L[q.x][q.y] != 0) {
      printf("(%d,%d)\n", q.x, q.y);
      q = anterior(L, q);
    }
    printf("(%d,%d)\n\n", q.x, q.y); 
  }
}

main() {
  FILE *entrada;
  char nome[max], resp;

  int n, m,            /* Dimens�es do labirinto           */
      L[max][max],     /* Matriz representando o labirinto */
      i, j,
      fora; 
      posicao rato,    /* Posi��o do ratinho */
              queijo;  /* Posi��o do queijo  */

  printf("\nDigite o nome do arquivo com o labirinto: ");
  gets(nome);
  if ((entrada = fopen(nome, "r")) == NULL) {
    printf("Erro: problemas na leitura do arquivo %s.\n", nome);
    exit(3);
  }

  /* Leitura do labirinto e constru��o da moldura */
  fscanf(entrada, "%d %d ", &m, &n);
  for (i=1; i<=m; i++) {
    L[i][0] = -1;
    for (j=1; j<=n; j++)
      fscanf(entrada, "%d ", &L[i][j]);
    L[i][n+1] = -1;
  }
  for (j=1; j<=n; j++) {
    L[0][j]   = -1;
    L[n+1][j] = -1;
  }
  fclose(entrada);

  printf("\nO labirinto (0 indica posi��o livre) \n");
  imprime_labirinto(L, m, n);

  do {
    do {
      printf("Digite a posi��o do ratinho: ");
      scanf("%d%d", &rato.x, &rato.y);
      fora = (rato.x <= 0 || rato.x > m || rato.y <= 0 || rato.y > n);
      if (fora || L[rato.x][rato.y] == -1) 
	printf("Posi��o invalida!\n");
    } while (fora || L[rato.x][rato.y] == -1);
    printf("O ratinho est� em (%d,%d).\n", rato.x, rato.y);
    do {
      printf("Digite a posi��o do queijo: ");
      scanf("%d%d", &queijo.x, &queijo.y);
      fora = (queijo.x <= 0 || queijo.x > m || queijo.y <= 0 || queijo.y > n);
      if (fora || L[queijo.x][queijo.y] == -1) 
	printf("Posi��o invalida!\n");
    } while (fora || L[queijo.x][queijo.y] == -1);
    printf("O queijo est� em (%d,%d).\n", queijo.x, queijo.y);
    marca_labirinto(L, m, n, queijo);

    printf("\nO labirinto marcado com as dist�ncias \n");
    imprime_labirinto(L, m, n);

    determina_caminho(L, m, n, rato);
    printf("Tenta novamente? (S/N) ");
    scanf(" %c", &resp);
  } while (resp == 's' || resp == 'S');
}

