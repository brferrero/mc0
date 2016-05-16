#include<stdio.h>

int main () {
    int soma = 0;
    int n, num, i;
    scanf ("%d",&n);
    if (n <= 50 && n>= 0) {
        for (i = 0; i < n; i++) {
            scanf("%d",&num);
            if (num <= 5000 && num >= -5000)
                soma = soma + num;
        }
    }
    printf ("%d\n", soma);
    return 0;
}
