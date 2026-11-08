#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

int main() {
    Grafo g;
    g.V = 4;
    g.E = 5;
    g.arestas = malloc(g.E * sizeof(Aresta));

    // Configurando um grafo de teste
    g.arestas[0] = (Aresta){0, 1, 10};
    g.arestas[1] = (Aresta){0, 2, 6};
    g.arestas[2] = (Aresta){0, 3, 5};
    g.arestas[3] = (Aresta){1, 3, 15};
    g.arestas[4] = (Aresta){2, 3, 4};

    printf("=== Algoritmo de Kruskal ===\n");
    kruskal(&g);

    printf("\n=== Algoritmo de Prim ===\n");
    prim(&g, 0); // Inicia do vértice 0

    free(g.arestas);
    return 0;
}