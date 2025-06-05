#include "equipamentos.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** normalizeData
 *   - Recebe uma string 'raw' contendo dia, mês e ano em algum formato:
 *       • "04062025"
 *       • "4/6/2025"
 *       • "04.06.2025"
 *       • "4-6-25"   (embora, para anos de dois dígitos, sugerimos não usar)
 *       • etc.
 *   - Tenta extrair inteiros dia, mês e ano de 'raw'.
 *   - Se conseguir, escreve em 'out' o formato "DD/MM/AAAA" (sempre com 2 dígitos de dia, 2 de mês e 4 de ano).
 *   - Retorna 1 em sucesso, 0 caso não consiga parsear (ex.: letras no meio, número de dígitos inválido, datas fora de intervalo).
 *
 * 'out' deve ter ao menos 11 bytes disponíveis (10 caracteres + '\0').
 */
int normalizeData(const char *raw, char *out) {
    int dia = 0, mes = 0, ano = 0;
    int len = strlen(raw);

    // 1) Verifica se raw tem exatamente 8 dígitos (e não contém nenhum separador)
    int apenasDigitos = 1;
    if (len == 8) {
        for (int i = 0; i < 8; i++) {
            if (!isdigit((unsigned char)raw[i])) {
                apenasDigitos = 0;
                break;
            }
        }
        if (apenasDigitos) {
            // extrai: raw[0..1] = dia, raw[2..3] = mes, raw[4..7] = ano
            dia = (raw[0] - '0') * 10 + (raw[1] - '0');
            mes = (raw[2] - '0') * 10 + (raw[3] - '0');
            ano =  (raw[4] - '0') * 1000
                 + (raw[5] - '0') * 100
                 + (raw[6] - '0') * 10
                 + (raw[7] - '0');
            // Checa intervalos básicos
            if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1000) {
                return 0;
            }
            sprintf(out, "%02d/%02d/%04d", dia, mes, ano);
            return 1;
        }
    }

    // 2) Caso contrário, tenta usar sscanf consumindo quaisquer separadores não numéricos
    //    A expressão "%d%*[^0-9]%d%*[^0-9]%d" pega três inteiros, ignorando tudo que não for dígito entre eles.
    if (sscanf(raw, "%d%*[^0-9]%d%*[^0-9]%d", &dia, &mes, &ano) == 3) {
        // Se capturou três inteiros, checa intervalos básicos
        if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1000) {
            return 0;
        }
        sprintf(out, "%02d/%02d/%04d", dia, mes, ano);
        return 1;
    }

    // 3) Se chegou aqui, não conseguiu parsear
    return 0;
}

/** normalizeHora:
 *   - Recebe uma string 'raw' contendo hora e minuto em algum formato:
 *       • "0430"   (4 dígitos, sem separador)
 *       • "4:30"   (com dois dígitos e separador :)
 *       • "4.30"   (separador .)
 *       • "430"    (3 dígitos, sem separador)
 *       • "04-30"  (outro separador não numérico)
 *       • etc.
 *   - Tenta extrair inteiros hora e minuto de 'raw'.
 *   - Se conseguir, escreve em 'out' o formato "HH:MM" (sempre com 2 dígitos de hora e 2 de minuto).
 *   - Retorna 1 em sucesso, 0 caso não consiga parsear (ex.: horas ≥ 24, minutos ≥ 60, letras no meio, poucos dígitos).
 *
 * 'out' deve ter ao menos 6 bytes disponíveis (5 caracteres + '\0').
 */
