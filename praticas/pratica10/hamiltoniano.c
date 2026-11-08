#include "hamiltoniano.h"
#include <stdlib.h>

Grafo* criar_grafo(int n) {
    Grafo *g = malloc(sizeof(Grafo));
    g->num_vertices = n;
    g->matriz = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->matriz[i] = calloc(n, sizeof(int));
    }
    return g;
}

void liberar_grafo(Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) free(g->matriz[i]);
    free(g->matriz);
    free(g);
}

// Backtracking com permutações
bool encontrar_caminho_hamiltoniano_bt(Grafo *g, int v, int pos, int *caminho, bool *visitado) {
    caminho[pos] = v;
    visitado[v] = true;

    // Se todos os vértices foram visitados, achou o caminho
    if (pos == g->num_vertices - 1) return true;

    for (int i = 0; i < g->num_vertices; i++) {
        if (g->matriz[v][i] > 0 && !visitado[i]) {
            if (encontrar_caminho_hamiltoniano_bt(g, i, pos + 1, caminho, visitado)) {
                return true;
            }
        }
    }

    // Backtrack
    visitado[v] = false;
    return false;
}