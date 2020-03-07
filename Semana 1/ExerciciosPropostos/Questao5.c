/* 
    Questão 5

    $ gcc Questao5.c
*/
#include <stdio.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} DATA;

void atualizar(DATA* pontData, int dia, int mes, int ano) {
    *pontData = (DATA) {
        dia: dia,
        mes: mes,
        ano: ano
    };
}

int main() {
   
    DATA dataExmeplo;

    atualizar(&dataExmeplo, 02,11,2000);

    printf("%i/%i/%i", dataExmeplo.dia, dataExmeplo.mes, dataExmeplo.ano);

    return 0;
}
