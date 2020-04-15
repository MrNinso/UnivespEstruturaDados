/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploArvoreNaria.c
*/
#define MAX 50

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include <string.h>

typedef int CHAVE;

typedef struct aux {
    CHAVE chave;
    struct aux *primFilho, *proxIrmao;
} NO , * PONTEIRO;

PONTEIRO criarNo(CHAVE ch) {
    PONTEIRO novo  = (PONTEIRO) malloc(sizeof(NO));
    novo->primFilho = NULL;
    novo->proxIrmao = NULL;
    novo->chave = ch;
    return novo;
}

PONTEIRO inicializar(CHAVE ch) {
    return criarNo(ch);
}

PONTEIRO buscaBinaria(PONTEIRO raiz, CHAVE ch) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch)  return raiz;

    PONTEIRO p = raiz->primFilho;

    while (p) {
        PONTEIRO resp = buscaBinaria(p, ch);
        if (resp) return resp;
        p = p->proxIrmao;
    }

    return NULL;
}

bool inserir(PONTEIRO raiz, CHAVE ch, CHAVE chPai) {
    PONTEIRO pai = buscaBinaria(chPai, raiz);
    if (!pai) return false;

    PONTEIRO filho = criarNo(ch);

    PONTEIRO p = pai->primFilho;

    if (!p)
        pai->primFilho = filho;
    else {
        while (p->proxIrmao) {
            p = p->proxIrmao;
        }
        p->proxIrmao = filho;
    }
    return true;
}

void exibirArvore(PONTEIRO raiz) {
    if (raiz == NULL) return;
    printf("%i(", raiz->chave);
    PONTEIRO p = raiz->primFilho;

    while (p) {
        exibirArvore(p);
        p->proxIrmao;
    }

    printf(")");
}



int main() {
    PONTEIRO seed = (PONTEIRO) malloc(sizeof(NO));
    
    srand((unsigned) &seed);

    free(seed);

    PONTEIRO root =  inicializar(rand());
}