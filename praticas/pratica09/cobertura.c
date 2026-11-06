#include "cobertura.h"
#include <stdio.h>
#include <stdlib.h>

// Verifica se todas as arestas estão cobertas.
bool eh_cobertura(Grafo *g, bool *conjunto) {
    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = i + 1; j < g->num_vertices; j++) {
            if (g->matriz_adj[i][j] == 1) {
                if (!conjunto[i] && !conjunto[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Backtracking com poda por limite[cite: 1].
void cobertura_minima_bt(Grafo *g, int vertice_atual, bool *cobertura_atual, int tamanho_atual, bool *melhor_cobertura, int *melhor_tamanho) {
    // Poda: se o tamanho atual já for maior ou igual ao melhor encontrado, interrompe a busca
    if (tamanho_atual >= *melhor_tamanho) return;
    
    if (vertice_atual == g->num_vertices) {
        if (eh_cobertura(g, cobertura_atual)) {
            *melhor_tamanho = tamanho_atual;
            for (int i = 0; i < g->num_vertices; i++) {
                melhor_cobertura[i] = cobertura_atual[i];
            }
        }
        return;
    }
    
    // Ramo 1: Inclui o vértice atual na cobertura
    cobertura_atual[vertice_atual] = true;
    cobertura_minima_bt(g, vertice_atual + 1, cobertura_atual, tamanho_atual + 1, melhor_cobertura, melhor_tamanho);
    
    // Ramo 2: Não inclui o vértice atual
    cobertura_atual[vertice_atual] = false;
    cobertura_minima_bt(g, vertice_atual + 1, cobertura_atual, tamanho_atual, melhor_cobertura, melhor_tamanho);
}

// Seleciona o vértice de maior grau restante[cite: 1].
void cobertura_gulosa(Grafo *g, bool *cobertura) {
    // Inicializa a cobertura como falsa
    for (int i = 0; i < g->num_vertices; i++) cobertura[i] = false;
    
    // Copia a matriz de adjacência para manipular os graus restantes
    int **matriz_temp = malloc(g->num_vertices * sizeof(int*));
    for (int i = 0; i < g->num_vertices; i++) {
        matriz_temp[i] = malloc(g->num_vertices * sizeof(int));
        for (int j = 0; j < g->num_vertices; j++) {
            matriz_temp[i][j] = g->matriz_adj[i][j];
        }
    }
    
    while (!eh_cobertura(g, cobertura)) {
        int max_grau = -1;
        int vertice_escolhido = -1;
        
        // Encontra o vértice com maior grau
        for (int i = 0; i < g->num_vertices; i++) {
            if (cobertura[i]) continue;
            int grau = 0;
            for (int j = 0; j < g->num_vertices; j++) {
                if (matriz_temp[i][j] == 1) grau++;
            }
            if (grau > max_grau) {
                max_grau = grau;
                vertice_escolhido = i;
            }
        }
        
        // Adiciona à cobertura e remove as arestas incidentes
        if (vertice_escolhido != -1) {
            cobertura[vertice_escolhido] = true;
            for (int j = 0; j < g->num_vertices; j++) {
                matriz_temp[vertice_escolhido][j] = 0;
                matriz_temp[j][vertice_escolhido] = 0;
            }
        }
    }
    
    // Limpeza de memória
    for (int i = 0; i < g->num_vertices; i++) free(matriz_temp[i]);
    free(matriz_temp);
}