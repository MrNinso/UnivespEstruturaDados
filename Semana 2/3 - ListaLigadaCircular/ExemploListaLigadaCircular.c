/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploListaLigadaCircular.c
*/
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX 50

typedef int CHAVE;

typedef struct{
    CHAVE chave;
    int valor;
} REGISTRO;

typedef struct aux {
    REGISTRO registro;
    struct aux* proximo;
} ELEMENTO;

typedef ELEMENTO* PONTEIRO;

typedef struct{
    PONTEIRO cabeca;
} LISTA;

// Função que inicia a LISTA fazendo a cabeca apontar para ela mesma
void iniciarLista(LISTA* l) {
    l->cabeca = (PONTEIRO) malloc(sizeof(ELEMENTO));
    l->cabeca->proximo = l->cabeca;
}

// Função que retorna a quantidade de itens na lista
int getSize(LISTA* l) {
    // Pego a posição inicial da lista
    PONTEIRO i = l->cabeca->proximo;
    int size = 0;

    // Loop que pecorre a lista ate acha o ultimo item onde seu valor de proximo é o mesmo da cabeca
    while (i != l->cabeca) {
        size++;
        i = i->proximo;
    }

    return size;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirLista(LISTA* l) {
    PONTEIRO i = l->cabeca->proximo;
    printf("{\"Lista\": [");
    
    // Loop que pecorre a lista printando cada um
    while (i != l->cabeca) {
        ELEMENTO elemento = *i;
        i = elemento.proximo;
        
        printf(
            "\n\t{ \"Registro\": { \"chave\": %i, \"valor\": %i }, \"Proximo\": %i }%s", 
            elemento.registro.chave,
            elemento.registro.valor,
            (int) elemento.proximo,
            (i != l->cabeca) ? "," : ""
        );
    }

    printf("]}\n");
}

// Função que retorna a posição na memoria de um registro na lista com uma determinada chave
// de maneira opcional pode ser passado a posição na memoria de um ponteiro para salvar o
// o registro anterior, caso contrario apenas passar NULL
PONTEIRO buscaSentinela(LISTA* l, CHAVE ch, PONTEIRO* anterior) {
    PONTEIRO i = l->cabeca->proximo;
    l->cabeca->registro.chave = ch;
    
    // Caso tenha sido passado a posição do PONTEIRO anterior ele inica o PONTEIRO
    if (anterior != NULL)
        *anterior = l->cabeca;

    // Loop que percorre a lista ate o registro final, ou o que bate com a chave determinada
    while (i->registro.chave != ch) {
        // Caso tenha sido passado a posição do PONTEIRO anterior ele salva o valor
        if (anterior != NULL)
            *anterior = i;
        i = i->proximo;
    }

    if (i != l->cabeca)
        return i;

    return NULL;
}

//Função que adiciona um registro a lista
bool inserirElemento(LISTA* l, REGISTRO reg) {
    PONTEIRO anterior, i;

    // Verifica se o registro existe e já pega o valor do anterior que se caso não existir vai
    // vai ser o ultimo item da lista
    i = buscaSentinela(l, reg.chave, &anterior);
    if (i != NULL)
        return false;
    
    // Aloca o PONTEIRO na memoria
    i = (PONTEIRO) malloc(sizeof(ELEMENTO));

    i->registro = reg;

    // Atualiza os campos proximo
    i->proximo = anterior->proximo;
    anterior->proximo  = i;

    return true;
}

// Função que remove o registro com a chave determinada
bool excluirElemento(LISTA* l, CHAVE ch) {
    PONTEIRO anterior, i;

    // Verifica se o registro existe e já pega o valor do anterior que se caso não existir vai
    // vai ser o ultimo item da lista
    i = buscaSentinela(l, ch, &anterior);
    if (i == NULL)
        return false;

    // Atualiza os campo Proximo
    anterior->proximo  = i->proximo;
    
    // Libera o espaço na memoria
    free(i);

    return true;
}

// Função que reinicia a Lista limpando todos os registros na memorias
void reiniciarLista(LISTA* l) {
    PONTEIRO i = l->cabeca->proximo;
    
    
    while (i != l->cabeca) {
        PONTEIRO apagar = i;
        i = i->proximo;
        free(apagar);
    }

    l->cabeca->proximo = l->cabeca;
}


int main() {
    // Aloca a LISTA na memoria
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));
    //inicia a Lista
    srand((unsigned) &l);

    //inicia a Lista
    iniciarLista(l);

    // Loop que adiciona valores aleatoris a lista
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .chave = i,
            .valor = rand()
        };

        if  (!inserirElemento(l, reg)) {
            printf(
               "Erro ao adicionar o registro { %i, %i } \n",
               reg.chave,
               reg.valor
           );

           return 1;
        }
    }

    // Printa a lista
    exibirLista(l);

    printf("Totalizando %i Registros \n", getSize(l));

    //Remove um item aleatorio
    CHAVE chaveAleatotia = (rand() % MAX);

    printf("Removendo item %i \n", chaveAleatotia);

    if (!excluirElemento(l, chaveAleatotia)) {
        printf(
            "Erro ao remover item de chave %i \n",
            chaveAleatotia
        );
        return 1;
    }

    printf("Agora temos %i registros \n", getSize(l));
    
    // Coloca um registro novo no lugar do que foi deletado 
    REGISTRO reg =  {
        .chave = chaveAleatotia,
        .valor =  rand()
    };

    printf("recolocando o registro de chave %i com valor %i \n", reg.chave, reg.valor);
    
    if (!inserirElemento(l, reg)) {
        printf(
            "Erro ao adicionar o registro { %i, %i } \n",
            reg.chave,
            reg.valor
        );

        return 1;
    }

    printf("voltamos a ter %i registros \n", getSize(l));

    // Limpa a Lista
    reiniciarLista(l);

    printf("Lista reiniciada \n");
    exibirLista(l);

    return 0;
}
