/* ******************************************** */
/* Bruno Ferrero                     3690142    */
/* Oceanografia                Data  12/2006    */
/* MAC_115 Intrducao a Computacao               */
/* Exercico Programa numero 4                   */
/* Compilador utilizado : GCC versao 4.0.1      */
/* ******************************************** */

/*                 AGENCIA BANCARIA IRREAL                              */
/* Controla operacoes bancarias para diversos usuarios                  */

#include <stdio.h>
#include <stdlib.h>
#define NMAXC 100    /* numero maximo de clientes*/
#define COMPMAX 60  /* comprimento nome         */  

/* PROTOTIPO DAS FUNCOES */
int busca (int num, int v[], int n);
void le_info (int ncc[], char nome[][COMPMAX], float sl[][3], int *nc);
void relatorio (int n, int ncc[], char nome[][COMPMAX], float sl[][3]);
void depositar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
		float sl[][3], FILE *arqop);
void retirar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
	      float sl[][3], FILE *arqop);
void transferir (int num, float v, int n, int ncc[], char nome[][COMPMAX],
		 float sl[][3], FILE *arqop);
void aplicar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
	      float sl[][3], FILE *arqop);

/* ********************************************************************* */
int main ()
{
  FILE *arq;
  int num_conta[NMAXC],              /* vetor contendo numero das contas */ 
    n,                               /* numero de clientes               */
    cont,                            /* conta numero de operacoes        */
    num;                             /* numero da conta                  */
  char nome_cliente[NMAXC][COMPMAX], /* matriz de nomes                  */
    arquivo_saida[COMPMAX],
    acao;
  float saldo_lim[NMAXC][3],
    valor;                           /* armazena quantia para cada acao  */
  le_info (num_conta, nome_cliente, saldo_lim, &n);
  printf ("Entre com o nome do arquivo de saida : ");
  scanf (" %s", arquivo_saida);
  arq = fopen (arquivo_saida, "w");
  cont = 1;
  printf ("Digite a letra correspondente a uma acao : \n"
	  "Depositar na sua conta corrente : (d) \n"
	  "Retirar de sua conta corrente :   (r) \n"
	  "Transferir de sua conta :         (t) \n"
	  "Aplicar :                         (a) \n"
          "Sair                              (s) \n");
  scanf (" %c", &acao);
  while (acao != 's') {
    printf ("Entre com o numero da conta : ");
    scanf ("%d", &num);
    while (busca (num, num_conta, n) == (-1)) {
      printf ("Numero de conta invalido. \n");
      printf ("Entre com um numero valido de conta : ");
      scanf ("%d", &num);
    }
    printf ("Entre com o valor : ");
    scanf ("%f", &valor);
    fprintf (arq, "Operacao %d : ", cont);
    cont++;
    switch (acao) {
    case 'd' : depositar (num, valor, n, num_conta, nome_cliente, saldo_lim, arq); break;
    case 'r' : retirar (num, valor, n, num_conta, nome_cliente, saldo_lim, arq); break;
    case 't' : transferir (num, valor, n, num_conta, nome_cliente, saldo_lim, arq); break;
    case 'a' : aplicar (num, valor, n, num_conta, nome_cliente, saldo_lim, arq); break;
    default : printf ("\nOPERACAO INVALIDA. \n\n"); break;
    }
    printf ("Digite a letra correspondente a uma acao : \n"
	    "Depositar na sua conta corrente : (d) \n"
	    "Retirar de sua conta corrente :   (r) \n"
	    "Transferir de sua conta :         (t) \n"
	    "Aplicar :                         (a) \n"
	    "Sair                              (s) \n");
    scanf (" %c", &acao);
  }
  relatorio (n, num_conta, nome_cliente, saldo_lim);
  return 0;
  fclose(arq);
}
/* ********************************************************************* */

int busca (int numero, int v[], int n) 
{
  int i;
  for (i = 0; i < n; i++)
    if (v[i] == numero)
      return i;
  return -1;
}

void le_info (int ncc[], char nome[][COMPMAX], float sl[][3], int *nc)
{
  FILE *arqentra;
  char nome_arq[COMPMAX], aux;
  int i,j;
  printf ("Digite o nome do arquivo a ser lido : ");
  scanf (" %s", nome_arq);
  arqentra = fopen (nome_arq, "r");
  if (arqentra == NULL) {
    printf ("Nao foi possivel abrir o arquivo %s.\n", nome_arq);
    exit (1);
  }
  /* preenche vetor com -9999. Este numero nao deve ser utilizado como numero de conta */
  for (i = 0; i < COMPMAX; i++)
    ncc[i] = -9999;
  for (i = 0, j = 1; j < COMPMAX; i++, j++) {
    fscanf (arqentra, " %d %[^\n]",&ncc[i], nome[i]);
    fscanf (arqentra, " %f %f %f", &sl[i][0], &sl[i][1], &sl[i][2]);
  }
  /* determina o numero de contas presente no vetor ncc */
  if (busca (-9999, ncc, COMPMAX) == -1)
    *nc = COMPMAX;
  else *nc = busca (-9999, ncc, COMPMAX);
  fclose (arqentra);
}

