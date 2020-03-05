/*
    Um Programa que mostra como é usado o typedef em C

    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploTypeDef.c
*/
#include<stdio.h>

#define alturaMaxima 225

typedef struct {
    int peso; //peso em quilogramas
    int altura; // altura em centimetros
} PesoAltura;

int main() {
    // Cria a estrutura de dados do tipo PesoAltura
    PesoAltura pessoa1;

    //Coloca os valores nos campos
    pessoa1.peso = 80;
    pessoa1.altura = 185;

    //Printa os valores dentro de pessoal1
    printf("Peso: %i \n Altura: %i \n", pessoa1.peso, pessoa1.altura);


    //Verifica se o valor da altura da pessoa e maior que o alturaMaxima que foi definida
    if ( pessoa1.altura > alturaMaxima )
        printf("Essa pessoa esta acima da altura maxima");
    else
        printf("Essa pessoa esta acima da altura maxima");
    

    return 0;
}
