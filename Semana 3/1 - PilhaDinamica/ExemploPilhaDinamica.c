/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploPilhasDinamica.c
*/
#define MAX 50

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

typedef int CHAVE;

typedef struct{
    int valor;
} REGISTRO;

typedef struct aux {
    REGISTRO registro;
    struct aux* proximo;
} ELEMENTO;

typedef ELEMENTO* PONTEIRO;

typedef struct {
    PONTEIRO topo;
} PILHA;

//Função que inicia a pilha
void iniciarPilha(PILHA* p) {
    p->topo = NULL;
}

// Função que retorna a quantidade de itens na pilha
int getSize(PILHA* p) {
    //Primeiro elemento
    PONTEIRO elemento = p->topo;
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
void exibirPilha(PILHA* p) {
    PONTEIRO elemento = p->topo;
    printf("{\"Pilha\": [");
    
    // Loop que pecorre a lista printando cada um
    while (elemento != NULL) {
        PONTEIRO e = elemento;
        elemento = elemento->proximo;

        printf(
            "\n\t{ \"Registro\": { \"valor\": %i } }%s",
            e->registro.valor,
            (elemento != NULL) ? "," : ""
        );
    }

    printf("]} \n");
}

// Função que adiciona um registro a pilha
// no caso da pilha todos os registros são adicionados no inicio dela
bool push(PILHA* p, REGISTRO reg) {
    PONTEIRO novo = (PONTEIRO) malloc(sizeof(ELEMENTO));
    novo->registro = reg;
    novo->proximo = p->topo;
    p->topo = novo;

    return true;
}

// Função que remove o ultimo registro e retorna de maneira opcional o mesmo
bool pop(PILHA* p, REGISTRO* reg) {
    if (p->topo == NULL) return false;

    if (reg != NULL) *reg = p->topo->registro;

    PONTEIRO apagar = p->topo;
    p->topo = p->topo->proximo;

    free(apagar);

    return true;
}

//Função que apaga todos os itens na pilha e inicia ela novamente
void reinicializarPilha(PILHA* p) {
    PONTEIRO posicao = p->topo;

    while (posicao != NULL) {
        PONTEIRO apagar = posicao;
        posicao = posicao->proximo;
        free(apagar);
    }

    iniciarPilha(p);
}

int main(void) {
    // Aloca a PILHA na memoria
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));

    //Adiciona uma seed para a geração de numeros aleatorios
    srand((unsigned) &p);

    //inicia a pilha
    iniciarPilha(p);

    // Loop que adiciona valores aleatoris a pilha
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .valor = rand()
        };

        if (!push(p, reg)) {
            printf(
               "Erro ao adicionar o registro { %i, %i } \n",
               i,
               reg.valor
           );

           return 1;
        }
    }

    // Printa a pilha
    exibirPilha(p);

    printf("Totalizando %i Registros \n", getSize(p));

    //Remove o ultimo item
    printf("Removendo o ultimo item \n");
    REGISTRO antigo;

    if (!pop(p, &antigo)) {
        printf(
            "Erro ao remover item \n"
        );
        return 1;
    }

    printf("Agora temos %i registros \n", getSize(p));

    // recoloca o ultimo item
    antigo.valor = rand();
    printf("recolocando o registro com valor %i \n", antigo.valor);
    if (!push(p, antigo)) {
        printf("Erro ao recolocar o registro \n");

        return 1;
    }

    printf("voltamos a ter %i registros \n", getSize(p));

    // Limpa a Lista
    reinicializarPilha(p);

    printf("Lista reiniciada \n");
    exibirPilha(p);

    return 0;
}