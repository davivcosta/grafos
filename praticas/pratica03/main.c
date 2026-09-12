#include <stdio.h>
#include <stdlib.h>

#include "../pratica01/grafo_lista.h"
#include "../pratica01/grafo_lista.c"
#include "dag.h"

void inserir_aresta_direcionada(GrafoLista *g, int origem, int destino) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return;
    }

    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

void imprimir_ordem(const char *nome, int *ordem, int tamanho) {
    printf("%s: ", nome);

    for (int i = 0; i < tamanho; i++) {
        printf("%d", ordem[i]);

        if (i < tamanho - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}

void testar_dag(void) {
    int n = 6;

    GrafoLista *g = criar_grafo_lista(n);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return;
    }

    /*
     * DAG:
     *
     *       0
     *      / \
     *     v   v
     *     1   2
     *      \ / \
     *       v   v
     *       3   4
     *        \ /
     *         v
     *         5
     *
     * Uma possivel ordenacao:
     * 0 -> 1 -> 2 -> 3 -> 4 -> 5
     */

    inserir_aresta_direcionada(g, 0, 1);
    inserir_aresta_direcionada(g, 0, 2);
    inserir_aresta_direcionada(g, 1, 3);
    inserir_aresta_direcionada(g, 2, 3);
    inserir_aresta_direcionada(g, 2, 4);
    inserir_aresta_direcionada(g, 3, 5);
    inserir_aresta_direcionada(g, 4, 5);

    printf("=== TESTE 1: DAG ===\n");

    printf("Eh DAG? %s\n", eh_dag(g) ? "sim" : "nao");

    int tamanho_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);

    if (ordem_kahn != NULL) {
        imprimir_ordem("Kahn", ordem_kahn, tamanho_kahn);
        free(ordem_kahn);
    } else {
        printf("Kahn: nao existe ordenacao topologica.\n");
    }

    int tamanho_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);

    if (ordem_dfs != NULL) {
        imprimir_ordem("DFS", ordem_dfs, tamanho_dfs);
        free(ordem_dfs);
    } else {
        printf("DFS: nao existe ordenacao topologica.\n");
    }

    liberar_grafo_lista(g);
}

void testar_ciclo(void) {
    int n = 4;

    GrafoLista *g = criar_grafo_lista(n);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return;
    }

    /*
     * Grafo com ciclo:
     *
     * 0 -> 1 -> 2
     *      ^    |
     *      |    v
     *      +----3
     *
     * Ciclo: 1 -> 2 -> 3 -> 1
     */

    inserir_aresta_direcionada(g, 0, 1);
    inserir_aresta_direcionada(g, 1, 2);
    inserir_aresta_direcionada(g, 2, 3);
    inserir_aresta_direcionada(g, 3, 1);

    printf("\n=== TESTE 2: GRAFO COM CICLO ===\n");

    printf("Eh DAG? %s\n", eh_dag(g) ? "sim" : "nao");

    int tamanho_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);

    if (ordem_kahn != NULL) {
        imprimir_ordem("Kahn", ordem_kahn, tamanho_kahn);
        free(ordem_kahn);
    } else {
        printf("Kahn: ciclo detectado, ordenacao impossivel.\n");
    }

    int tamanho_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);

    if (ordem_dfs != NULL) {
        imprimir_ordem("DFS", ordem_dfs, tamanho_dfs);
        free(ordem_dfs);
    } else {
        printf("DFS: ciclo detectado, ordenacao impossivel.\n");
    }

    liberar_grafo_lista(g);
}

int main(void) {
    testar_dag();
    testar_ciclo();

    return 0;
}