/*
 * arquivo: cos.c
 * Dados x real e n natural, calcular uma aproxima��o para cos(x) atrav�s dos n
 * primeiros termos da s�rie.
 * Aproximacao boa em torno do zero.
 * e ineficiente!!! pois calcula numerador e dividendo separadamente.
 * modifique-o 
 */

#include<stdio.h>
#include<math.h>  // <=== para fazer o calculo de cos(x) usando a funcao cos(.)
                  // da biblioteca math.  Veja o ultimo printf.
int main()
{
    int n, k, sinal;
    double fatorial, x, cosx, termo, dividendo;
                   // Veja: fatorial declarado como 'double'
    printf("Forne�a o valor do �ngulo em radianos: ");
    scanf("%lf", &x);
    printf("N�mero de termos: ");
    scanf("%d", &n);
    cosx = 1;
    sinal= 1;
    fatorial = 1; 
    dividendo = 1;
    for (k = 1; k < n; k++) {
        fatorial = fatorial * (2 * k -1) * (2 * k); //<==== calculo do fatorial
                               // aproveitando o fatorial anterior.
        dividendo = dividendo * x * x;
        termo = dividendo / fatorial;
        sinal  = - sinal;              // para alternar o sinal do termo
        cosx = cosx + sinal * termo;   // veja o uso do sinal aqui. 
       
    }
    printf("cos(%g) = %g\n", x, cosx);
    printf("Usando a funcao cos(.) ja' disponivel:  cos(%g) = %g\n", x, cos(x));
    return 0;
}

