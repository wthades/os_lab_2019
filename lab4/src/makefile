# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Цели для сборки программ
all: parallel_min_max process_memory parallel_sum

# Правило для сборки parallel_min_max
parallel_min_max: /workspaces/os_lab_2019/lab3/src/parallel_min_max.c /workspaces/os_lab_2019/lab3/src/utils.o /workspaces/os_lab_2019/lab3/src/find_min_max.o
	$(CC) $(CFLAGS) -o parallel_min_max /workspaces/os_lab_2019/lab3/src/parallel_min_max.c /workspaces/os_lab_2019/lab3/src/utils.o /workspaces/os_lab_2019/lab3/src/find_min_max.o

# Правило для сборки process_memory
process_memory: process_memory.c
	$(CC) $(CFLAGS) -o process_memory process_memory.c

# Правило для сборки parallel_sum
parallel_sum: parallel_sum.c sum.o /workspaces/os_lab_2019/lab3/src/utils.o
	$(CC) $(CFLAGS) -o parallel_sum parallel_sum.c sum.o /workspaces/os_lab_2019/lab3/src/utils.o -lpthread

# Правило для сборки sum.o
sum.o: sum.c sum.h
	$(CC) $(CFLAGS) -c -o sum.o sum.c

# Правило для сборки utils.o
/workspaces/os_lab_2019/lab3/src/utils.o: /workspaces/os_lab_2019/lab3/src/utils.c /workspaces/os_lab_2019/lab3/src/utils.h
	$(CC) $(CFLAGS) -c -o /workspaces/os_lab_2019/lab3/src/utils.o /workspaces/os_lab_2019/lab3/src/utils.c

# Правило для очистки сгенерированных файлов
clean:
	rm -f parallel_min_max process_memory parallel_sum

# Правило для удаления исполняемых файлов и объектных файлов
distclean: clean
	rm -f *.o