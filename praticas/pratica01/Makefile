CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main

OBJ = main.o grafo_matriz.o grafo_lista.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) -c main.c

grafo_matriz.o: grafo_matriz.c grafo_matriz.h
	$(CC) $(CFLAGS) -c grafo_matriz.c

grafo_lista.o: grafo_lista.c grafo_lista.h
	$(CC) $(CFLAGS) -c grafo_lista.c

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe