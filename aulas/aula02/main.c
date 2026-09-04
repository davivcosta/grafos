#include <stdio.h>
#include "grafo_matriz.h"

int main() {
    int num_vertices = 8;

    GrafoMatriz grafo;

    inicializar(&grafo, num_vertices);

    insertir_aresta(&grafo, 0, 1);
    insertir_aresta(&grafo, 0, 2);
    insertir_aresta(&grafo, 0, 3);
    insertir_aresta(&grafo, 1, 4);
    insertir_aresta(&grafo, 1, 5);
    insertir_aresta(&grafo, 2, 3);
    insertir_aresta(&grafo, 2, 6);
    insertir_aresta(&grafo, 3, 6);
    insertir_aresta(&grafo, 4, 5);
    insertir_aresta(&grafo, 7, 4);
    insertir_aresta(&grafo, 7, 5);
    insertir_aresta(&grafo, 7, 6);

    print("Matriz de Adjacência:\n");
    exibir_matriz(&grafo);
    return 0;
}