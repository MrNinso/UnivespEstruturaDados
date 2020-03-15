/*
    Exemplo de uma função retornando 2 valores
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploQuadradoCubo.c
*/

#include <stdio.h>

int quadradoCubo(int x, int* y) {
    *y = x*x*x;
    return x*x;
}

int main() {
    int a = 30;
    int cubo;
    
    int r = quadradoCubo(a, &cubo);

    printf(" a: %i \n a*a: %i \n a*a*a: %i \n", a, r, cubo);

    return 0;
}