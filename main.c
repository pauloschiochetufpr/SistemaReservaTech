#include <stdio.h>
#include <stdlib.h>
#include "equipamentos.h"
#include "lista.h"

void menu() {
    printf("\n=== Sistema de Reservas de Equipamentos ===\n");
    printf("Escolha uma opcao: \n");
    printf("1 - Cadastrar Tipo\n");
    printf("2 - Cadastrar Equipamento\n");
    printf("3 - Reservar Equipamento\n");
    printf("4 - Listar Reservas por Tipo\n");
    printf("5 - Consultar Reservas por Data\n");
    printf("6 - Cancelar Reserva\n");
    printf("7 - Exibir Historico por Tipo\n");
    printf("8 - Exibir Todos os Tipos e Equipamentos\n");
    printf("0 - Sair\n");
    printf("\n");
}

int main() {
    Tipo* lista = criarLista();  

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar();  

        switch (opcao) {
            case 1: {
                printf("\n");
                char nomeTipo[100];
                printf("Informe o nome do tipo: ");
                scanf(" %99[^\n]", nomeTipo);
                if (inserirTipo(&lista, nomeTipo)) {
                    printf("Tipo '%s' cadastrado com sucesso!\n", nomeTipo);
                } else {
                    printf("Tipo '%s' ja existe e nao sera cadastrado novamente.\n", nomeTipo);
                }
                break;
                }
            case 2:
                printf("\n");
                lista = cadastrarEquipamento(lista);
                break;
            case 3:
                printf("\n");
                lista = reservarEquipamento(lista);
                break;
            case 4:
                printf("\n");
                listarReservasPorTipo(lista);
                break;
            case 5:
                printf("\n");
                consultarReservasPorData(lista);
                break;
            case 6:
                printf("\n");
                lista = cancelarReserva(lista);
                break;
            case 7:
                printf("\n");
                exibirHistoricoPorTipo(lista);
                break;
            case 8:
                printf("\n");
                exibirListaPorTipo(lista);
                break;

            case 0: 
                printf("\n");
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarListaTipos(lista); 

    return 0;
}