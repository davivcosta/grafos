#ifndef AGM_H
#define AGM_H

// Estruturas obrigatórias
typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

// Estrutura auxiliar para o Grafo
typedef struct {
    int V, E;
    Aresta *arestas;
} Grafo;

// Funções do DSU (Union-Find)
DSU* criar_dsu(int n);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void liberar_dsu(DSU *d);

// Funções da Prática
void kruskal(Grafo *g);
void prim(Grafo *g, int inicio);

#endif