void relatorio (int n, int ncc[], char nome[][COMPMAX], float sl[][3])
{
  FILE *arqsaida;
  char arquivo[COMPMAX];
  int i;
  printf ("Entre com o nome do arquivo do relatorio : ");
  scanf (" %s", arquivo);
  arqsaida = fopen (arquivo, "w");
  fprintf (arqsaida, "Numero     Nome                          Saldo         Saldo       Limite    \n"
	   "conta      titular                       conta         conta       cheque    \n" 
	   "corrente                                 corrente      invest.     especial  \n"
	   "-----------------------------------------------------------------------------\n");
  for (i = 0; i < n; i++)
    fprintf (arqsaida, "%5d \t %27s R$%8.2f    R$%8.2f    R$%8.2f \n"
	     , ncc[i], nome[i], sl[i][0], sl[i][1], sl[i][2]);     
  fclose (arqsaida);
}

void depositar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
		float sl[][3], FILE *arqop)
{ 
  int aux;
  aux = busca (num, ncc, n);;
  fprintf (arqop, "Depositar R$%g na conta corrente \n\n", v);
  fprintf (arqop, "Numero da conta corrente : %d\n", ncc[aux]);
  fprintf (arqop, "Nome do titular : %s \n", nome[aux]);
  fprintf (arqop, "Saldo da conta corrente : R$%g\n", sl[aux][0]);
  fprintf (arqop, "Saldo da conta de investimento : R$%g\n", sl[aux][1]);
  fprintf (arqop, "Saldo do cheque especial : R$%g\n\n", sl[aux][2]);
  sl[aux][0] = sl[aux][0] + v;
  fprintf (arqop, "Operacao realizada com sucesso!\n\n");
  fprintf (arqop, "Saldo da conta corrente : R$%g \n\n", sl[aux][0]);
}

void retirar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
	      float sl[][3], FILE *arqop)
{
  int aux;
  aux = busca (num, ncc, n);
  fprintf (arqop, "Retirar R$%g na conta corrente \n\n", v);
  fprintf (arqop, "Numero da conta corrente : %d\n", ncc[aux]);
  fprintf (arqop, "Nome do titular : %s \n", nome[aux]);
  fprintf (arqop, "Saldo da conta corrente : R$%g\n", sl[aux][0]);
  fprintf (arqop, "Saldo da conta de investimento : R$%g\n", sl[aux][1]);
  fprintf (arqop, "Saldo do cheque especial : R$%g\n", sl[aux][2]);
  sl[aux][0] = sl[aux][0] - v;
  if (sl[aux][0] >= 0)
    fprintf (arqop, "Operacao realizada com sucesso!\n\n"
	     "Saldo da conta corrente : R$%g \n\n", sl[aux][0]);
  else fprintf (arqop, "Operacao realizada (mas saldo esta negativo).\n\n"
		"Saldo da conta corrente : R$%g (negativo) \n\n", sl[aux][0]*(-1));
  

}
void transferir (int num, float v, int n, int ncc[], char nome[][COMPMAX],
		 float sl[][3], FILE *arqop)
{
  int aux;
  aux = busca (num, ncc, n);
  fprintf (arqop, "Transferir R$%g da conta investimento para conta corrente \n\n", v);
  fprintf (arqop, "Numero da conta corrente : %d\n", ncc[aux]);
  fprintf (arqop, "Nome do titular : %s \n", nome[aux]);
  fprintf (arqop, "Saldo da conta corrente : R$%g\n", sl[aux][0]);
  fprintf (arqop, "Saldo da conta de investimento : R$%g\n", sl[aux][1]);
  fprintf (arqop, "Saldo do cheque especial : R$%g\n", sl[aux][2]);
  if (v > sl[aux][1])
    fprintf (arqop, "NAO foi possivel realizar essa operacao \n\n");
  else {
    sl[aux][1] = sl[aux][1] - v;
    sl [aux][0] = sl[aux][0] + v;
    fprintf (arqop, "Operacao realizada com sucesso!\n\n"
	     "Saldo da conta corrente : R$%g \n"
	     "Saldo da conta investimento : R$%g \n\n", sl[aux][0], sl[aux][1]);
  }
}
void aplicar (int num, float v, int n, int ncc[], char nome[][COMPMAX],
	      float sl[][3], FILE *arqop)
{
  int aux;
  aux = busca (num, ncc, n);
  fprintf (arqop, "Aplicar R$%g na conta investimento \n\n", v);
  fprintf (arqop, "Numero da conta corrente : %d\n", ncc[aux]);
  fprintf (arqop, "Nome do titular : %s \n", nome[aux]);
  fprintf (arqop, "Saldo da conta corrente : %g\n", sl[aux][0]);
  fprintf (arqop, "Saldo da conta de investimento : %g\n", sl[aux][1]);
  fprintf (arqop, "Saldo do cheque especial : %g\n", sl[aux][2]);
  if (v > sl[aux][0])
    fprintf (arqop, "NAO foi possivel realizar essa operacao \n\n");
  else {
    sl[aux][0] = sl[aux][0] - v;
    sl [aux][1] = sl[aux][1] + v;
    fprintf (arqop, "Operacao realizada com sucesso!\n\n"
	     "Saldo da conta corrente : R$%g \n"
	     "Saldo da conta investimento : R$%g \n\n", sl[aux][0], sl[aux][1]);
  }
}

