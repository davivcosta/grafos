#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H
#include <stdbool.h>

// Estrutura de Grafo baseada em matriz de adjacência (ideal para TSP)
typedef struct {
    int num_vertices;
    int **matriz;
} Grafo;

Grafo* criar_grafo(int n);
void liberar_grafo(Grafo *g);
bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int v, int pos, int *caminho, bool *visitado);

#endif