#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLIN 20
#define MAXCOL 22
#define MAXNOME 31 
#define NUM_TIROS 3

/* PROTOTIPO DAS FUNCOES */
void leia_ate_fim_linha (FILE *arq);
void leia_mapa (int *plin, int *pcol, char mapa[][MAXCOL]);
void escreva_mapa_tela (char mapa[][MAXCOL], int nlin, int ncol);
void escreva_mapa_arquivo (FILE *arq, char mapa[][MAXCOL], int nlin, int ncol);
int coluna_inicial_barco (char mapa[][MAXCOL], int ncol);

int rema_barco (int *plin, int *pcol, char mapa[][MAXCOL]);
int num_aleatorio (int k);
int dispara_tiros(char mapa[][MAXCOL], int nlin, int ncol);

/* PROGRAMA */
int main ()
{
  FILE *arq;
  int lin, col, a, b, lin_atual, col_atual, jogada;
  char arq_saida[MAXNOME], mapa_info[MAXLIN][MAXCOL];
  lin_atual = 1;
  a = b = 1;
  jogada = 1;
  printf ("Entre com o nome do arquivo de saida : ");
  scanf (" %s", arq_saida);
  arq = fopen (arq_saida, "w");
  srand ((unsigned int) time(NULL));
  leia_mapa (&lin, &col, mapa_info);
  escreva_mapa_arquivo (arq, mapa_info,lin,col);
  escreva_mapa_tela(mapa_info,lin,col);
  col_atual = coluna_inicial_barco(mapa_info,col);
  escreva_mapa_tela(mapa_info,lin,col);
  /* LOOP DAS JOGADAS */
  while (lin_atual < lin && a && b) {
    printf ("\n");
    printf ("Jogada %d \n",jogada);
    b = dispara_tiros (mapa_info,lin,col);
    escreva_mapa_tela(mapa_info,lin,col);
    mapa_info[lin_atual][col_atual] = '.';
    a = rema_barco (&lin_atual, &col_atual, mapa_info);
    mapa_info[lin_atual][col_atual] = 'B';
    jogada = jogada + 1;
  }
  if (a && b) 
    printf ("GANHOU O JOGO.\n");
  else printf ("PERDEU O JOGO HAHAHA.\n");
  fclose(arq);
  return 0;
}

/* FUNCOES */

/* essa funcao e' utilizada para garantir que uma linha foi lida ate o fim */
void leia_ate_fim_linha (FILE *arq) {
  char carac;
  fscanf (arq, "%c",&carac);
  while (carac != '\n')
    fscanf (arq, "%c",&carac); 
}
/* LE O ARQUIVO DE ENTRADA */
void leia_mapa (int *plin, int *pcol, char mapa[][MAXCOL])
{
  FILE *arqentrada;
  char nomearq[MAXNOME];
  int nlin, ncol, i, j;
  printf ("Digite o nome (maximo %d caracteres) do arquivo de entrada :\n", MAXNOME-1);
  scanf ("%s", nomearq);
  arqentrada = fopen (nomearq, "r");
  if (arqentrada == NULL) {
    printf ("ERRO: nao foi possivel abrir arquivo %s\n", nomearq);
    exit (-1);
  }
  /* ... */
  fscanf (arqentrada, "%d %d", &nlin, &ncol);
  printf("%d %d\n", nlin,ncol);
  leia_ate_fim_linha (arqentrada);
  /* ... */
  for (i = 1; i <= nlin; i++)    {
    for (j = 1; j <= ncol; j++)
      fscanf (arqentrada, "%c", &mapa[i][j]);
    leia_ate_fim_linha (arqentrada);
  }
  *plin = nlin;
  *pcol = ncol;
  fclose (arqentrada);
  /* ... */
}

/* ESCREVE CADA JOGADA NA TELA */
void escreva_mapa_tela (char mapa[][MAXCOL], int nlin, int ncol) 
{
  int i, j;
  printf("    ");
  for (j = 1; j <= ncol; j++)
    printf("%2d  ",j);
  printf("\n");
  for (i = 1; i <= nlin; i++) {
    printf("%2d |", i);
    for (j = 1; j <= ncol; j++) {
      if (mapa[i][j] == 'B' || mapa[i][j] == '*')
	printf (" %c |", mapa[i][j]);
      else printf (" %c |", '.');
    }
    printf("\n");
    printf("   +");
    for (j = 0; j < ncol; j++) 
      printf("---+");
    printf("\n");
  }
}

