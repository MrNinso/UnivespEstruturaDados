/* 
    Questão 2

    $ gcc Questao2.c
*/
#include <stdio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} DATA;

// Imprime a data
void imprimir(DATA copia){
    printf("%i/%i/%i");
}

int main() {

    DATA dataExemplo = {
        dia: 02,
        mes: 11,
        ano: 2000
    };

    imprimir(dataExemplo);

    return 0;
}
