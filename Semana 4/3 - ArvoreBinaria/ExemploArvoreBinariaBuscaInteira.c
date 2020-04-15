/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploArvoreBinariaBuscaInteira.c
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
    struct aux *menor, *maior;
} NO , * PONTEIRO;

PONTEIRO inicializar() {
    return NULL;
}

PONTEIRO inserir(PONTEIRO raiz, PONTEIRO no) {
    if (raiz == NULL) return no;

    if (no->chave < raiz->chave)
        raiz->menor = inserir(raiz->menor, no);
    else 
        raiz->maior = inserir(raiz->maior, no);

    return raiz;
}

PONTEIRO criarNo(CHAVE ch) {
    PONTEIRO n = (PONTEIRO) malloc(sizeof(NO));
    n->maior = NULL;
    n->menor = NULL;
    n->chave = ch;

    return n;
}

PONTEIRO buscaBinaria(PONTEIRO raiz, CHAVE ch, PONTEIRO *pai) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;

    if (pai != NULL) *pai = raiz;
    if (raiz->chave > ch) return buscaBinaria(raiz->menor, ch, pai);
    
    return buscaBinaria(raiz->maior, ch, pai);
}

PONTEIRO removerNo(PONTEIRO raiz, CHAVE ch) {
    PONTEIRO pai, no, p, q;
    no = buscaBinaria(raiz, ch, &pai);

    if (no == NULL) return raiz;
        
    if (no->menor && no->maior) {
        p = no;
        q = no->menor;
        
        while (p->maior) {
            p = q;
            q = q->maior;
        }

        if (p != no) {
            p->maior = q->menor;
            q->menor = no->menor;
        }

        q->maior = no->maior;
    } else
        q = (!no->menor) ? no->menor : no->maior;
    
    
    if (!pai) {
        free(no);
        return q;
    }

    if (ch < pai->chave) {
        pai->menor = q;
    } else {
        pai->maior = q;
    }

    free(no);
    return raiz;
}

void exibirArvore(PONTEIRO raiz) {
    if (raiz != NULL) {
        printf("{ \"Chave\": %i,", raiz->chave);
        printf("\"Menor\": ");
        exibirArvore(raiz->menor);
        printf(", \"Maior\": ");
        exibirArvore(raiz->maior);
        printf(" }");
    } else printf("\"NULL\"");
}

int getSize(PONTEIRO raiz) {
    if (raiz == NULL) return 0;
    return getSize(raiz->menor) + 1
         + getSize(raiz->maior) + 1;
}

int main() {
    PONTEIRO root = inicializar();

    srand((unsigned) &root);
    
    //Array auxiliar para testar a busca
    int itens[MAX];

    for (int i = 0; i < MAX; i++) {
        PONTEIRO no = criarNo(rand());
        itens[i] = no->chave;
        root = inserir(root, no);
    }
    
    exibirArvore(root);
    printf("\n Totalizando %i nos \n", getSize(root));

}