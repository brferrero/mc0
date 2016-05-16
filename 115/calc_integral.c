/* ******************************************** */
/* Bruno Ferrero                     3690142    */
/* Oceanografia                Data  10/2006    */
/* MAC_115 Intrducao a Computacao               */
/* Exercico Programa numero 2                   */
/* Compilador utilizado : GCC versao 4.0.1      */
/* ******************************************** */

/*                     CALCULO DE INTEGRAIS                              */
/* Calcula as integrais das funcoes seno e cosseno no intervalo [O; pi/2]*/
/* por dois diferentes metodos: Metodo dos Retangulos e Metodo dos Trape-*/
/*zios. A saida e' dada em arquivo saida.txt                             */

#include <stdio.h>

/* PROTOTIPO DAS FUNCOES */
double fatorial (int x);          
double potencia (double a, int b);
double seno (double x);
double cosseno (double x);

int main () 
{
  FILE *arq;
  int n,      /* numero de intervalos ente 0 e k                         */
    i, j;     /* utilizados para controlar o for                         */    
  double k,   /* limite do intervalo de integracao                       */
    eps,      /* base dos retangulos ou trapezios                        */
    integral, /* resultado do calculo atraves das series                 */ 
    termo;    /* armazena os termos para o calculo da somatoria da serie */
  arq = fopen ("saida.txt","w");
  printf ("Entre com um numero real k tal que 0 < k < pi/2 : ");
  scanf ("%lf",&k);
  eps = k;
  fprintf (arq, "INTEGRAL DE SENO E COSSENO NO INTERVALO [0, %g] \n",k);
  fprintf (arq, "   Metodo dos Retangulos \t Metodo dos Trapezios  \n"); 
  for (j = 0; eps >= 1.e-5; j++) {
    eps = k/potencia(2,j);
    fprintf (arq,"eps = %g\n",eps);
    n = k/eps;
    /* intergral de SENO (metodo dos retangulos) */
    integral = 0;
    for (i = 1; i<=n; i++) {
      termo = seno (i*eps)*eps;
      integral = integral + termo;
    }
    fprintf (arq, "SENO   : %10.10f", integral);
    /* integral de SENO (metodo dos trapezios) */
    integral = 0;
    for (i = 1; i<=n; i++) {
      termo = (seno ((i-1)*eps) + seno (i*eps))*eps/2;
      integral = integral + termo;
    } 
    fprintf (arq, "%28.10f\n", integral);
    /* integral de COSSENO (metodo dos retangulos) */ 
    integral = 0;
    for (i = 1; i<=n; i++) {
      termo = cosseno (i*eps)*eps;
      integral = integral + termo;
    }
    fprintf (arq, "COSSENO: %10.10f", integral); 
    /* integral de COSSENO (metodo dos trapezios) */ 
    integral = 0;
    for (i = 1; i<=n; i++) {
      termo = (cosseno ((i-1)*eps) + cosseno (i*eps))*eps/2;
      integral = integral + termo;
    } 
    fprintf (arq, "%28.10f\n\n", integral);
  }
  return 0;
  fclose (arq);
}

/* funcao fatorial */
/* recebe um numero inteiro x e devolve um inteiro fat */
double fatorial (int x) 
{
  int fat;
  for (fat = 1; x > 1; x--) {
    fat = fat*x;
  }
  return (fat);
}

/* funcao potencia */
/* recebe um numero real a e um inteiro b; devolve um real pot */
double potencia (double a, int b) 
{
  double pot;
  for (pot = 1; b != 0; b--) {
    pot = pot*a;
  }
  return (pot);
}

/* funcao seno */
/* recebe um numero real x; devolve um real result */
double seno (double x) 
{
  int i;
  double termo, result;
  result = 0;
  termo = 1;
  for (i = 0; (termo > 1.e-8 || termo < -1.e-8); i++) {
    termo = potencia (-1,i)*potencia (x,2*i+1)/fatorial (2*i+1);
    result = result + termo;
  }
  return (result);
}

/* funcao cosseno */
/* recebe um numero real x; devolve um real result */
double cosseno (double x) 
{
  int i;
  double termo, result;
  result = 1;
  termo = 1;
  for (i = 1; (termo > 1.e-8 || termo < -1.e-8); i++) {
    termo = potencia (-1,i)*potencia (x,2*i)/fatorial (2*i);
    result = result + termo;
  }
  return (result);
}
