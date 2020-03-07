/* 
    Questão 6

    $ gcc Questao6.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

#define MAX 50

typedef int CHAVE;

typedef struct {
    CHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int nroElem;
} LISTA;

// Função que inicia a lista
void iniciarLista(LISTA* l) {
    l->nroElem = 0;
}

// Função que printa os valores de uma lista
void exibirLista(LISTA* l) {
    int i;

    printf("Lista: \" ");

    // Loop que passa item por item printando os valores de cada um
    for (i=0; i < l->nroElem; i++) 
        printf(" %i ", l->A[i].chave);
    
    printf("\" \n");
}

// Função que adiciona um item a lista
bool inserirNovo(LISTA* l, REGISTRO reg){
    if (l->nroElem >= MAX) 
        return false;

    l->A[l->nroElem] = l->A[0];
    l->A[0] = reg;
    l->nroElem++;

    return true;
}



int main() {
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));
    
    iniciarLista(l);

    inserirNovo(l, (REGISTRO) {
        chave:10
    });

    inserirNovo(l, (REGISTRO) {
        chave:20
    });

    inserirNovo(l, (REGISTRO) {
        chave:30
    });

    inserirNovo(l, (REGISTRO) {
        chave:40
    });

    exibirLista(l);

    return 0;
}
