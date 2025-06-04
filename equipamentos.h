#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h" 

// —— Struct de Reserva ——————————————————————————————— 
typedef struct Reserva {
    int id;
    char nome[50];
    char data[11]; // formato "dd/mm/aaaa"
    char hora[6];  // formato "hh:mm"
    struct Reserva* prox;
} Reserva;

// —— Struct de Equipamento ———————————————————————————
typedef struct Equipamento {
    int codigo;
    char tipo[20];
    char descricao[100];
    Reserva* reservas;
} Equipamento;

// Protótipos de utilitários:
int normalizeData(const char *raw, char *out);
int normalizeHora(const char *raw, char *out);

// Autor: Thiago Tanaka
/* Função para criar um novo equipamento 
Recebe o ponteiro para o cabeçalho de tipos (TipoEquipamento*),
faz o cadastro e insere o novo Equipamento dentro da lista de tipo apropriada.
*/
Tipo* cadastrarEquipamento(Tipo* listaTipos);

// Autor: Thiago Tanaka
/* Função para reservar um equipamento
Recebe a lista de cabeçalhos de tipo, pede código do equipamento e dados da reserva;
procura o equipamento e insere uma nova Reserva no início da lista de reservas do Equipamento,
após checar conflito de data/hora.
*/
Tipo* reservarEquipamento(Tipo* listaTipos);

// Autor: Thiago Tanaka
/* Fução para cancelar uma reserva existente
Recebe a lista de cabeçalhos de tipo, pede código/data/hora;
procura o Equipamento, percorre sua lista de reservas, e
remove a reserva que bate com data+hora (se houver).
*/
Tipo* cancelarReserva(Tipo* listaTipos);

// debbug only
void listarEquipamentos(Tipo* listaTipos);

// Prototipo externo chamado por exibirListaPorTipo (lista.c)
void exibirEquipamento(Equipamento* equip);

// Autor: Paulo Roberto Schiochet 
// Essas funçoes são para contar reservas;
int contarReservasDoTipo(Tipo* listaTipos, const char* nomeTipo);
int contarReservasNaData(Tipo* listaTipos, const char* data);

#endif
