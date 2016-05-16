#include <stdio.h>
#define PI 3.14159265358979
#define EPSILON 0.001

/* Fatorial*/
int fatorial (int x) {
    int fat;
    for (fat = 1; x > 1; x--){
        fat = fat*x;
    }
    return fat;
}

/* Potencia */
float potencia (float a, int b) {
    float pot;
    for (pot = 1; b != 0; b--) {
        pot = pot*a;
    }
    return pot;
}

/* Raiz quadrada */
float raiz (float x) {
    float rant, ratual;
    rant = x;
    ratual = (rant+1)/2;
    while ((ratual-rant) > EPSILON || (ratual-rant) < -EPSILON) {
        rant = ratual;
        ratual = (rant+x/rant)/2;
    }
    return ratual;
}

/* Seno */
float seno (float x) {
    float total, termo, y;
    int i, sinal;
    y = x;
    sinal = 1;
    while (y > PI){
        y = y-PI;
        sinal = (-1)*sinal;
    }
    while (y < -PI){
        y = y + PI;
        sinal = (-1)*sinal;
    }
    total = 0;
    termo = 1;
    for (i = 0; (termo > EPSILON || termo < -EPSILON); i++) {
        termo = (potencia (-1, i) * potencia (y, 2*i+1))/fatorial (2*i+1);
        total = total+termo;
    }
    total = sinal*total;
    return total;
}

/* Cosseno */
float cosseno (float x) {
    int n;
    float result, meio;
    meio = 1 - (seno (x) * seno (x));
    result = raiz (meio);
    if (x < 0) {
        x = -1*x;
    }
    for (n = 0; n <= x/2; n++) {
        if ((x > PI*(n*2+0.5)) && (x < PI*(n*2+1.5))) {
            result = -1*result;
        }
    }
    return result;
}

int main () {

    float a, b, num, inter; /* espaço entre os pontos */
    int n, i, pseno, pcosseno; /* posição de seno e cosseno no gráfico */
    int pto;
    printf ("%f\n", raiz(64.0));
    printf ("%f\n", potencia (8.0,2));
    printf ("%d\n", fatorial(4));

    printf ("%f\n", seno(PI));
    printf ("%f\n", cosseno(PI));

    printf ("Programa que imprime os graficos das funcoes seno e cosseno\n\n");
    printf ("Digite o intervalo a e b: ");
    scanf ("%f%f", &a, &b);
    printf ("Digite a qualidade: ");
    scanf ("%d", &n);
    inter = (b-a)/(n-1);
    printf ("\nseno x\ncosseno +\n\n");
    printf ("-1                   0                   1\n");
    printf ("-+-------------------+-------------------+->\n");
    i = 0;
    for (num = 0; num < b; i++) {
        num = a + (i*inter);
        printf (" ");
        if (seno (num) == 0)
            pseno = 21;
        else  pseno = 21 + seno(num)*20;

        if (cosseno (num) == 0)
            pcosseno = 21;
        else  pcosseno = 21 + cosseno(num)*20;

        for (pto = 1; pto < 42; pto++) {
            if (pto == 21 || pto == pcosseno || pto == pseno) {
                if (pto == 21) {
                    if (pto == pcosseno || pto == pseno)
                        printf ("*");
                    else /* se pto!=pcosseno e pto!=pseno */
                        printf ("|");
                }
                else 
                    if (pto == pcosseno || pto == pseno) {
                        if (pcosseno == pseno)
                            printf ("*");
                        else { /* se pcosseno!=pseno */
                            if (pto == pcosseno) printf ("+"); 
                            if (pto == pseno) printf ("x");
                        }
                    }
            }
            else printf (" "); /* se pto!=21 e pto!=pcosseno e pto!=pseno */
        }
        printf ("\n");
    }
    return (0);
}
