#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "../pratica01/grafo_lista.h"

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

void dfs_recursiva(
    GrafoLista *g,
    int u,
    int *visitado,
    int *tempo_entrada,
    int *tempo_saida,
    int *tempo
);

void dfs(GrafoLista *g, int *tempo_entrada, int *tempo_saida);

int tem_ciclo(GrafoLista *g);

int contar_componentes(GrafoLista *g);

int eh_bipartido(GrafoLista *g);

#endif