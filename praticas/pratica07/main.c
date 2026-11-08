#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main() {
    // 1. Inicializar a estrutura do grafo
    GrafoListaPonderado grafo;
    grafo.num_vertices = 4;
    grafo.num_arestas = 4;
    
    // Alocar memória para as arestas
    grafo.arestas = malloc(grafo.num_arestas * sizeof(Aresta));
    
    // Aresta 0: 0 -> 1 (peso 1)
    grafo.arestas[0].origem = 0;
    grafo.arestas[0].destino = 1;
    grafo.arestas[0].peso = 1;
    
    // Aresta 1: 1 -> 2 (peso 2)
    grafo.arestas[1].origem = 1;
    grafo.arestas[1].destino = 2;
    grafo.arestas[1].peso = 2;
    
    // Aresta 2: 2 -> 3 (peso 3)
    grafo.arestas[2].origem = 2;
    grafo.arestas[2].destino = 3;
    grafo.arestas[2].peso = 3;
    
    // Aresta 3: 3 -> 1 (peso -10) -- Cria um ciclo negativo (2 + 3 - 10 = -5)
    grafo.arestas[3].origem = 3;
    grafo.arestas[3].destino = 1;
    grafo.arestas[3].peso = -10;

    // 2. Alocar arrays de distâncias e predecessores
    int *dist = malloc(grafo.num_vertices * sizeof(int));
    int *pred = malloc(grafo.num_vertices * sizeof(int));

    // 3. Executar o algoritmo a partir do vértice de origem 0
    printf("A executar Bellman-Ford...\n");
    int resultado = bellman_ford(&grafo, 0, dist, pred);
    
    if (resultado == 1) {
        printf("Sucesso: Nenhum ciclo negativo encontrado.\n");
        for (int i = 0; i < grafo.num_vertices; i++) {
            printf("Distancia ate %d: %d\n", i, dist[i]);
        }
    } else {
        printf("Falha: O algoritmo retornou 0 devido ao ciclo negativo.\n");
    }

    // 4. Libertar a memória para evitar memory leaks (muito importante para o GitHub Actions)
    free(grafo.arestas);
    free(dist);
    free(pred);

    return 0;
}