int normalizeHora(const char *raw, char *out) {
    int hora = 0, minuto = 0;
    int len = strlen(raw);

    // 1) Se tiver exatamente 4 dígitos e todos numéricos, considera "HHMM"
    int apenasDigitos = 1;
    if (len == 4) {
        for (int i = 0; i < 4; i++) {
            if (!isdigit((unsigned char)raw[i])) {
                apenasDigitos = 0;
                break;
            }
        }
        if (apenasDigitos) {
            hora   = (raw[0] - '0') * 10 + (raw[1] - '0');
            minuto = (raw[2] - '0') * 10 + (raw[3] - '0');
            if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
                return 0;
            }
            sprintf(out, "%02d:%02d", hora, minuto);
            return 1;
        }
    }

    // 2) Se tiver 3 dígitos e todos numéricos, considera "HMM"
    apenasDigitos = 1;
    if (len == 3) {
        for (int i = 0; i < 3; i++) {
            if (!isdigit((unsigned char)raw[i])) {
                apenasDigitos = 0;
                break;
            }
        }
        if (apenasDigitos) {
            // Exemplo: "430" → hora=4, minuto=30
            hora   = raw[0] - '0';
            minuto = (raw[1] - '0') * 10 + (raw[2] - '0');
            if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
                return 0;
            }
            sprintf(out, "%02d:%02d", hora, minuto);
            return 1;
        }
    }

    // 3) Caso contrário, tenta usar sscanf consumindo separadores não numéricos:
    //    "%d%*[^0-9]%d" lê dois inteiros <hora> e <minuto>, ignorando tudo entre eles.
    if (sscanf(raw, "%d%*[^0-9]%d", &hora, &minuto) == 2) {
        if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
            return 0;
        }
        sprintf(out, "%02d:%02d", hora, minuto);
        return 1;
    }

    // 4) Se nenhum caso funcionar, retorna falha
    return 0;
}

// Implementação de exibirEquipamento, usada por lista.c
void exibirEquipamento(Equipamento* equip) {
    printf("  - Codigo: %d | Descricao: %s\n", equip->codigo, equip->descricao);
// Se quiser listar reservas, poderia fazer aqui (não obrigatório)
}

// Autor: Thiago Tanaka
/* Função para criar um novo equipamento 
Recebe o ponteiro para o cabeçalho de tipos (TipoEquipamento*),
faz o cadastro e insere o novo Equipamento dentro da lista de tipo apropriada.
*/
Tipo* cadastrarEquipamento(Tipo* listaTipos){
    // Aloca memória para um novo equipamento
    Equipamento* novo = (Equipamento*) malloc(sizeof(Equipamento));
    if (!novo) {
        printf("Erro de memoria!\n");
        return listaTipos;
    }

    // Pede os dados para o novo equipamento
    printf("=== Cadastrar Equipamento ===\n");
    printf("Codigo: ");
    scanf("%d", &novo->codigo);

    // **1) Verifica se já existe esse código em algum equipamento**
    if (buscarEquipamento(listaTipos, novo->codigo) != NULL) {
        printf("Erro: ja existe um equipamento cadastrado com codigo %d.\n\n", novo->codigo);
        free(novo);
        return listaTipos;
    }

    printf("Tipo (ex: Notebook, Tablet, Camera, Projetor): ");
    scanf(" %19[^\n]", novo->tipo);
    printf("Descricao: ");
    scanf(" %99[^\n]", novo->descricao);

    // Nenhuma reserva ainda: lista de reservas começa vazia
    novo->reservas = NULL;

    // Verifica se já existe esse tipo cadastrado 
    Tipo* tipoNode = buscarTipo(&listaTipos, novo->tipo);
    if (!tipoNode) {
        // Tipo não existe: avisa e descarta o equipamento
        printf("Erro: tipo '%s' nao cadastrado. Cadastre o tipo antes de adicionar equipamentos.\n\n", novo->tipo);
        free(novo);
        return listaTipos;
    }

    // Insere o novo equipamento na lista de equipamentos do tipo apropriado
    inserirEquipamento(tipoNode, novo);

    printf("Equipamento cadastrado com sucesso!\n\n");
    return listaTipos; 
}

