/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploFila.c
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

typedef struct {
    REGISTRO registros[MAX];
    int inicio;
    int nroElem;
} FILA;

// Função que reseta a fila
void resetarFila(FILA* f) {
    f->inicio = 0;
    f->nroElem = 0;
}

// Função que retorna a quantidade de itens na fila
int getSize(FILA* f) {
    return f->nroElem;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirFila(FILA* f) {
    printf("{\"Fila\": [");

    int i = f->inicio;
    // Loop que pecorre a lista printando cada um
    for (int temp = 0; temp < f->nroElem; temp++) {
        
        printf(
            "\n\t{ \"Registro\": { \"chave\": %i \"valor\": %i } }%s", 
            f->registros[i].chave,
            f->registros[i].valor,
            ((temp + 1) != f->nroElem) ? "," : ""
        );

        i = ( i + 1) % MAX;
    }

    printf("]}\n");
}

// Função que adiciona um registro a fila
bool iniserirRegistro(FILA* f, REGISTRO reg) {
    if (f->nroElem >= MAX) return false;

    int posicao = (f->inicio + f->nroElem) % MAX;

    f->registros[posicao] = reg;
    f->nroElem++;

    return true;
}

// Função que remove o primeiro registro da fila e retorna de maneira opcional o mesmo
bool removerRegistro(FILA* f, REGISTRO* reg) {
    if (f->nroElem == 0) return false;

    if (reg != NULL) *reg = f->registros[f->inicio];

    f->inicio = (f->inicio+1) % MAX;
    f->nroElem--;

    return true;
}


int main() {
    // Aloca a FILA na memoria
    FILA* f = (FILA*) malloc(sizeof(FILA));

    // Adiciona uma seed para a geração de numeros aleatorios 
    srand((unsigned) &f);

    resetarFila(f);

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


    printf("Removendo registro da fila \n");
    REGISTRO antigo;
    if (!removerRegistro(f, &antigo)) {
        printf(
            "Erro ao remover registro"
        );
    }

    printf("Agora temos %i registros \n", getSize(f));

    // recoloca o ultimo registro excluida
    antigo.valor = rand();
    printf("recolocando o registro com valor %i \n", antigo.valor);
    if (!iniserirRegistro(f, antigo)) {
        printf("Erro ao recolocar o registro \n");

        return 1;
    }

    printf("voltamos a ter %i registros \n", getSize(f));

    // Limpa a fila
    resetarFila(f);

    printf("Fila reiniciada \n");
    exibirFila(f);

    return 0;
}
