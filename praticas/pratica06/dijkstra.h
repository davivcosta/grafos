#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// --- Estruturas do Grafo ---
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta **listas_adj;
} GrafoListaPonderado;

// --- Estruturas Obrigatórias (Prática 06) ---
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

// --- Funções do Grafo ---
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado* g, int origem, int destino, int peso);
void liberar_grafo(GrafoListaPonderado* g);

// --- Funções Obrigatórias ---
MinHeap* criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap* heap);
void diminuir_chave(MinHeap* heap, int vertice, int nova_distancia);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif