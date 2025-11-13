# Nome do executável
EXEC = main

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c11

# Detecta todos os arquivos .c da pasta
SRC = $(wildcard *.c)

# Gera os arquivos objeto correspondentes
OBJ = $(SRC:.c=.o)

# Regra padrão: compilar tudo
all: $(EXEC)

# Como gerar o executável a partir dos objetos
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Como gerar os arquivos objeto a partir dos .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: $(EXEC)
	./$(EXEC)

# Limpar arquivos objeto e executável
clean:
	rm -f $(OBJ) $(EXEC)
