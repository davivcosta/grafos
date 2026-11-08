#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

// Estrutura genérica sugerida para o Grafo (Lista Ponderada / Lista de Arestas)
typedef struct {
    int origem;
    int destino;
    int peso;
} Aresta;

typedef struct {
    int num_vertices;
    int num_arestas;
    Aresta *arestas;
} GrafoListaPonderado;

// Funções obrigatórias da prática
int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(int vertice_inicio, int *pred, int num_vertices);

#endif