CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = main

SRCS = main.c busca_largura.c busca_profundidade.c ../pratica01/grafo_lista.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)