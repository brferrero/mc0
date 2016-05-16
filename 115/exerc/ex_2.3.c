#include <stdio.h>

int main() 
{
  int n, m;         /* determinam o intervalo da funcao */
  int x, y;         /* usados para o calculo do maximo */
  int valor;        /* guarda x*y - x*x + y */
  int xmax, ymax;   /* argumentos que maximizam a funcao */
  int valormax;     /* guarda xmax*ymax - xmax*xmax + ymax */

  printf("Maximizo x*y - x*x + y, onde 0 <= x <= n e 0 <= y <= m.\n");

  /* leia os limitantes do intervalo */
  printf("Entre com n e m: ");
  scanf ("%d %d", &n, &m);

  /* inicializacoes */
  xmax = ymax = 0;
  valormax = 0;  /* valormax ==  xmax*ymax - xmax*xmax + ymax */

  /* testa tos os possiveis valores da funcao */
  for (x = 0; x <= n; x++) 
    {
      for (y = 0; y <= m; y++) 
	{
          valor = x*y - x*x + y;
          if (valor > valormax)
	    {
              valormax = valor;
              xmax = x;
              ymax = y;
	    }
	}  
    }
  
  printf("Valor maximo da funcao = %d foi alcancado com x = %d e y = %d\n", 
          valormax, xmax, ymax);
    
  return 0;
} 