// Autor: Thiago Tanaka
/* Função para reservar um equipamento
Recebe a lista de cabeçalhos de tipo, pede código do equipamento e dados da reserva;
procura o equipamento e insere uma nova Reserva no início da lista de reservas do Equipamento,
após checar conflito de data/hora.
*/
Tipo* reservarEquipamento(Tipo* listaTipos){
    // Verifica se a lista de tipos está vazia
    if (!listaTipos) {
        printf("Nao ha equipamentos cadastrados.\n");
        return listaTipos;
    }

    // Pede dados da reserva
    int codigo;
    printf("=== Reservar Equipamento ===\n");
    printf("Codigo do equipamento: ");
    scanf("%d", &codigo);

    // Procura o equipamento
    Equipamento* eq = buscarEquipamento(listaTipos, codigo);
    if (!eq) {
        printf("Equipamento nao encontrado!\n\n");
        return listaTipos;
    }

    // Cria a reserva e aloca na memória
    Reserva* nova = (Reserva*) malloc(sizeof(Reserva));
    if (!nova) {
        printf("Erro de memoria ao criar reserva.\n\n");
        return listaTipos;
    }

    char dataRaw[20];      // buffer para capturar qualquer formato digitado
    char dataNorm[11];     // buffer final "DD/MM/AAAA"

    // Restante dos dados da reserva
    printf("Nome do solicitante: ");
    scanf(" %49[^\n]", nova->nome);
    printf("Data (DD/MM/AAAA): ");
    scanf(" %19[^\n]", dataRaw);

    // Tenta normalizar
    if (!normalizeData(dataRaw, dataNorm)) {
        printf("Formato de data invalido. Use DD/MM/AAAA (com ou sem separador).\n\n");
        free(nova);
        return listaTipos;
    }
    // Copia a data normalizada para a nova reserva
    strcpy(nova->data, dataNorm);

    char horaRaw[10];  // suficiente para ler “430”, “4:30”, “04:30” etc.
    char horaNorm[6];  // "HH:MM" + '\0'

    printf("Hora (HH:MM): ");
    scanf(" %9[^\n]", horaRaw);

    if (!normalizeHora(horaRaw, horaNorm)) {
        printf("Formato de hora invalido. Use HH:MM (por exemplo, 04:30 ou 430 ou 4:30).\n\n");
        free(nova);
        return listaTipos;
    }
    strcpy(nova->hora, horaNorm);
    nova->prox = NULL;

    // Verifica conflitos de data/hora na lista de reservas desse equipamento
    Reserva* atual = eq->reservas;
    while (atual != NULL) {
        if (strcmp(atual->data, nova->data) == 0 &&
            strcmp(atual->hora, nova->hora) == 0) {
            // Encontrou conflito exato de data+h ora
            printf("Conflito: ja existe uma reserva em %s as %s!\n\n", 
                   nova->data, nova->hora);
            free(nova);
            return listaTipos;
        }
        atual = atual->prox;
    }

    // Se não houver conflitos, adiciona no início da lista de reservas
    nova->prox = eq->reservas;
    eq->reservas = nova;

    printf("Reserva cadastrada com sucesso!\n\n");
    return listaTipos;
}

// Autor: Thiago Tanaka
/* Fução para cancelar uma reserva existente
Recebe a lista de cabeçalhos de tipo, pede código/data/hora;
procura o Equipamento, percorre sua lista de reservas, e
remove a reserva que bate com data+hora (se houver).
*/
Tipo* cancelarReserva(Tipo* listaTipos){
    // Verifica se a lista de tipos está vazia
    if (!listaTipos) {
        printf("Nao ha equipamentos cadastrados.\n");
        return listaTipos;
    }

    // Pede dados da reserva
    int codigo;
    char dataRaw[20], dataNorm[11];
    char horaRaw[10], horaNorm[6];
    printf("=== Cancelar Reserva ===\n");
    printf("Codigo do equipamento: ");
    scanf("%d", &codigo);
    
     // Lê a data bruta
    printf("Data (DD/MM/AAAA): ");
    scanf(" %19[^\n]", dataRaw);

    if (!normalizeData(dataRaw, dataNorm)) {
        printf("Formato de data invalido. Use DD/MM/AAAA.\n\n");
        return listaTipos;
    }

    printf("Hora (HH:MM): ");
    scanf(" %9[^\n]", horaRaw);
    if (!normalizeHora(horaRaw, horaNorm)) {
        printf("Formato de hora invalido. Use HH:MM (por exemplo, 04:30 ou 430 ou 4:30).\n\n");
        return listaTipos;
    }

    // Busca o equipamento
    Equipamento* eq = buscarEquipamento(listaTipos, codigo);
    if (!eq) {
        printf("Equipamento nao encontrado.\n\n");
        return listaTipos;
    }

    //Percorre a lista de reservas para encontrar a que bate data e hora
    Reserva* ant = NULL;
    Reserva* atual = eq->reservas;
    while (atual != NULL) {
        if (strcmp(atual->data, dataNorm) == 0 && strcmp(atual->hora, horaNorm) == 0){
            if (ant) {
                // não é a primeira reserva
                ant->prox = atual->prox;
            } else {
                // é a primeira reserva da lista
                eq->reservas = atual->prox;
            }
            free(atual);
            printf("Reserva cancelada com sucesso!\n\n");
            return listaTipos;
        }
        ant = atual;
        atual = atual->prox;
    }
    // Reserva não encontrada
    printf("Reserva nao encontrada para %s as %s.\n\n", dataNorm, horaNorm);
    return listaTipos;
}

