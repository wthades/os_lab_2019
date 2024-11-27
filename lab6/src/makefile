# Имена исполняемых файлов
CLIENT_EXEC = client
SERVER_EXEC = server

# Исходные файлы
CLIENT_SRC = client.c
SERVER_SRC = server.c
COMMON_SRC = common.c

# Флаги компиляции
CFLAGS = -Wall -Wextra -pthread

# Компилятор
CC = gcc

# Правила для сборки клиента и сервера
all: $(CLIENT_EXEC) $(SERVER_EXEC)

$(CLIENT_EXEC): $(CLIENT_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC) $(COMMON_SRC)

$(SERVER_EXEC): $(SERVER_SRC) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC) $(COMMON_SRC)

# Правило для очистки
clean:
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC)

# Правило для перекомпиляции
rebuild: clean all

.PHONY: all clean rebuild