/* ESCREVE O MAPA ORIGINAL NO ARQUIVO */
void escreva_mapa_arquivo (FILE *arq, char mapa[][MAXCOL], int nlin, int ncol) 
{
  int i, j;
  fprintf(arq,"    ");
  for (j = 1; j <= ncol; j++)
    fprintf(arq,"%2d  ",j);
  fprintf(arq,"\n");
  for (i = 1; i <= nlin; i++) {
    fprintf(arq,"%2d |", i);
    for (j = 1; j <= ncol; j++) 
      fprintf(arq," %c |",mapa[i][j]);
    fprintf(arq,"\n");
    fprintf(arq,"   +");
    for (j = 1; j <= ncol; j++) 
      fprintf(arq,"---+");
    fprintf(arq,"\n");
  }
}

/* PRIMEIRA JOGADA */
int coluna_inicial_barco (char mapa[][MAXCOL], int ncol)
{
  int inicio;
  printf ("Entre com a posicao inicial(coluna) do barco : ");
  scanf ("%d",&inicio);
  while (inicio > ncol || mapa[1][inicio] != '-') {
    printf ("POSICAO INVALIDA: Entre com outra posicao :");
    scanf ("%d",&inicio);
  }
  mapa[1][inicio] = 'B';
  return inicio; 
} 

/* FUNCAO PRA MOVIMENTAR O BARCO */
int rema_barco (int *plin, int *pcol, char mapa[][MAXCOL])
{
  char movimento;
  printf ("Movimento do barco : baixo [b] , esquerda [e], direita [d] : ");
  scanf (" %c",&movimento);
  if (movimento == 'b') 
    *plin = *plin + 1;
  else {
    if (movimento == 'e')
      *pcol = *pcol - 1;
    else *pcol = *pcol + 1;
  }
  if (mapa[*plin][*pcol] == '-')
    return 1;
  else return 0;
}

/* GERA NUMERO ALEATORIO */
int num_aleatorio (int k) 
{
  return (int)(1 + (rand()/(RAND_MAX+1.0))*k);
}

/* DISPARA OS TIROS */
/* NO CASO DE ACERTAR O INIMIGO, DESTROI INIMIGO INTEIRO */
/* SE ACERTAR O BARCO ACABA O JOGO */
int dispara_tiros(char mapa[][MAXCOL], int nlin, int ncol) 
{
  int linha_rand;
  int coluna_rand;
  int cont;
  int acabou;
  cont = 0;
  acabou = 1;
  /* laco para disparar todos os tiros */
  printf ("Disparando tiros ...\n");
  while(cont < NUM_TIROS && acabou) {
    printf("Tiro n %d: ", cont+1);
    linha_rand = num_aleatorio(nlin);
    coluna_rand = num_aleatorio(ncol);
    printf ("linha(%2d), coluna(%2d)  ---> ", linha_rand, coluna_rand);
    /* ACERTOU AGUA */
    if (mapa[linha_rand][coluna_rand] == '-' || mapa[linha_rand][coluna_rand] == '*' )
      printf("AGUA! \n");
    else {
      /* ACERTOU O BARCO */
      if (mapa[linha_rand][coluna_rand] == 'B') {
	mapa[linha_rand][coluna_rand] = '+';
	printf ("O BARCO FOI ATINGIDO! \n");
	acabou = 0;
      }
      else {
	/* ACERTOU INIMIGO */
        if (mapa[linha_rand][coluna_rand] == 'D') {
	  /* MATA DESTROYER */ 
	  printf("ACERTOU DESTROYER! \n");
          if (mapa[linha_rand][coluna_rand+1] == 'D') {
	  }
          if (mapa[linha_rand][coluna_rand-1] == 'D') {
	  }
          if (mapa[linha_rand+1][coluna_rand] == 'D') {
	  }
          if (mapa[linha_rand-1][coluna_rand] == 'D') {
	  }
	}
        if (mapa[linha_rand][coluna_rand] == 'S') {
          /* MATA SUBMARINO */ 
          printf("ACERTOU SUBMARINO! \n");
	}
	if (mapa[linha_rand][coluna_rand] == 'C') {
	  /* MATA CRUZADOR */
	  printf("ACERTOU CRUZADOR! \n");
	  if (mapa[linha_rand+1][coluna_rand+1] == 'C') {
	  }
          if (mapa[linha_rand+1][coluna_rand-1] == 'C') {
	  }
          if (mapa[linha_rand-1][coluna_rand+1] == 'C') {
	  }
	  if (mapa[linha_rand-1][coluna_rand-1] == 'C') {
	  }  
	}
        if (mapa[linha_rand][coluna_rand] == 'P') { 
	  /* MATA PORTA AVIAO */
          printf("ACERTOU PORTA-AVIAO! \n");
          if (mapa[linha_rand][coluna_rand+1] == 'P') {
	  }
          if (mapa[linha_rand][coluna_rand-1] == 'P') {
	  }
          if (mapa[linha_rand+1][coluna_rand] == 'P') {
	  }
          if (mapa[linha_rand-1][coluna_rand] == 'P') {
	  }
	}
	mapa[linha_rand][coluna_rand] = '*';
      }
    }
    cont++;
  }
  return acabou;
}
