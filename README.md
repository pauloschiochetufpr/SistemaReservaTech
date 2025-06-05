
# Sistema de Reservas de Equipamentos Tecnológicos

## 📌 Descrição do Projeto

Este é um sistema desenvolvido em **linguagem C**, que permite o **gerenciamento de reservas** de diversos **equipamentos tecnológicos** (como notebooks, tablets, câmeras, etc.).

O sistema foi implementado utilizando **listas encadeadas simples com cabeçalho**, garantindo uma estrutura flexível, eficiente e organizada para armazenar os diferentes tipos de equipamentos e suas respectivas reservas.

Cada **Tipo** de equipamento funciona como um **nó de cabeçalho**, contendo uma **sub-lista** de equipamentos daquele tipo, e cada equipamento possui sua própria **lista de reservas**.

## 🛠️ Estrutura de Dados Utilizada

✅ **Lista Encadeada Simples com Cabeçalho**:  
- Cada **Tipo** é um cabeçalho que armazena o nome do tipo e aponta para uma lista de **Equipamentos** daquele tipo.  
- Cada **Equipamento** possui sua própria lista de **Reservas**.  

Esse modelo permite que o sistema gerencie múltiplos tipos de equipamentos, cada um com seus respectivos registros e reservas, de maneira modular e escalável.

## 🚀 Funcionalidades Principais

### ✅ Gerenciamento de Tipos de Equipamento
- **Inserir Tipo**: adiciona um novo tipo de equipamento na lista, caso ainda não exista.
- **Buscar Tipo**: localiza um tipo pelo nome, de forma insensível a maiúsculas/minúsculas.

### ✅ Gerenciamento de Equipamentos
- **Cadastrar Equipamento**: insere um equipamento associado a um tipo previamente cadastrado.
- **Remover Equipamento**: remove um equipamento da lista pelo seu código.
- **Buscar Equipamento**: localiza um equipamento pelo código.

### ✅ Gestão de Reservas
- **Reservar Equipamento**: realiza uma reserva de um equipamento para uma data e hora específicas, evitando conflitos.
- **Cancelar Reserva**: remove uma reserva específica informando código, data e hora.
- **Listar Reservas por Tipo**: exibe todas as reservas realizadas para um tipo específico.
- **Consultar Reservas por Data**: exibe todas as reservas realizadas em uma data específica, independente do tipo.
- **Exibir Histórico por Tipo**: mostra todos os equipamentos de um tipo e o total de reservas realizadas.

### ✅ Exibição e Utilitários
- **Exibir Todos os Tipos e Equipamentos**: mostra todos os tipos cadastrados e seus respectivos equipamentos.
- **Normalização de Data e Hora**: funções `normalizeData` e `normalizeHora` para garantir consistência na entrada de datas e horários.
- **Liberação de Memória**: libera toda a memória alocada ao final do programa, evitando vazamentos.

## 🖥️ Como Executar

1. Compile todos os arquivos:  
```bash
gcc main.c lista.c equipamentos.c -o sistema
```

2. Execute o programa:  
```bash
./sistema
```

## ✅ Exemplo de Interação

- Cadastrar tipos como "Notebook" ou "Tablet".
- Cadastrar equipamentos vinculados aos tipos.
- Fazer reservas, consultar e cancelar conforme necessário.

## 📝 Organização dos Arquivos

| Arquivo            | Função                                      |
|--------------------|---------------------------------------------|
| `main.c`           | Interface com o usuário, menu principal.    |
| `lista.c/.h`       | Implementação e protótipos da lista encadeada. |
| `equipamentos.c/.h`| Funções de gerenciamento de equipamentos e reservas. |

## ✅ Diferenciais

- Sistema modular, com separação clara entre as operações.
- Uso de **listas encadeadas com cabeçalho** para refletir a estrutura hierárquica dos dados.
- Prevenção de **conflitos de reservas**.
- **Normalização** e validação robusta de **datas e horários**.

## 🧑‍💻 Autores

- Felyppe Marcelo da Silva
- Henrique Meneses dos Santos
- Paulo Roberto Schiochet
- Thiago Tanaka Peczek



