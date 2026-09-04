#include "grafo_matriz.h"

/* Declaração mínima para permitir a compilação sem depender do IntelliSense. */
extern int printf(const char *format, ...);

void inicializar(GrafoMatriz *grafo, int numero){
    grafo->num_vertices = numero;
    for (int i = 0; i < numero; i++) {
        for (int j = 0; j < numero; j++) {
            grafo->adjacencia[i][j] = 0;
        }
    }
}

void inserir_aresta(GrafoMatriz *grafo, int u, int v){
    grafo->adjacencia[u][v] = 1;
}

void exibir_matriz(GrafoMatriz *grafo){
    for(int i = 0; i < grafo->num_vertices; i++){
        for(int j = 0; j < grafo->num_vertices; j++){
            printf("%3i", grafo->adjacencia[i][j]);
        }
        printf("\n");
    }
}
