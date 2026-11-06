#include "cobertura.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função auxiliar para criar grafo aleatório (adicione a lógica de inicialização da matriz)
Grafo* criar_grafo_aleatorio(int n) {
    Grafo *g = malloc(sizeof(Grafo));
    g->num_vertices = n;
    g->matriz_adj = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->matriz_adj[i] = calloc(n, sizeof(int));
        for(int j = 0; j < i; j++) {
            int aresta = rand() % 2;
            g->matriz_adj[i][j] = aresta;
            g->matriz_adj[j][i] = aresta;
        }
    }
    return g;
}

int main() {
    int tamanhos[] = {5, 8, 10, 12, 15};
    int num_experimentos = 5;
    
    for (int i = 0; i < num_experimentos; i++) {
        int n = tamanhos[i];
        Grafo *g = criar_grafo_aleatorio(n);
        
        // Arrays auxiliares para Backtracking
        bool *cobertura_atual = calloc(n, sizeof(bool));
        bool *melhor_cobertura = calloc(n, sizeof(bool));
        int melhor_tamanho = n + 1; // Infinito inicial
        
        // Medir tempo Backtracking
        clock_t inicio_bt = clock();
        cobertura_minima_bt(g, 0, cobertura_atual, 0, melhor_cobertura, &melhor_tamanho);
        clock_t fim_bt = clock();
        double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;
        
        // Array auxiliar para Gulosa
        bool *cobertura_gulosa_arr = calloc(n, sizeof(bool));
        
        // Medir tempo Gulosa
        clock_t inicio_gl = clock();
        cobertura_gulosa(g, cobertura_gulosa_arr);
        clock_t fim_gl = clock();
        double tempo_gl = (double)(fim_gl - inicio_gl) / CLOCKS_PER_SEC;
        
        printf("N = %d | Tempo BT: %f s | Tempo Guloso: %f s\n", n, tempo_bt, tempo_gl);
        
        // Lembre-se de liberar a memória alocada do grafo
    }
    return 0;
}