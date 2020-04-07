/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploFilaDinamica.c
*/
#define MAX 50

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

typedef int CHAVE;

typedef struct {
    CHAVE chave;
    int valor;
} REGISTRO;

typedef struct aux {
    REGISTRO registro;
    struct aux* proximo;
} ELEMENTO, * PONTEIRO;

typedef struct {
    PONTEIRO inicio;
    PONTEIRO fim;
} FILA;

//Função que inicia a fila
void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Função que retorna a quantidade de itens na pilha
int getSize(FILA* f) {
    //Primeiro elemento
    PONTEIRO elemento = f->inicio;
    int tam = 0;

    //Percorre todos os elementos e soma +1 para cada um na variavel tam
    while (elemento != NULL) {
        tam++;
        elemento = elemento->proximo;
    }

    return tam;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirFila(FILA* f) {
    printf("{\"Fila\": [");
    PONTEIRO elemento = f->inicio;
    
    // Loop que pecorre a lista printando cada um
    while (elemento != NULL) {
        
        printf(
            "\n\t{ \"Registro\": { \"chave\": %i \"valor\": %i } }%s", 
            elemento->registro.chave,
            elemento->registro.valor,
            (elemento->proximo != NULL) ? "," : ""
        );

        elemento = elemento->proximo;
    }

    printf("]}\n");
}

// Função que adiciona um registro na fila
bool iniserirRegistro(FILA* f, REGISTRO reg) {
    PONTEIRO novo = (PONTEIRO) malloc(sizeof(ELEMENTO));

    novo->registro = reg;
    novo->proximo = NULL;

    if (f->inicio == NULL)
        f->inicio = novo;
    else 
        f->fim->proximo = novo;
    
    f->fim = novo;

    return true;
}

// Função que remove o ultimo registro e retorna de maneira opcional o mesmo
bool removerRegistro(FILA* f, REGISTRO* reg) {
    if (f->inicio == NULL) return false;

    PONTEIRO apagar =  f->inicio;
    if (reg != NULL) *reg = apagar->registro;


    f->inicio = apagar->proximo;
    if (f->inicio == NULL) f->fim = NULL;

    free(apagar);

    return true;
}

//Função que apaga todos os itens na fila e inicia ela novamente
void reinicializarFila(FILA* f) {
    PONTEIRO elemento = f->inicio;
    while (elemento != NULL) {
        PONTEIRO apagar = elemento;
        elemento = elemento->proximo;
        free(apagar);
    }

    inicializarFila(f);
}


int main() {
    // Aloca a FILA na memoria
    FILA* f = (FILA*) malloc(sizeof(FILA));

    // Adiciona uma seed para a geração de numeros aleatorios 
    srand((unsigned) &f);

    //inicia a fila
    inicializarFila(f);

    // Loop que adiciona valores aleatorios a FILA
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .chave = i,
            .valor = rand()
        };

       if (!iniserirRegistro(f, reg)) {
           printf(
               "Erro ao adicionar o registro { %i, %i } \n",
               reg.chave,
               reg.valor
           );

           return 1;
       }
            
    }

    // Printa a FILA
    exibirFila(f);

    printf("Totalizando %i Registros \n", getSize(f));

    printf("Removendo elemento da fila \n");
    REGISTRO antigo;
    if (!removerRegistro(f, &antigo)) {
        printf(
            "Erro ao remover elemento"
        );
    }

    printf("Agora temos %i elementos \n", getSize(f));

    // recoloca o ultimo elemento
    antigo.valor = rand();
    printf("recolocando o registro com valor %i \n", antigo.valor);
    if (!iniserirRegistro(f, antigo)) {
        printf("Erro ao recolocar o registro \n");

        return 1;
    }

    printf("voltamos a ter %i elementos \n", getSize(f));

    // Limpa a Lista
    reinicializarFila(f);

    printf("Fila reiniciada \n");
    exibirFila(f);

    return 0;
}
