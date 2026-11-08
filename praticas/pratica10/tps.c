#include "tps.h"
#include <stdlib.h>
#include <limits.h>

// Redução: peso 1 para arestas existentes, 2 para inexistentes
void grafo_para_tsp(Grafo *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = 0; j < g->num_vertices; j++) {
            if (i != j) {
                if (g->matriz[i][j] == 0) {
                    g->matriz[i][j] = 2; 
                } else if (g->matriz[i][j] > 0 && g->matriz[i][j] != 2) {
                    g->matriz[i][j] = 1; 
                }
            }
        }
    }
}

// Auxiliar recursiva para (n-1)! permutações
static void permutar_tsp(Grafo *g, int *caminho_atual, bool *visitado, int pos, int custo_atual, int *melhor_custo, int *melhor_caminho) {
    if (pos == g->num_vertices) {
        int custo_final = custo_atual + g->matriz[caminho_atual[pos-1]][caminho_atual[0]];
        if (custo_final < *melhor_custo) {
            *melhor_custo = custo_final;
            for (int i = 0; i < g->num_vertices; i++) melhor_caminho[i] = caminho_atual[i];
        }
        return;
    }
    
    for (int i = 1; i < g->num_vertices; i++) { // Ignora o 0 (origem fixa)
        if (!visitado[i]) {
            visitado[i] = true;
            caminho_atual[pos] = i;
            permutar_tsp(g, caminho_atual, visitado, pos + 1, custo_atual + g->matriz[caminho_atual[pos-1]][i], melhor_custo, melhor_caminho);
            visitado[i] = false;
        }
    }
}

int tsp_forca_bruta(Grafo *g, int *melhor_caminho) {
    int *caminho_atual = malloc(g->num_vertices * sizeof(int));
    bool *visitado = calloc(g->num_vertices, sizeof(bool));
    int melhor_custo = INT_MAX;
    
    caminho_atual[0] = 0; 
    visitado[0] = true;
    
    permutar_tsp(g, caminho_atual, visitado, 1, 0, &melhor_custo, melhor_caminho);
    
    free(caminho_atual); free(visitado);
    return melhor_custo;
}

int tsp_vizinho_mais_proximo(Grafo *g, int *caminho) {
    bool *visitado = calloc(g->num_vertices, sizeof(bool));
    int atual = 0, custo_total = 0;
    caminho[0] = atual;
    visitado[atual] = true;

    for (int i = 1; i < g->num_vertices; i++) {
        int proximo = -1;
        int menor_dist = INT_MAX;
        for (int j = 0; j < g->num_vertices; j++) {
            if (!visitado[j] && g->matriz[atual][j] < menor_dist) {
                menor_dist = g->matriz[atual][j];
                proximo = j;
            }
        }
        caminho[i] = proximo;
        visitado[proximo] = true;
        custo_total += menor_dist;
        atual = proximo;
    }
    custo_total += g->matriz[atual][caminho[0]]; // Retorno à origem
    free(visitado);
    return custo_total;
}

int tsp_insercao(Grafo *g, int *caminho) {
    bool *no_ciclo = calloc(g->num_vertices, sizeof(bool));
    int custo_total = 0;
    
    caminho[0] = 0; caminho[1] = 1; caminho[2] = 0;
    no_ciclo[0] = true; no_ciclo[1] = true;
    int tam_ciclo = 2;
    
    while (tam_ciclo < g->num_vertices) {
        int melhor_k = -1, melhor_pos = -1, min_aumento = INT_MAX;
        
        for (int k = 0; k < g->num_vertices; k++) {
            if (!no_ciclo[k]) {
                for (int i = 0; i < tam_ciclo; i++) {
                    int u = caminho[i], v = caminho[i+1];
                    int aumento = g->matriz[u][k] + g->matriz[k][v] - g->matriz[u][v];
                    if (aumento < min_aumento) {
                        min_aumento = aumento; melhor_k = k; melhor_pos = i + 1;
                    }
                }
            }
        }
        for (int i = tam_ciclo; i >= melhor_pos; i--) caminho[i+1] = caminho[i];
        caminho[melhor_pos] = melhor_k;
        no_ciclo[melhor_k] = true;
        tam_ciclo++;
    }
    for (int i = 0; i < tam_ciclo; i++) custo_total += g->matriz[caminho[i]][caminho[i+1]];
    free(no_ciclo);
    return custo_total;
}