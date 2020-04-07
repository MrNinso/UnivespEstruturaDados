/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploDeque.c
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
    struct aux* anterior;
    struct aux* proximo;
} ELEMENTO;

typedef ELEMENTO* PONTEIRO;

typedef struct {
    PONTEIRO cabeca;
} DEQUE;

//Função que inicia o deque
void inicializarDeque(DEQUE* d) {
    d->cabeca = (PONTEIRO) malloc(sizeof(ELEMENTO));
    d->cabeca->proximo = d->cabeca;
    d->cabeca->anterior = d->cabeca;
}
// Função que retorna a quantidade de elementos no deque
int getSize(DEQUE* d) {
    PONTEIRO elemento = d->cabeca->proximo;
    int tam = 0;

    while (elemento != d->cabeca) {
        tam++;
        elemento = elemento->proximo;
    }

    return tam;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirDeque(DEQUE* d) {
    PONTEIRO elemento = d->cabeca->proximo;
    printf("{\"DEQUE\": [");

    // Loop que pecorre a lista printando cada um
    while (elemento != d->cabeca) {
        PONTEIRO e = elemento;
        elemento = elemento->proximo;

        printf(
            "\n\t{ \"Elemento\": { \"Registro\": { \"chave\": %i, \"valor\": %i } } }%s",
            e->registro.chave,
            e->registro.valor,
            (elemento != NULL) ? "," : ""
        );
    }

    printf("]} \n");
}

//Função que adiciona um registro no fim do deque
bool inserirRegistroFim(DEQUE* d, REGISTRO reg) {
    PONTEIRO novo = (PONTEIRO) malloc(sizeof(ELEMENTO));
    novo->registro = reg;
    novo->proximo = d->cabeca;
    novo->anterior = d->cabeca->anterior;
    d->cabeca->anterior = novo;
    novo->anterior->proximo = novo;

    return true;
}

//Função que adiciona um registro no inicio do deque
bool removerRegistroInicio(DEQUE* d, REGISTRO* reg) {
    if (d->cabeca->proximo == d->cabeca) return false;
    PONTEIRO apagar = d->cabeca->proximo;

    if (reg != NULL) *reg = apagar->registro;

    d->cabeca->proximo = apagar->proximo;
    apagar->proximo->anterior = d->cabeca;

    return true;
}

//Função que apaga todos os itens na pilha e inicia ela novamente
void reinicializarDeque(DEQUE* d) {
    PONTEIRO posicao = d->cabeca->proximo;

    while (posicao != d->cabeca) {
        PONTEIRO apagar = posicao;
        posicao = posicao->proximo;
        free(apagar);
    }

    d->cabeca->proximo = d->cabeca;
    d->cabeca->anterior = d->cabeca;
}

int main(void) {
    // Aloca o DEQUE na memoria
    DEQUE* d = (DEQUE*) malloc(sizeof(DEQUE));

    //Adiciona uma seed para a geração de numeros aleatorios
    srand((unsigned) &d);

    //inicia o deque
    inicializarDeque(d);

    // Loop que adiciona valores aleatoris o deque
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .chave = i,
            .valor = rand()
        };

        if (!inserirRegistroFim(d, reg)) {
            printf(
               "Erro ao adicionar o registro {\"Chave\": %i, \"Valor\": %i } \n",
               reg.chave,
               reg.valor
           );

           return 1;
        }
    }

    // Printa o deque
    exibirDeque(d);

    printf("Totalizando %i Registros \n", getSize(d));

    //Remove um elemento
    printf("Removendo um elemento \n");
    REGISTRO antigo;

    if (!removerRegistroInicio(d, &antigo)) {
        printf(
            "Erro ao remover elemento \n"
        );
        return 1;
    }

    printf("Agora temos %i elementos \n", getSize(d));

    // recoloca o ultimo removido elemento
    antigo.valor = rand();
    printf("recolocando o registro com valor %i \n", antigo.valor);
    if (!inserirRegistroFim(d, antigo)) {
        printf("Erro ao recolocar o registro \n");

        return 1;
    }

    printf("voltamos a ter %i elementos \n", getSize(d));

    // Limpa o deque
    reinicializarDeque(d);

    printf("Deque reiniciada \n");
    exibirDeque(d);

    return 0;
}