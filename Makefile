
# Nome do executável
TARGET = sistema

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SRCS = main.c lista.c equipamentos.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Como compilar cada .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos objetos e executável
clean:
	rm -f $(OBJS) $(TARGET)
