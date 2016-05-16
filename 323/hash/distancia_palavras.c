#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*                       DISTANCIA ENTRE PALAVRAS                  */
/* O programa recebe um dicionario  de palavras e para cada par de */
/* palavras desejados, encontra um caminho de custo minimo formado */
/* de palavras vizinhas. Palavras vizinhas sao aquelas em que uma  */
/* se transforma na outra atraves da remocao, insersao ou          */
/* substituicao de uma letra                                       */

/* PROTOTIPO DAS FUNCOES */
void insere_lista(char palavra[]);
void imprime();
void procura_vizinho(char palavra[], int k);

/* DECLARACAO DE VARIAVEIS */
typedef struct nome* apontador;

struct nome {
  char info[27];
  int custo;
  apontador prox;
  apontador vizinho;
};

apontador hash[676];

/* PROGRAMA PRINCIPAL */
int main () {
  int n, i, j;
  char palavra[27];
  for (i = 0; i < 676; i++) {
    hash[i] =(apontador) malloc(sizeof(struct nome));
    hash[i] = NULL;
  }
  scanf ("%d", &n);
  for (i = 0; i < n; i++) {
    scanf ("%s", &palavra);
    for (j = 0; palavra[j] != '\0'; j++) {}
    insere_lista(palavra);
    procura_vizinho(palavra, j);
    printf ("TERMINOU\n");
  }
  imprime();
}

/* Funcao que recebe uma palavra e coloca na lista */
/* de hash em funcao das duas primeiras letras da  */
/* palavra, segundo a seguinte funcao:             */
/* (primeira - 'a') * 26 + (segunda - 'a')         */

/* STRCMP (str1, str2) devolve <0 se str1 é menor  */
/* que str2, >0 se str1 é maior que str2, e 0 se   */ 
/* forem iguais                                    */

void insere_lista(char palavra[])
{
 int a;
  apontador novo, t, ant;
  a = (palavra[0] - 'a')*26 + (palavra[1] - 'a');
  novo = (apontador)malloc(sizeof(struct nome));
  strcpy(novo->info, palavra);
  novo->prox = NULL;
  novo->vizinho = NULL;
  novo->custo = 0;
  if (hash[a] == NULL) {
    hash[a] = novo;
  }
  else {
    t = hash[a];
    while (t != NULL && strcmp(palavra, t->info) > 0) {
      ant = t;
      t = t->prox;
    }
    if (t == NULL)
      ant->prox = novo;
    else{
      if (t == hash[a]) {
	novo->prox = hash[a];
	hash[a] = novo;
      }
      else {
	ant->prox = novo;
	novo->prox = t;
      }
    }
  }
}

void imprime()
{
  int i;
  apontador t;
  for (i = 0; i < 676; i++) {
    for (t = hash[i]; t != NULL; t = t->prox) {
      printf ("%d: %s\n", i, t->info);
    }
  }
}

void procura_vizinho(char palavra[], int k)
{
  int i, j, m, a;
  char nova[27];
  apontador novo, t;
  strcpy(nova, palavra);
  for(i = 0; i < k; i++) {
    printf("primeiro   ");
    for (j = 'a'; j <= 'z'; j++) {
      printf("segundo   ");
      if (palavra[i] != j) {
	printf ("---%d--- ", j);
	nova[i] = j;
	/*procura no hash*/
	a = (nova[0] - 'a') * 26 + (nova[1] - 'a');
	t = hash[a];
	while (t != NULL) {
	  printf("meio  ");
	  if (!strcmp(t->info, nova)) {
	    novo = (apontador)malloc(sizeof(struct nome));
	    strcpy(novo->info, palavra);
	    novo->prox = NULL;
	    novo->vizinho = NULL;
	    t->vizinho = novo;
	    printf ("achou");
	    break;
	  }
	  else t = t->prox;
	}
      }
    }
  }
  for(i = 0; i < k; i++) {
    printf ("quarto  ");
    for (j = 0, m = 0; m < k; j++, m++) {
      printf ("quinto  ");
      if (m != i)
	nova[j] = palavra [m];
	else 
	  j--;
    }
	a = (nova[0] - 'a') * 26 + (nova[1] - 'a');
	t = hash[a];
	while (t != NULL) {
	  if (!strcmp(t->info, nova)) {
	    novo = (apontador)malloc(sizeof(struct nome));
	    strcpy(novo->info, palavra);
	    novo->prox = NULL;
	    novo->vizinho = NULL;
	    t->vizinho = novo;
      }
    }
  }
}


/* int procura_caminho(char palav1[], char palav2[]) */
/* { */
/* coloca na fila de prioridade */
/*   novo = (link)malloc(strcut fila); */
/*  strcpy(novo->info, palav1); */
/*  novo->ordem = 0; */
/*  novo->custo = 0; */
/*  t = fila; */
/*  while (t != NULL) { //enquanto fila nao acaba */
/* pega primeiro da fila */
/* guarda ordem e custo */
/*   q = hash[a]->vizinho; */
/*  while (q != NULL) {//enquanto tem vizinhos */
/* pega vizinho */
/*   for (p = fila; p != NULL && strcmp(p->info, vizinho->info) != 0; p = p->prox)//procura na fila */
/*     if (p == NULL) { */
/*  novo = (link)malloc(strcut fila); */
/*  strcpy(novo->info, vizinho->info); */
/*  novo->ordem = ordem + 1; */
/*  novo->custo = custo + vizinho->custo; */
/*     } */
/*     else {//se estiver */
/*       if (p->custo > vizinho->custo) {//verifica custo se for maior */
/* tira e coloca na nova posicao */
