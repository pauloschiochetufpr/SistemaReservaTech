#ifndef LISTA_H
#define LISTA_H

typedef struct Equipamento Equipamento;

// Estrutura de uma Lista Encadeada Simples que armazena os Equipametos
typedef struct No {
    Equipamento* equipamento;   // Ponteiro para o equipamento armazenado no nodo
    struct No* prox;            // Ponteiro para o próximo nodo da lista
} No;

// Estrutura que representa o o cabecalho para a lista de equipamentos desse tipo
typedef struct Tipo {
    char tipo[100];             // ex: notebook, tablet, etc
    No* listaEquipamentos;      // Ponteiro para a lista ligada de equipamentos desse tipo
    struct Tipo* prox;          // Ponteiro para o próximo tipo na lista de tipos
} Tipo;

// Funções
// TADS da lista com cabecalho

// Cria e inicializa uma lista de tipos vazia. Vai retornar NULL
Tipo* criarLista();

// Busca um tipo na lista por nome (tipo). Retorna o ponteiro para o tipo se encontrado e NULL caso não exista o tipo informado
Tipo* buscarTipo(Tipo** lista, const char* tipo);

// Busca um equipamento pelo cod em todas as listas de equipamentos dentro da lista de tipos. Retorna o ponteiro para o equipamento, ou NULL se não encontrado
Equipamento* buscarEquipamento(Tipo* lista, int codigo);

// Insere um equipamento na lista de equipamentos do tipo informado
void inserirEquipamento(Tipo* tipo, Equipamento* equipamento);

//Insere um novo tipo. Se ja existe, retorna o existente
void inserirTipo(Tipo** lista, const char* nome);


// Remove um equipamento pelo cod da lista de tipos, liberando a memoria e ajustando a ordem dos ponteiros
void removerEquipamento(Tipo* lista, int codigo);

// Exibe todos os tipos com os equipamentos ligados
void exibirListaPorTipo(Tipo* lista);

// Libera a memória alocada para a lista de tipos e equipamentos
void liberarListaTipos(Tipo* lista);


#endif
