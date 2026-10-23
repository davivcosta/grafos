#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int V = 5; // Grafo de 5 vértices (0 a 4)
    GrafoListaPonderado* g = criar_grafo(V);

    // Grafo de exemplo
    adicionar_aresta(g, 0, 1, 10);
    adicionar_aresta(g, 0, 4, 3);
    adicionar_aresta(g, 1, 2, 2);
    adicionar_aresta(g, 1, 4, 4);
    adicionar_aresta(g, 2, 3, 9);
    adicionar_aresta(g, 3, 2, 7);
    adicionar_aresta(g, 4, 1, 1);
    adicionar_aresta(g, 4, 2, 8);
    adicionar_aresta(g, 4, 3, 2);

    int dist[V];
    int pred[V];
    int origem = 0;

    printf("Calculando Dijkstra a partir do vertice %d...\n\n", origem);
    dijkstra(g, origem, dist, pred);

    printf("Distancias minimas e caminhos:\n");
    for (int i = 0; i < V; i++) {
        printf("Vértice %d (Distância: %d) | Caminho: ", i, dist[i]);
        reconstruir_caminho(origem, i, pred);
        printf("\n");
    }

    liberar_grafo(g);
    return 0;
}