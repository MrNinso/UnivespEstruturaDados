/*
    Um Programa que mostra como é usado o malloc em C

    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploMalloc.c
*/
#include<stdio.h>
#include<malloc.h>

int main() {
    // Aloca o espaço na memoria no tamanho de um int usando o metodo malloc e coloca o endereço dessa memoria no ponteiro y
    int* y = (int*) malloc(sizeof(int));

    // Coloca na memoria alocada o valor 20
    *y = 20;

    // Coloca na variavel z a quantidade de bytes ocupados pelo valor inteiro
    int z = sizeof(int);

    // Printa os valores das variaveis
    printf("y=%i *y=%i z=%i \n", y, *y, z);

    return 0;
}