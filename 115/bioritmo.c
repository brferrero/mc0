/* ******************************************** */
/* Bruno Ferrero                     3690142    */
/* Oceanografia                Data  11/2006    */
/* MAC_115 Intrducao a Computacao               */
/* Exercico Programa numero 3                   */
/* Compilador utilizado : GCC versao 4.0.1      */
/* ******************************************** */

/*                    GRAFICO DO BIORITMO                               */
/* Recebe a data de nascimento, um mes e ano para o qual sera plotado o */ 
/* gráfico do bioritmo para os tres diferentes ciclos                   */

#include <stdio.h>
#include <math.h>
#define PERIODOF 23
#define PERIODOE 28
#define PERIODOI 33
#define COMPMAX 61
#define TAMMAX 100
#define NMAX 31

/* PROTOTIPO DAS FUNCOES */
int ano_bissexto (int ano);
int ultimo_dia_mes (int mes, int ano);
int conta_dias (int d1, int m1, int a1, int d2, int m2, int a2);
double amplitude_ciclo (int idade_dias, int periodo);
int indice_amplitude (double amplitude);
void determina_linha_grafico (int indF, int indE, int indI, char linha[]);
void determina_indices_amplitude (int idade_dias, int *pF, int *pE, 
				  int *pI);
void descreve_dia (int indF, int indE, int indI, int dia, 
		   int criativo[], int critico[], 
		   int minicritico[], int combina[]);

/* FUNCAO PRINCIPAL */
int main ()
{
  FILE *arq;
  int i, j, k, dd, mm, aa, mm_final, aa_final, dias, 
    ind_fis, ind_emo, ind_intel,
    criat[NMAX], crit[NMAX], minicrit[NMAX], comb[NMAX];
  /* mm_final e aa_final referem-se ao mes e ano para os quais sera */
  /* plotado o grafico do bioritimo                                 */
  char vetor_linha[COMPMAX], nome[TAMMAX], arquivo[TAMMAX];
  criat[0] = crit[0] = minicrit[0] = comb[0] = 0;
  printf ("Entre com o seu nome : ");
  scanf (" %[^\n]", nome);
  printf ("Entre com sua data de nascimento (dd/mm/aaaa) : ");
  scanf ("%d/%d/%d", &dd, &mm, &aa);
  printf ("Entre com o mes e o ano (mm/aaaa) para o grafico do bioritmo : ");
  scanf ("%d/%d", &mm_final, &aa_final);
  printf ("Entre com o nome do arquivo de saida : ");
  scanf (" %s", arquivo);
  arq = fopen (arquivo, "w");
  dias = conta_dias (dd, mm, aa, ultimo_dia_mes (mm_final, aa_final), 
		     mm_final, aa_final);
  i = dias - ultimo_dia_mes (mm_final, aa_final) + 1;
  k = 1;
  fprintf (arq, "Nome: %s\n", nome);
  fprintf (arq,	"Data de nascimento: %d/%d/%d \n\n", dd, mm, aa);
  fprintf (arq,	"                Grafico do Bioritmo para o mes ");
  switch (mm_final) {
  case 1 : fprintf (arq, "Janeiro "); break;
  case 2 : fprintf (arq, "Fevereiro "); break;
  case 3 : fprintf (arq, "Marco "); break;
  case 4 : fprintf (arq, "Abril "); break;
  case 5 : fprintf (arq, "Maio" ); break;
  case 6 : fprintf (arq, "Junho "); break;
  case 7 : fprintf (arq, "Julho "); break;
  case 8 : fprintf (arq, "Agosto "); break;
  case 9 : fprintf (arq, "Setembro "); break;
  case 10 : fprintf (arq, "Outubro "); break;
  case 11 : fprintf (arq, "Novembro "); break;
  case 12 : fprintf (arq, "Dezembro "); break;
  default : ;
  }
  fprintf (arq, "de %d\n\n", aa_final);
  fprintf (arq, " dia                      amplitude dos ciclos\n"
	   "    -1.0                           0.0                           1.0\n");   
  fprintf (arq, "      |-----------------------------|-----------------------------|\n"); 
  for (i; i <= dias; i++) {  
    determina_indices_amplitude (i, &ind_fis, &ind_emo, &ind_intel);
    determina_linha_grafico (ind_fis, ind_emo, ind_intel, vetor_linha);  
    fprintf (arq, "%3d - ", k);
    for (j = 0; j <= COMPMAX; j++)       
      fprintf (arq, "%c", vetor_linha[j]);
    fprintf (arq, " - %3d", k);
    descreve_dia (ind_fis, ind_emo, ind_intel, k, criat, crit, minicrit, comb);
    k++;
    fprintf (arq, "\n");
  }
  fprintf (arq, "      |-----------------------------|-----------------------------|\n\n");
  fprintf (arq, "   F = ciclo Fisico     E = ciclo Emocional     I = ciclo Intelectual\n\n");
  fprintf (arq, "Dia(s) em que a criatividade esta acentuada : ");
  for (i = 1; i < criat[0]; i++)
    fprintf (arq, " %d,", criat[i]);
  fprintf (arq, " %d\n", criat[i]); 

  fprintf (arq, "Dia(s) criticos : ");
  for (i = 1; i < crit[0]; i++)
    fprintf (arq, " %d,", crit[i]);
  fprintf (arq, " %d\n", crit[i]);
  
  fprintf (arq, "Dia(s) minicriticos : ");
  for (i = 1; i < minicrit[0]; i++)
    fprintf (arq, " %d,", minicrit[i]);
  fprintf (arq, " %d\n", minicrit[i]);

  fprintf (arq, "Dia(s) de combinacao (produtividade esta reduzida) : ");
  for (i = 1; i < comb[0]; i++) {
    fprintf (arq, " %d,", comb[i]);
  }
  fprintf (arq, " %d\n", comb[i]);
  return 0;
  fclose (arq);
}

