#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bellman_ford.h"

void reconstruir_ciclo_negativo(int vertice_inicio, int *pred, int num_vertices) {
    int atual = vertice_inicio;
    
    // Retrocede n vezes pelo pred[] para garantir que estamos dentro do ciclo
    for (int i = 0; i < num_vertices; i++) {
        atual = pred[atual];
    }
    
    // Agora 'atual' faz garantidamente parte do ciclo negativo
    int inicio_ciclo = atual;
    int *ciclo = malloc(num_vertices * sizeof(int));
    int cont = 0;
    
    // Reconstrói e guarda o ciclo
    do {
        ciclo[cont++] = atual;
        atual = pred[atual];
    } while (atual != inicio_ciclo);
    ciclo[cont++] = inicio_ciclo; // Fecha o ciclo
    
    // Imprime o ciclo (invertido, para mostrar a ordem correta)
    printf("Ciclo negativo detectado: ");
    for (int i = cont - 1; i >= 0; i--) {
        printf("%d ", ciclo[i]);
    }
    printf("\n");
    
    free(ciclo);
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    int E = g->num_arestas;

    // Inicialização
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[origem] = 0;

    // Relaxação de arestas n - 1 vezes
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = g->arestas[j].origem;
            int v = g->arestas[j].destino;
            int peso = g->arestas[j].peso;
            
            if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
            }
        }
    }

    // n-ésima iteração: Deteção de ciclo negativo
    for (int j = 0; j < E; j++) {
        int u = g->arestas[j].origem;
        int v = g->arestas[j].destino;
        int peso = g->arestas[j].peso;
        
        if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
            reconstruir_ciclo_negativo(v, pred, V);
            return 0; // Retorna 0 (ciclo negativo encontrado)
        }
    }

    return 1; // Retorna 1 (sucesso, sem ciclos negativos)
}