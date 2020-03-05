/*
    Um Programa que mostra como é usado o typedef com malloc em C

    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploTypeDef.c
*/
#include<stdio.h>
#include<malloc.h>

#define alturaMaxima 225

typedef struct {
    int peso; //peso em quilogramas
    int altura; // altura em centimetros
} PesoAltura;

int main() {
    // Cria a estrutura de dados do tipo PesoAltura
    PesoAltura* pessoa1 = (PesoAltura*) malloc(sizeof(PesoAltura));

    // Printa a Posição na memoria de pessoa1
    printf("Posição de pessoa1: %i \n", pessoa1);

    // Printa quanto em bytes foi alocado para pessoa1
    printf("Ocupando %i bytes \n", sizeof(PesoAltura));

    //Coloca os valores nos campos
    pessoa1->peso = 80;
    pessoa1->altura = 185;

    //Printa os valores dentro de pessoal1
    printf("Peso: %i \nAltura: %i \n", pessoa1->peso, pessoa1->altura);


    //Verifica se o valor da altura da pessoa e maior que o alturaMaxima que foi definida
    if ( pessoa1->altura > alturaMaxima )
        printf("Essa pessoa esta acima da altura maxima\n");
    else
        printf("Essa pessoa esta acima da altura maxima\n");
    

    return 0;
}
