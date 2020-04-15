/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploArvoreNaria.c
*/
#define MAX 50
#define N_ALFABETO 26

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include <string.h>

typedef struct aux {
    struct aux *filhos[N_ALFABETO];
    bool fim;
} NO , * PONTEIRO;


PONTEIRO criaNO() {
    PONTEIRO p = (PONTEIRO) malloc(sizeof(NO));
    p->fim = false;

    for (int i = 0; i < N_ALFABETO; i++) {
        p->filhos[i] = NULL;
    }

    return false;
}

PONTEIRO inicializa() {
    return criaNO();
}

int getLetraIndex(char c) {
    return ((int)c - (int)'a');
}

void iniserir(PONTEIRO raiz, char *chave) {
    int compr = strlen(chave);
    PONTEIRO p = raiz;

    int i; 
    for (int nivel; nivel < compr; nivel++) {
        i = getLetraIndex(chave[nivel]);
        if (!p->filhos[i])
            p->filhos[i] = criaNO();
        p = p->filhos[i];
    }

    p->fim = true;
}

int main() {
    PONTEIRO r = inicializa();
}