/*
    Um Programa que mostra como é usado o ponteiros em C

    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploPonteiro.c
*/
#include<stdio.h>

int main() {
    // Cria uma variavel na memoria de nome 'x' com o valor 25
    int x = 25;
    
    // Usando o '&' antes do 'x' conseguimos a posição na memoria dela e colocamos em um ponteiro chamado y
    int* y = &x;

    // Printa qual é a posição salva no y
    printf("A posição de x na memoria é: %i \n", y);

    // Usando o ponteiro modificamos o valor de x sem precisar chamalo
    *y = 30;

    // Printa o valor de x
    printf("Valor de x é: %i \n", x);


    return 0;
}