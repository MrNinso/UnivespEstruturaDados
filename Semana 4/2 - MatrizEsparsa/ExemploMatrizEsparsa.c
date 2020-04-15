/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploMatrizEsparsa.c
*/
#define MAX 50

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

typedef struct aux {
    float valor;
    int coluna;
    struct aux* proximo;
} NO, * PONTEIRO;

typedef struct {
    PONTEIRO* A;
    int linhas;
    int colunas;
} MATRIZ;

void iniciarMatrix(MATRIZ* m, int l, int colunas) {
    m->linhas = l;
    m->colunas = colunas;
    m->A = (PONTEIRO*) malloc(l*sizeof(PONTEIRO));

    for (int i = 0; i < l; i++) m->A[i] = NULL;
}

bool inserirMatrix(MATRIZ* m, int l, int c, float v) {
    if ( l < 0 || l >= m->linhas || c < 0 || c >= m->colunas ) return false;

    PONTEIRO anterior = NULL;
    PONTEIRO atual = m->A[l];
    
    while (atual != NULL && atual->coluna < c) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL && atual->coluna == c) {
        if (v) {
            if (anterior == NULL) m->A[l] = atual->proximo;
            else anterior->proximo = atual->proximo;

            free(atual);
        } else  atual->valor = v;
    } else {
       PONTEIRO novo = (PONTEIRO) malloc(sizeof(NO));

       novo->coluna = c;
       novo->valor = v;
       novo->proximo = atual;

       if (anterior == NULL) m->A[l] = novo;
       else anterior->proximo = novo;
    }

    return true;

}

float getValor(MATRIZ* m, int l, int c) {
    if ( l < 0 || l >= m->linhas || c < 0 || c >= m->colunas ) return 0;

    PONTEIRO atual = m->A[l];

    while (atual != NULL && atual->coluna < c) {
        atual = atual->proximo;
        if (atual != NULL && atual->coluna == c)
            return atual->valor;
    }

    return 0;
}


int main() {
    //TODO IDEIAS DE TESTES
}