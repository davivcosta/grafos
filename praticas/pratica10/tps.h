#ifndef TPS_H
#define TPS_H
#include "hamiltoniano.h"

void grafo_para_tsp(Grafo *g);
int tsp_forca_bruta(Grafo *g, int *melhor_caminho);
int tsp_vizinho_mais_proximo(Grafo *g, int *caminho);
int tsp_insercao(Grafo *g, int *caminho);

#endif