// Apagar DEBUG ONLY
void listarEquipamentos(Tipo* listaTipos) {
    if (!listaTipos) {
        printf("Nenhum equipamento cadastrado.\n");
        return;
    }

    printf("=== Lista de Equipamentos por Tipo ===\n");
    Tipo* t = listaTipos;
    while (t) {
        printf(">> Tipo: %s\n", t->tipo);
        No* nodo = t->listaEquipamentos;
        if (!nodo) {
            printf("   (vazio)\n");
        } else {
            while (nodo) {
                Equipamento* e = nodo->equipamento;
                printf("   - Codigo: %d | Descricao: %s\n", e->codigo, e->descricao);
                nodo = nodo->prox;
            }
        }
        t = t->prox;
    }
    printf("\n");
}

/* Implementações para reserva
   Autor: Paulo Roberto Schiochet
 * praticamente todas funções são ou para consultas ou reservas utilizando também utilizando as funções, ponteiros e afins já implementados pelo o Thiago e/ou Henrique 
   Estão com parte da suas explicações do que estão fazendo na lista.h */

/* Para conseguir listar todas as reservas de um determinado tipo de equipamento, por data específica e mostrar o histórico. 
 * listarReservasPorTipo: recebe a lista de tipos e pede ao usuário o tipo que ele quer, e então exibe todas as reservas do equipamento desse tipo.
 */
void listarReservasPorTipo(Tipo* listaTipos) {  // ← Alterado: retorno de int para void, removido parâmetro
    if (!listaTipos) {
        printf("Nenhum tipo cadastrado.\n");
        return;
    }

    char nomeTipo[100];  // ← Alterado: agora pede o nome do tipo dentro da função
    printf("Informe o tipo: ");
    scanf(" %99[^\n]", nomeTipo);

    Tipo* tipoEncontrado = buscarTipo(&listaTipos, nomeTipo);
    if (!tipoEncontrado) {
        printf("Tipo '%s' nao encontrado.\n", nomeTipo);
        return;
    }

    int totalReservas = 0;

    No* noAtual = tipoEncontrado->listaEquipamentos;
    while (noAtual != NULL) {
        Equipamento* equip = noAtual->equipamento;
        Reserva* reservaAtual = equip->reservas;
        while (reservaAtual != NULL) {
            printf("Equipamento: %s | Codigo: %d | Reserva: %s as %s por %s\n",
                   equip->descricao, equip->codigo,
                   reservaAtual->data, reservaAtual->hora, reservaAtual->nome);
            totalReservas++;
            reservaAtual = reservaAtual->prox;
        }
        noAtual = noAtual->prox;
    }

    printf("Total de reservas para tipo '%s': %d\n", nomeTipo, totalReservas);
}

/* consultarReservasPorData: essencialmente igual à de cima, mas ao invés de requerer o tipo de equipamento, pede a data e mostra as reservas, independente do tipo.
 */
