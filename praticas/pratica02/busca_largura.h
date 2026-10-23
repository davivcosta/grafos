#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "../pratica01/grafo_lista.h"

typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;

Fila *criar_fila(int capacidade);
void enfileirar(Fila *fila, int valor);
int desenfileirar(Fila *fila);
int fila_vazia(Fila *fila);
void liberar_fila(Fila *fila);

void bfs(GrafoLista *g, int origem, int *dist, int *pred);

#endif