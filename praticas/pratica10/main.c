#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

// Gera um grafo com densidade razoável para teste
void popular_grafo_aleatorio(Grafo *g) {
    for(int i = 0; i < g->num_vertices; i++) {
        for(int j = i + 1; j < g->num_vertices; j++) {
            int aresta = (rand() % 100 < 60) ? 1 : 0; // 60% de chance de ter aresta
            g->matriz[i][j] = aresta;
            g->matriz[j][i] = aresta;
        }
    }
}

int main() {
    int ns[] = {5, 8, 10, 12};
    int num_testes = 4;
    srand(42); // Semente fixa para testes reproduzíveis

    for (int t = 0; t < num_testes; t++) {
        int n = ns[t];
        Grafo *g = criar_grafo(n);
        popular_grafo_aleatorio(g);

        int *caminho_hamilton = calloc(n, sizeof(int));
        bool *visitado = calloc(n, sizeof(bool));
        bool achou_hamilton = encontrar_caminho_hamiltoniano_bt(g, 0, 0, caminho_hamilton, visitado);

        // Prepara para o Caixeiro Viajante
        grafo_para_tsp(g);
        int *caminho_tsp = calloc(n + 1, sizeof(int));

        // Força Bruta
        clock_t t_inicio = clock();
        int custo_fb = tsp_forca_bruta(g, caminho_tsp);
        double tempo_fb = (double)(clock() - t_inicio) / CLOCKS_PER_SEC;

        // Vizinho Mais Próximo
        t_inicio = clock();
        int custo_vmp = tsp_vizinho_mais_proximo(g, caminho_tsp);
        double tempo_vmp = (double)(clock() - t_inicio) / CLOCKS_PER_SEC;

        // Inserção
        t_inicio = clock();
        int custo_ins = tsp_insercao(g, caminho_tsp);
        double tempo_ins = (double)(clock() - t_inicio) / CLOCKS_PER_SEC;

        printf("=== N = %d ===\n", n);
        printf("Caminho Hamiltoniano: %s\n", achou_hamilton ? "ENCONTRADO" : "NAO ENCONTRADO");
        printf("TSP (Forca Bruta)  : Custo = %d | Tempo = %f s\n", custo_fb, tempo_fb);
        printf("TSP (Vizinho Mais) : Custo = %d | Tempo = %f s\n", custo_vmp, tempo_vmp);
        printf("TSP (Insercao)     : Custo = %d | Tempo = %f s\n\n", custo_ins, tempo_ins);

        free(caminho_hamilton); free(visitado); free(caminho_tsp); liberar_grafo(g);
    }
    return 0;
}