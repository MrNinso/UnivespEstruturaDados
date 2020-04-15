/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploPilhasDupla.c
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
    int topo1; 
    int topo2;
} PILHADUPLA;

// Função que reseta a pilha
void resetarPilha(PILHADUPLA* p) {
    p->topo1 = INVALIDO;
    p->topo2 = MAX;
}

// Função que retorna a quantidade de itens nas pilhas
int getSize(PILHADUPLA* p) {
    return p->topo1 + 1 + MAX - p->topo2;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirPilha(PILHADUPLA* p, bool isPilha1) {

    printf("{\"Pilha_%i\": [", (isPilha1) ? 1 : 2);

    // Loops que pecorre a pilha 1 printando cada um
    if (isPilha1)
        for(int i = p->topo1; i >= 0; i--) {
            REGISTRO registro = p->registros[i];
            
            printf(
                "\n\t{ \"Registro\": { \"valor\": %i } }%s", 
                registro.valor,
                (i != 0) ? "," : ""
            );
        }
    else
        for(int i = p->topo2; i < MAX; i++) {
            REGISTRO registro = p->registros[i];
            
            printf(
                "\n\t{ \"Registro\": { \"valor\": %i } }%s", 
                registro.valor,
                (i != MAX-1) ? "," : ""
            );
        }

    printf("]}\n");
}

// Função que adiciona um registro a pilha
// no caso da pilha todos os registros são adicionados no inicio dela
bool push(PILHADUPLA* p, REGISTRO reg, bool isPilha1) {
    
    if (getSize(p) >= MAX)
        return false;
    
    if (isPilha1) {
        p->topo1 = p->topo1+1;
        p->registros[p->topo1] = reg;
    } else {  
        p->topo2 = p->topo2-1;
        p->registros[p->topo2] = reg;
    }

    return true;
}

// Função que remove o ultimo registro e retorna de maneira opcional o mesmo
bool pop(PILHADUPLA* p, REGISTRO* reg,  bool isPilha1) {
    if (isPilha1) {
        if (p->topo1 == INVALIDO) return false;
        if (reg != NULL) *reg = p->registros[p->topo1];
        p->topo1 = p->topo1 - 1;
    } else {
        if (p->topo2 == MAX) return false;
        if (reg != NULL) *reg = p->registros[p->topo2];
        p->topo2 = p->topo2 + 1;
    }

    return true;
}

int main(void) {
    // Aloca a PILHA na memoria
    PILHADUPLA* p = (PILHADUPLA*) malloc(sizeof(PILHADUPLA));

    //Adiciona uma seed para a geração de numeros aleatorios
    srand((unsigned) &p);

    //inicia a pilha
    resetarPilha(p);

    // Loop que adiciona valores aleatoris a pilha sendo os valores gerados com i par indo para pilha 1 e os impares para pilha 2
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .valor = rand()
        };

        if (!push(p, reg, (i%2 == 0))) {
            printf(
               "Erro ao adicionar o registro { %i, %i } \n",
               i,
               reg.valor
           );

           return 1;
        }
    }

    // Printa a pilha
    exibirPilha(p, true);
    exibirPilha(p, false);

    printf("Totalizando %i Registros \n", getSize(p));

    for (int i = 1; i <= 2; i++) {
        //Remove o ultimo item
        printf("Removendo o topo da pilha %i  \n", i);
        REGISTRO antigo;

        if (!pop(p, &antigo, (i == 1))) {
            printf(
                "Erro ao remover item  da pilha %i\n",
                i
            );
            return 1;
        }

        printf("Agora temos %i registros na pilha %i \n", getSize(p), i);

        // recoloca o ultimo item
        antigo.valor = rand();
        printf("recolocando o registro com valor %i na pilha %i\n", antigo.valor, i);
        if (!push(p, antigo, (i == 1))) {
            printf(
                "Erro ao recolocar o registro na pilha %i\n",
                i
            );
            return 1;
        }

        printf("voltamos a ter %i registros na pilha %i \n", getSize(p), i);
    }
    // Limpa a Lista
    resetarPilha(p);

    printf("Lista reiniciada \n");
    exibirPilha(p, true);
    exibirPilha(p, false);

    return 0;
}