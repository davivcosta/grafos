#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

void dfs_recursiva(
    GrafoLista *g,
    int u,
    int *visitado,
    int *tempo_entrada,
    int *tempo_saida,
    int *tempo
) {
    visitado[u] = 1;

    (*tempo)++;
    tempo_entrada[u] = *tempo;

    No *atual = g->adj[u];

    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            dfs_recursiva(
                g,
                v,
                visitado,
                tempo_entrada,
                tempo_saida,
                tempo
            );
        }

        atual = atual->prox;
    }

    (*tempo)++;
    tempo_saida[u] = *tempo;
}

void dfs(GrafoLista *g, int *tempo_entrada, int *tempo_saida) {
    if (g == NULL || tempo_entrada == NULL || tempo_saida == NULL) {
        return;
    }

    int *visitado = calloc(g->n, sizeof(int));

    if (visitado == NULL) {
        return;
    }

    for (int i = 0; i < g->n; i++) {
        tempo_entrada[i] = 0;
        tempo_saida[i] = 0;
    }

    int tempo = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_recursiva(
                g,
                i,
                visitado,
                tempo_entrada,
                tempo_saida,
                &tempo
            );
        }
    }

    free(visitado);
}

int contar_componentes(GrafoLista *g) {
    if (g == NULL) {
        return 0;
    }

    int *visitado = calloc(g->n, sizeof(int));

    if (visitado == NULL) {
        return 0;
    }

    int componentes = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            componentes++;

            int *tempo_entrada = calloc(g->n, sizeof(int));
            int *tempo_saida = calloc(g->n, sizeof(int));
            int tempo = 0;

            if (tempo_entrada == NULL || tempo_saida == NULL) {
                free(tempo_entrada);
                free(tempo_saida);
                free(visitado);
                return 0;
            }

            dfs_recursiva(
                g,
                i,
                visitado,
                tempo_entrada,
                tempo_saida,
                &tempo
            );

            free(tempo_entrada);
            free(tempo_saida);
        }
    }

    free(visitado);

    return componentes;
}

int tem_ciclo(GrafoLista *g) {
    if (g == NULL) {
        return 0;
    }

    int *visitado = calloc(g->n, sizeof(int));

    if (visitado == NULL) {
        return 0;
    }

    int ciclo = 0;

    for (int inicio = 0; inicio < g->n && !ciclo; inicio++) {
        if (visitado[inicio]) {
            continue;
        }

        int *pilha_vertices = malloc(g->n * sizeof(int));
        int *pilha_pais = malloc(g->n * sizeof(int));

        if (pilha_vertices == NULL || pilha_pais == NULL) {
            free(pilha_vertices);
            free(pilha_pais);
            free(visitado);
            return 0;
        }

        int topo = 0;

        pilha_vertices[topo] = inicio;
        pilha_pais[topo] = -1;
        topo++;

        visitado[inicio] = 1;

        while (topo > 0 && !ciclo) {
            topo--;

            int u = pilha_vertices[topo];
            int pai = pilha_pais[topo];

            No *atual = g->adj[u];

            while (atual != NULL) {
                int v = atual->destino;

                if (!visitado[v]) {
                    visitado[v] = 1;

                    pilha_vertices[topo] = v;
                    pilha_pais[topo] = u;
                    topo++;
                } else if (v != pai) {
                    ciclo = 1;
                    break;
                }

                atual = atual->prox;
            }
        }

        free(pilha_vertices);
        free(pilha_pais);
    }

    free(visitado);

    return ciclo;
}

int eh_bipartido(GrafoLista *g) {
    if (g == NULL) {
        return 0;
    }

    int *cor = malloc(g->n * sizeof(int));

    if (cor == NULL) {
        return 0;
    }

    for (int i = 0; i < g->n; i++) {
        cor[i] = -1;
    }

    int *fila = malloc(g->n * sizeof(int));

    if (fila == NULL) {
        free(cor);
        return 0;
    }

    for (int inicio = 0; inicio < g->n; inicio++) {
        if (cor[inicio] != -1) {
            continue;
        }

        int inicio_fila = 0;
        int fim_fila = 0;

        cor[inicio] = 0;
        fila[fim_fila++] = inicio;

        while (inicio_fila < fim_fila) {
            int u = fila[inicio_fila++];

            No *atual = g->adj[u];

            while (atual != NULL) {
                int v = atual->destino;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila[fim_fila++] = v;
                } else if (cor[v] == cor[u]) {
                    free(fila);
                    free(cor);
                    return 0;
                }

                atual = atual->prox;
            }
        }
    }

    free(fila);
    free(cor);

    return 1;
}