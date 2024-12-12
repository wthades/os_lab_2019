# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -Wall -Wextra -Werror -pthread

# Имена исполняемых файлов
CLIENT = client
SERVER = server

# Исходные файлы
CLIENT_SRC = client.c
SERVER_SRC = server.c
COMMON_SRC = common.c
COMMON_H = common.h

# Объектные файлы
CLIENT_OBJ = client.o
SERVER_OBJ = server.o
COMMON_OBJ = common.o

# Цель по умолчанию
all: $(CLIENT) $(SERVER)

# Цель для клиента
$(CLIENT): $(CLIENT_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Цель для сервера
$(SERVER): $(SERVER_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Цель для объектного файла клиента
$(CLIENT_OBJ): $(CLIENT_SRC) $(COMMON_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для объектного файла сервера
$(SERVER_OBJ): $(SERVER_SRC) $(COMMON_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для объектного файла common
$(COMMON_OBJ): $(COMMON_SRC) $(COMMON_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для очистки
clean:
	rm -f $(CLIENT) $(SERVER) $(CLIENT_OBJ) $(SERVER_OBJ) $(COMMON_OBJ)

.PHONY: all clean
