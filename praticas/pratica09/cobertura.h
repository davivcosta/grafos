#ifndef COBERTURA_H
#define COBERTURA_H

#include <stdbool.h>

// Assumindo uma representação simples de grafo por matriz de adjacência
typedef struct {
    int num_vertices;
    int **matriz_adj;
} Grafo;

// Funções a implementar exigidas na prática
bool eh_cobertura(Grafo *g, bool *conjunto);
void cobertura_minima_bt(Grafo *g, int vertice_atual, bool *cobertura_atual, int tamanho_atual, bool *melhor_cobertura, int *melhor_tamanho);
void cobertura_gulosa(Grafo *g, bool *cobertura);

#endif