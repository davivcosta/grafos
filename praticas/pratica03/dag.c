#include <stdio.h>
#include <stdlib.h>

#include "dag.h"

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (g == NULL || tamanho == NULL) {
        return NULL;
    }

    *tamanho = 0;

    int *grau_entrada = calloc(g->n, sizeof(int));
    int *fila = malloc(g->n * sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));

    if (grau_entrada == NULL || fila == NULL || ordem == NULL) {
        free(grau_entrada);
        free(fila);
        free(ordem);
        return NULL;
    }

    /* Calcula o grau de entrada de cada vertice. */
    for (int u = 0; u < g->n; u++) {
        No *atual = g->adj[u];

        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    /* Coloca na fila todos os vertices com grau de entrada zero. */
    int inicio = 0;
    int fim = 0;

    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    /* Algoritmo de Kahn. */
    while (inicio < fim) {
        int u = fila[inicio++];

        ordem[*tamanho] = u;
        (*tamanho)++;

        No *atual = g->adj[u];

        while (atual != NULL) {
            int v = atual->destino;

            grau_entrada[v]--;

            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }

            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    /*
     * Se nem todos os vertices foram processados,
     * o grafo possui ciclo.
     */
    if (*tamanho != g->n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    return ordem;
}

static int dfs_topologica(
    GrafoLista *g,
    int u,
    int *estado,
    int *ordem,
    int *posicao
) {
    /*
     * Estado:
     * 0 = nao visitado
     * 1 = visitando
     * 2 = finalizado
     */
    estado[u] = 1;

    No *atual = g->adj[u];

    while (atual != NULL) {
        int v = atual->destino;

        /* Encontrou uma aresta de retorno: existe ciclo. */
        if (estado[v] == 1) {
            return 0;
        }

        if (estado[v] == 0) {
            if (!dfs_topologica(g, v, estado, ordem, posicao)) {
                return 0;
            }
        }

        atual = atual->prox;
    }

    estado[u] = 2;

    /* Empilha o vertice na saida da DFS. */
    ordem[--(*posicao)] = u;

    return 1;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (g == NULL || tamanho == NULL) {
        return NULL;
    }

    *tamanho = 0;

    int *estado = calloc(g->n, sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));

    if (estado == NULL || ordem == NULL) {
        free(estado);
        free(ordem);
        return NULL;
    }

    int posicao = g->n;

    for (int i = 0; i < g->n; i++) {
        if (estado[i] == 0) {
            if (!dfs_topologica(g, i, estado, ordem, &posicao)) {
                free(estado);
                free(ordem);
                return NULL;
            }
        }
    }

    *tamanho = g->n;

    free(estado);

    return ordem;
}

int eh_dag(GrafoLista *g) {
    if (g == NULL) {
        return 0;
    }

    int tamanho = 0;

    int *ordem = ordenacao_topologica_kahn(g, &tamanho);

    if (ordem == NULL) {
        return 0;
    }

    free(ordem);

    return tamanho == g->n;
}