#include <stdio.h>

int main ()
{
  int p, q, outra;
  printf ("Digite dois inteiros positivo (p, q), sendo que o numero de digitos de p e' menor ou igual ao numero de digitos de q : ");
  scanf ("%d%d", &p, &q);
  printf ("%d ", p);
  while (q > 0) {
    if ((p%10) == (q%10)) {
      outra = p;
      while ((outra%10) == (q%10) && outra>0) {
      outra = outra/10;
      q = q/10;
      }
    }
    q = q/10;
  }
  if (outra == 0) 
    printf ("e'subnumero. \n");
  else printf ("nao e' subnumero.\n");
  return 0;
}