/* se for bissexto retorna 1 */
int ano_bissexto (int ano)
{
  if ((ano%4 == 0) && (ano%100 != 0) || (ano%400 == 0))
    return 1;
  else return 0;
}

/* retorna o ultimo dia para cada mes */
int ultimo_dia_mes (int mes, int ano)
{
  int ultimo_dia;
  if (mes == 2) {
    if (ano_bissexto (ano))
      ultimo_dia = 29;
    else ultimo_dia = 28;
  }
  else {
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
      ultimo_dia = 30;
    else ultimo_dia = 31;
  }
  return ultimo_dia;
}

/* conta o numero de dias entre duas datas */
int conta_dias (int d1, int m1, int a1, int d2, int m2, int a2)
{
  int dias, i, cont_bissexto;
  dias = 0;
  cont_bissexto = 0;
  if (m1 == m2 && a1 == a2)
    dias = d2 - d1;
  else {
    if (a1 == a2) {
      for (i = m1 + 1; i < m2; i++)
	dias = dias + ultimo_dia_mes (i, a2);
      dias = dias + ultimo_dia_mes (m1,a1) - d1 + d2;
    }
    else {
      for (i = a1 + 1; i < a2; i++) {
	if (ano_bissexto (i))
	  cont_bissexto++;
	dias = dias + 365;
      }
      for (i = m1 + 1; i <= 12 ; i++)
	dias = dias + ultimo_dia_mes (i, a1);
      dias = dias + ultimo_dia_mes (m1, a1) - d1;
      for (i = 1; i < m2; i++)
	dias = dias + ultimo_dia_mes (i, a2);
      dias = dias + d2 + cont_bissexto;
    }
  }
  return dias;
}

/* devolve a amplitude para um ciclo */
double amplitude_ciclo (int idade_dias, int periodo)
{
  return sin (6.2831853*(double)idade_dias/(double)periodo);
}

/* devolve um int, que corresponde a amplitude convertida entre 0 e 60 */
int indice_amplitude (double amplitude)
{
  return (int)((amplitude + 1)*30 + 0.5);
}

/* recebe a idade em dias e determina os indices para cada um dos ciclos*/
void determina_indices_amplitude (int idade_dias, int *pF, int *pE, 
				  int *pI)
{
  *pF = indice_amplitude (amplitude_ciclo (idade_dias,PERIODOF));
  *pE = indice_amplitude (amplitude_ciclo (idade_dias,PERIODOE));
  *pI = indice_amplitude (amplitude_ciclo (idade_dias,PERIODOI));
}

/* define vetor linha */
void determina_linha_grafico (int indF, int indE, int indI, char linha[])
{
  int i;
  for (i = 0; i <= 60; i++)
    linha[i] = ' ';
  linha[0] = linha[30] = linha[60] = '|';
  linha[indF] = 'F';
  linha[indE] = 'E';
  linha[indI] = 'I';
  if (indF == indE)
    linha[indF] = linha[indE] = '*';
  if (indF == indI)
    linha[indF] = linha[indI] = '*';
  if (indE == indI)
    linha[indE] = linha[indI] = '*'; 
}
/* armazena dias especiais em seu vetor correspondente */
void descreve_dia (int indF, int indE, int indI, int dia, 
		   int criativo[], int critico[], 
		   int minicritico[], int combina[])
{
  if (indE > 30 && indI > 30) {
    criativo[criativo[0] + 1] = dia;
    criativo[0]++;
  }
  if (indF == 30 || indE == 30 || indI == 30) {
    critico[critico[0] + 1] = dia;
    critico[0]++;
  }
  if (indF == 60 || indE == 60 || indI == 60 || indF == 0 || indE == 0 || indI == 0) {
    minicritico[minicritico[0] + 1] = dia;
    minicritico[0]++;
    if (indF == 30 || indE == 30 || indI == 30) {
      combina[combina[0] + 1] = dia;   
      combina[0]++;
    }
  }
}
