#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "equipamentos.h"  
#include <ctype.h>  // Para usar tolower

//implementações das funçõeS
Tipo* criarLista(){
    return NULL;
}

//Percorre cada No da lista de tipos, comparando com o nome desejado até encontrar. Retorna NULL caso não existe o nome
Tipo* buscarTipo(Tipo** lista, const char* nomeTipo) {
    Tipo* atual = *lista;
    while (atual != NULL) {
        if (strcasecmp(atual->tipo, nomeTipo) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

//Essa aqui eu nao sei se realmente é aq, qlq coisa so mandar la pro outro codigo
Equipamento* buscarEquipamento(Tipo* lista, int codigo) {
    Tipo* tipoAtual = lista;
    while (tipoAtual != NULL) {
        No* noAtual = tipoAtual->listaEquipamentos;
        while (noAtual != NULL) {
            if (noAtual->equipamento->codigo == codigo) {
                return noAtual->equipamento; // Equipamento encontrado
            }
            noAtual = noAtual->prox;
        }
        tipoAtual = tipoAtual->prox;
    }
    return NULL; // Equipamento não encontrado
}

// Insere um equipamento na lista ligada a um tipo que ja existe
void inserirEquipamento(Tipo* tipo, Equipamento* nomeEquipamento) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) return; // retorna nada se houver erro na alocação
    novoNo->equipamento = nomeEquipamento;
    novoNo->prox = tipo->listaEquipamentos; // insere no começo da lista
    tipo->listaEquipamentos = novoNo;
}

//Função para que o Caps Lock não interfira no tipo 
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Insere um novo tipo na lista se ainda não existir, retornando o ponteiro para o tipo
//Insere o No tipo no começo da lista, usa a funçao de buscar tipo pra verificar se o tipo a ser inserido ja existe. 
//Inicializa uma lista vazia para o tipo criado. Atualiza os ponteiros para apontar para o novo tipo criado, que esta no inicio
int inserirTipo(Tipo** lista, const char* nomeTipo) {
    Tipo* existe = buscarTipo(lista, nomeTipo);
    if (existe != NULL) {
        return 0;  // Já existe
    }

    Tipo* novoTipo = (Tipo*) malloc(sizeof(Tipo));
    if (!novoTipo) {
        return 0;  // Falha de alocação
    }

    strncpy(novoTipo->tipo, nomeTipo, sizeof(novoTipo->tipo) - 1);
    novoTipo->tipo[sizeof(novoTipo->tipo) - 1] = '\0';
    toLowerCase(novoTipo->tipo);
    novoTipo->listaEquipamentos = NULL;
    novoTipo->prox = *lista;
    *lista = novoTipo;

    return 1;  // Inserido com sucesso
}

// Remove um equipamento pelo código de todas as listas
void removerEquipamento(Tipo* lista, int codigo) {
    Tipo* tipoAtual = lista;
    while (tipoAtual != NULL) {
        No* anterior = NULL;
        No* atual = tipoAtual->listaEquipamentos;

        while (atual != NULL) {
            if (atual->equipamento->codigo == codigo) {
                if (anterior == NULL) {
                    tipoAtual->listaEquipamentos = atual->prox; // Primeiro da lista
                } else {
                    anterior->prox = atual->prox; // Meio ou final
                }
                free(atual->equipamento);
                free(atual);
                return;
            }
            anterior = atual;
            atual = atual->prox;
        }
        tipoAtual = tipoAtual->prox;
    }
}

// Exibe todos os tipos e os equipamentos pertencentes a cada tipo
void exibirListaPorTipo(Tipo* lista) {
    if (lista == NULL) {
        printf("Nenhum tipo de equipamento foi cadastrado ainda.\n");
        return;
    }
    
    Tipo* tipoAtual = lista;
    while (tipoAtual != NULL) {
        printf("Tipo: %s\n", tipoAtual->tipo);
        No* noAtual = tipoAtual->listaEquipamentos;
        while (noAtual != NULL) {
            exibirEquipamento(noAtual->equipamento); // Função definida externamente
            noAtual = noAtual->prox;
        }
        tipoAtual = tipoAtual->prox;
    }
}

// Libera toda a memória alocada para tipos e seus equipamentos
void liberarListaTipos(Tipo* lista) {
    while (lista != NULL) {
        Tipo* proxTipo = lista->prox;
        No* noAtual = lista->listaEquipamentos;

        while (noAtual != NULL) {
            No* proxNo = noAtual->prox;
            free(noAtual->equipamento);
            free(noAtual);
            noAtual = proxNo;
        }

        free(lista);
        lista = proxTipo;
    }
}