void consultarReservasPorData(Tipo* listaTipos) {
    if (!listaTipos) {
        printf("Nenhum tipo cadastrado.\n");
        return;
    }

    char dataRaw[20];
    char dataNorm[11];  // DD/MM/AAAA

    printf("Informe a data (DD/MM/AAAA): ");
    scanf(" %19[^\n]", dataRaw);

    if (!normalizeData(dataRaw, dataNorm)) {
        printf("Formato de data invalido. Use DD/MM/AAAA (com ou sem separador).\n");
        return;
    }

    int totalReservas = 0;
    Tipo* tipoAtual = listaTipos;

    while (tipoAtual != NULL) {
        No* noAtual = tipoAtual->listaEquipamentos;
        while (noAtual != NULL) {
            Reserva* reservaAtual = noAtual->equipamento->reservas;
            while (reservaAtual != NULL) {
                if (strcmp(reservaAtual->data, dataNorm) == 0) {  // Comparação sempre normalizada!
                    printf("Tipo: %s | Equipamento: %s | Codigo: %d | Hora: %s | Nome: %s\n",
                           tipoAtual->tipo, noAtual->equipamento->descricao,
                           noAtual->equipamento->codigo, reservaAtual->hora, reservaAtual->nome);
                    totalReservas++;
                }
                reservaAtual = reservaAtual->prox;
            }
            noAtual = noAtual->prox;
        }
        tipoAtual = tipoAtual->prox;
    }

    printf("Total de reservas na data '%s': %d\n", dataNorm, totalReservas);
}

/* exibirHistoricoPorTipo: exibe um histórico completo por tipo de equipamento
 * então dali recebe a lista de tipos e pede ao usuário o tipo desejado, mostrando todos os equipamentos do tipo.
 */
void exibirHistoricoPorTipo(Tipo* listaTipos) {  // ← Alterado: retorno de int para void, removido parâmetro
    if (!listaTipos) {
        printf("Nenhum tipo cadastrado.\n");
        return;
    }

    char nomeTipo[100];  // ← Alterado: agora pede o nome do tipo dentro da função
    printf("Informe o tipo: ");
    scanf(" %99[^\n]", nomeTipo);

    Tipo* tipoEncontrado = buscarTipo(&listaTipos, nomeTipo);
    if (!tipoEncontrado) {
        printf("Tipo '%s' nao encontrado.\n", nomeTipo);
        return;
    }

    int totalEquipamentos = 0;
    int totalReservas = 0;

    No* noAtual = tipoEncontrado->listaEquipamentos;
    while (noAtual != NULL) {
        Equipamento* equip = noAtual->equipamento;
        totalEquipamentos++;
        printf("Equipamento: %s | Codigo: %d\n", equip->descricao, equip->codigo);

        Reserva* reservaAtual = equip->reservas;
        while (reservaAtual != NULL) {
            printf("  -> Reserva: %s as %s por %s\n",
                   reservaAtual->data, reservaAtual->hora, reservaAtual->nome);
            totalReservas++;
            reservaAtual = reservaAtual->prox;
        }

        noAtual = noAtual->prox;
    }

    printf("Total de equipamentos: %d | Total de reservas: %d\n", totalEquipamentos, totalReservas);
}

/* função auxiliar para contar reservas de um tipo específico;
   Retorna o total de reservas encontradas por tipo */
int contarReservasDoTipo(Tipo* listaTipos, const char* nomeTipo) {
    Tipo* tipoEncontrado = buscarTipo(&listaTipos, nomeTipo);
    if (!tipoEncontrado) return 0;
    //percorre só o tipo, depois a lista de reserva e entao soma
    int total = 0;
    No* noAtual = tipoEncontrado->listaEquipamentos;
    
    while (noAtual != NULL) {
        Reserva* reservaAtual = noAtual->equipamento->reservas;
        while (reservaAtual != NULL) {
            total++;
            reservaAtual = reservaAtual->prox;
        }
        noAtual = noAtual->prox;
    }
    return total;
}

/* função auxiliar para contar reservas em uma data específica; 
   É para retornar inteiro representando o total de reservas da data.*/
int contarReservasNaData(Tipo* listaTipos, const char* data) {
    int total = 0;
    Tipo* tipoAtual = listaTipos;
    //percorre tudo, vendo qual batem com a data informada
    while (tipoAtual != NULL) {
        No* noAtual = tipoAtual->listaEquipamentos;
        
        while (noAtual != NULL) {
            Reserva* reservaAtual = noAtual->equipamento->reservas;
            
            while (reservaAtual != NULL) {
                if (strcmp(reservaAtual->data, data) == 0) {
                    total++;
                }
                reservaAtual = reservaAtual->prox;
            }
            noAtual = noAtual->prox;
        }
        tipoAtual = tipoAtual->prox;
    }
    return total;
}
