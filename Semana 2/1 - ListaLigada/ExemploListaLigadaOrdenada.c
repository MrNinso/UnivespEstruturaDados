/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploListaLigadaOrdenada.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

#define MAX 50
#define INVALIDO -1

typedef int CHAVE;

typedef struct {
    CHAVE chave;
    int valor;
} REGISTRO;

typedef struct {
    REGISTRO registro;
    int proximo;
} ELEMENTO;

typedef struct {
    ELEMENTO elementos[MAX];
    int inicio;
    int disponivel;
} LISTA;

// Função que zera a lista
void resetarLista(LISTA* l) {

    for (int i = 0; i < MAX -1; i++)
        l->elementos[i].proximo = i + 1;

    l->elementos[MAX-1].proximo = INVALIDO;
    l->inicio = INVALIDO;
    l->disponivel = 0;

}
// Função que retorna a quantidade de itens na lista
int getSize(LISTA* l) {
    // Pego a posição inicial da lista
    int i = l->inicio;
    int size = 0;

    // Loop que pecorre a lista ate acha o ultimo item onde seu valor de proximo é INVALIDO
    while (i != INVALIDO) {
        size++;
        i = l->elementos[i].proximo;
    }

    return size;
}

// Função que printa os valores de uma lista no formato json,
// para ver esse formato na pratica use o site: https://jsoneditoronline.org/
void exibirLista(LISTA* l) {
    int i = l->inicio;
    printf("{\"Lista\": [");

    // Loop que passa item por item printando os valores de cada um
    while (i != INVALIDO) {
        ELEMENTO elemento = l->elementos[i];
        i = elemento.proximo;
        
        printf(
            "\n\t{ \"Registro\": { \"chave\": %i, \"valor\": %i }, \"Proximo\": %i }%s", 
            elemento.registro.chave,
            elemento.registro.valor,
            elemento.proximo,
            (i != INVALIDO) ? "," : ""
        );
    }

    printf("]}\n");
}

// Função que retorna a posição de um registro na lista com uma determinada chave
int buscaSequencial(LISTA* l, CHAVE ch) {
    int i = l->inicio;
    while ( i != INVALIDO && l->elementos[i].registro.chave < ch ) {
        i = l->elementos[i].proximo;
        if (l->elementos[i].registro.chave == ch )
            return i;
    }

    return INVALIDO;
}

//Função que retorna a posilção do ultimo item disponivel
// e libera esse espaço para que seja coloca um novo registro
int obterDisponivel(LISTA* l) {
    int resultado = l->disponivel;
    
    if ( l->disponivel != INVALIDO ) 
        l->disponivel = l->elementos[l->disponivel].proximo;

    return resultado;
}

//Função que retorna a posição do item anterior a chave especificada
int obterAnterior(LISTA* l, CHAVE ch) {
    int anterior = INVALIDO;
    int i = l->inicio;

    while ( i != INVALIDO && l->elementos[i].registro.chave < ch ) {
        anterior = i;
        i = l->elementos[i].proximo; 
    }

    return anterior;
}

// Função que adiciona um registro a lista
bool inserirElemento(LISTA* l, REGISTRO reg) {
    //Verifica se tem espaço na lista e se o registro já não esta na lista
    if (l->disponivel == INVALIDO || buscaSequencial(l, reg.chave) != INVALIDO) 
        return false;
    
    // Pega o registro anterior e a posição disponivel para adicioar
    int anterior = obterAnterior(l, reg.chave);
    int i = obterDisponivel(l);

    l->elementos[i].registro = reg;

    //Atualiza o campo proximo do anterior
    if (anterior == INVALIDO) {
        l->elementos[i].proximo = l->inicio;
        l->inicio = i;
    } else {
        l->elementos[i].proximo = l->elementos[anterior].proximo;
        l->elementos[anterior].proximo = i;
    }

    return true;    
}

// Função que adiciona um item para lista de disponiveis
void adicionarDisponivel(LISTA* l, int i) {
    l->elementos[i].proximo = l->disponivel;
    l->disponivel = i;
}

// Função que remove um registro da lista
bool excluirElemento(LISTA* l, CHAVE ch) {
    // Verifica se o registro existe
    int i = buscaSequencial(l, ch);
    if (i == INVALIDO)
        return false;

    int anterior = obterAnterior(l, ch);

    // Remove o registro
    if (anterior == INVALIDO) 
        l->inicio = l->elementos[i].proximo;
    else
        l->elementos[anterior].proximo = l->elementos[i].proximo;

    adicionarDisponivel(l, i);

    return true;
}

int main(void) {
    // Aloca a LISTA na memoria
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));

    //Adiciona uma seed para a geração de numeros aleatorios 
    srand((unsigned) &l);

    //inicia a Lista
    resetarLista(l);

    // Loop que adiciona valores aleatoris a lista
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            .chave = i,
            .valor = rand()
        };

        if (!inserirElemento(l, reg)) {
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

    //Remove um registro aleatorio
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
    resetarLista(l);

    printf("Lista reiniciada \n");
    exibirLista(l);

    return 0;
}