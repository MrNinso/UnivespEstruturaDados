/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploPilhas.c
*/
#define MAX 50
#define INVALIDO -1

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

typedef struct {
    int valor;
} REGISTRO;

typedef struct {
    REGISTRO registros[MAX];
    int topo; 
} PILHA;

// Função que reseta a pilha
void resetarPilha(PILHA* p) {
    p->topo = INVALIDO;
}

// Função que retorna a quantidade de itens na pilha
int getSize(PILHA* p) {
    return p->topo + 1;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirPilha(PILHA* p) {
    printf("{\"Pilha\": [");

    // Loop que pecorre a lista printando cada um
    for(int i = p->topo; i >= 0; i--) {
        REGISTRO registro = p->registros[i];
        
        printf(
            "\n\t{ \"Registro\": { \"valor\": %i } }%s", 
            registro.valor,
            (i != 0) ? "," : ""
        );
    }

    printf("]}\n");
}

// Função que adiciona um registro a pilha
// no caso da pilha todos os registros são adicionados no inicio dela
bool push(PILHA* p, REGISTRO reg) {
    if (p->topo >= MAX-1)
        return false;
    
    p->topo++;

    p->registros[p->topo] = reg;

    return true;
}

// Função que remove o ultimo registro e retorna de maneira opcional o mesmo
bool pop(PILHA* p, REGISTRO* reg) {
    if (p->topo == INVALIDO)
        return false;
    
    if (reg != NULL) {
        *reg = p->registros[p->topo];
    }

    p->topo = p->topo-1;

    return true;
}

int main(void) {
    // Aloca a LISTA na memoria
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));

    //Adiciona uma seed para a geração de numeros aleatorios
    srand((unsigned) &p);

    //inicia a pilha
    resetarPilha(p);

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
    resetarPilha(p);

    printf("Lista reiniciada \n");
    exibirPilha(p);

    return 0;
}