/*
    para compilar esse exemplo use o comando no terminal:
    
    $ gcc ExemploLista.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

#define MAX 50

typedef int CHAVE;

typedef struct {
    CHAVE chave;
    int valor;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int nroElem;
} LISTA;

// Função que inicia a lista
void iniciarLista(LISTA* l) {
    l->nroElem = 0;
}

// Função que reinicia a lista para ser reutilizada
void reiniciarLista(LISTA* l) {
    l->nroElem = 0;
}

// Função que retorna a quantidade de itens na lista
int getSize(LISTA* l) {
    return l->nroElem;
}

// Função que printa os valores de uma lista
void exibirLista(LISTA* l) {
    int i;

    printf("Lista: \" ");

    // Loop que passa item por item printando os valores de cada um
    for (i=0; i < getSize(l); i++) 
        printf("{ %i, %i }, ", l->A[i].chave, l->A[i].valor);
    
    printf("\" \n");
}

// Função que retorna a posição de um registro na lista com uma determinada chave
int getIndex(LISTA* l, CHAVE chave) {
    int i = 0;

    // Loop que passa por cada registro verificando se a chave é a mesma da passada
    // caso ele ache o registro retorna a posição do registro
    while (i < getSize(l)) {
        if (chave == l->A[i].chave)
            return i;
        
        i++;
    }

    // Caso ele não encontre ele vai retornar -1, por ser uma posição invalida
    return -1;
}

// Função que adiciona um registro a lista em uma posição determinada
bool addRegistro(LISTA* l, REGISTRO registro, int pos) {
    // Verifica se o valor é uma posição valida
    if ( (getSize(l) == MAX) || (pos < 0) || (pos > getSize(l)) )
        return false;
    
    int j;

    // Move todos os itens depois da posição determinada para direita para liberar a posição desejada
    for (j =  getSize(l); j > pos; j--) 
            l->A[j] = l->A[j-1];
    
    l->A[pos] = registro;
    l->nroElem++;

    return true;
}

// Função que remove um registro usando uma chave para determinar
bool removeRegistro(LISTA* l, CHAVE chave) {
    int pos, j;

    // Procura a posição do item a ser removido
    pos = getIndex(l, chave);
    
    // Verifica se ele encontrou o item
    if (pos == -1)
        return false;
    
    // Loop que remove o item e move os itens seguinte para a esquerda
    for (j = pos; j < getSize(l)-1; j++)
        l->A[j] = l->A[j+1];
    
    l->nroElem--;

    return true;
}

// Teste das funções
int main() {
    LISTA* l = (LISTA*) malloc(sizeof(LISTA));

    // Adiciona uma seed para a geração de numeros aleatorios 
    srand((unsigned) &l);

    iniciarLista(l);

    // Loop que adiciona valores aleatorios a lista
    for (int i = 0; i < MAX; i++) {
        REGISTRO reg = {
            chave: i,
            valor: rand()
        };

       if (!addRegistro(l, reg, getSize(l))) {
           printf(
               "Erro ao adicionar o registro { %i, %i } na posição %i \n",
               reg.chave,
               reg.valor,
               getSize(l)
           );

           return 1;
       }
            
    }

    // Printa a lista
    exibirLista(l);

    printf("Totalizando %i Registros \n", getSize(l));

    //Remove um item aleatorio
    CHAVE chaveAleatotia = (rand() % 50);

    printf("Removendo item %i \n", chaveAleatotia);

    if (!removeRegistro(l, chaveAleatotia)) {
        printf(
            "Erro ao remover item de chave %i \n",
            chaveAleatotia
        );
    }

    printf("Agora temos %i registros \n", getSize(l));

    // Limpa a Lista
    reiniciarLista(l);

    printf("Lista reiniciada \n");
    exibirLista(l);

    return 0;
}

