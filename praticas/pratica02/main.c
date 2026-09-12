#include <stdio.h>
#include <stdlib.h>

#include "../pratica01/grafo_lista.h"
#include "../pratica01/grafo_lista.c"

#include "busca_largura.h"
#include "busca_profundidade.h"

void imprimir_bfs(int *dist, int *pred, int n) {
    printf("\nBFS:\n");

    printf("Vertice: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i);
    }

    printf("\nDist:    ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dist[i]);
    }

    printf("\nPred:    ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pred[i]);
    }

    printf("\n");
}

void imprimir_dfs(int *entrada, int *saida, int n) {
    printf("\nDFS:\n");

    printf("Vertice: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i);
    }

    printf("\nEntrada: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", entrada[i]);
    }

    printf("\nSaida:   ");
    for (int i = 0; i < n; i++) {
        printf("%d ", saida[i]);
    }

    printf("\n");
}

int main(void) {
    int n = 6;

    GrafoLista *g = criar_grafo_lista(n);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    /*
     * Grafo:
     *
     *       1 ----- 3
     *      /       /
     *     0       /
     *      \     /
     *       2 ---
     *
     *       4 ----- 5
     *
     * Componentes: 2
     * Possui ciclo: sim (0-1-3-2-0)
     * Bipartido: sim
     */

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 0, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 2, 3);
    inserir_aresta_lista(g, 4, 5);

    int *dist = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int));

    if (dist == NULL || pred == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(dist);
        free(pred);
        liberar_grafo_lista(g);
        return 1;
    }

    bfs(g, 0, dist, pred);
    imprimir_bfs(dist, pred, n);

    int *tempo_entrada = malloc(n * sizeof(int));
    int *tempo_saida = malloc(n * sizeof(int));

    if (tempo_entrada == NULL || tempo_saida == NULL) {
        printf("Erro ao alocar memoria.\n");
        free(dist);
        free(pred);
        free(tempo_entrada);
        free(tempo_saida);
        liberar_grafo_lista(g);
        return 1;
    }

    dfs(g, tempo_entrada, tempo_saida);
    imprimir_dfs(tempo_entrada, tempo_saida, n);

    printf("\nComponentes conexos: %d\n", contar_componentes(g));

    printf("Possui ciclo: %s\n", tem_ciclo(g) ? "sim" : "nao");

    printf("Eh bipartido: %s\n", eh_bipartido(g) ? "sim" : "nao");

    free(dist);
    free(pred);
    free(tempo_entrada);
    free(tempo_saida);

    liberar_grafo_lista(g);

    return 0;
}