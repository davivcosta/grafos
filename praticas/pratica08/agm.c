#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "agm.h"

// ==========================================
// 1. KRUSKAL (DSU com compressão e rank)
// ==========================================

DSU* criar_dsu(int n) {
    DSU *d = malloc(sizeof(DSU));
    d->n = n;
    d->pai = malloc(n * sizeof(int));
    d->rank = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
        d->rank[i] = 0;
    }
    return d;
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        // Compressão de caminho
        d->pai[x] = find(d, d->pai[x]); 
    }
    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int raizX = find(d, x);
    int raizY = find(d, y);
    
    if (raizX != raizY) {
        // União por rank
        if (d->rank[raizX] < d->rank[raizY]) {
            d->pai[raizX] = raizY;
        } else if (d->rank[raizX] > d->rank[raizY]) {
            d->pai[raizY] = raizX;
        } else {
            d->pai[raizY] = raizX;
            d->rank[raizX]++;
        }
    }
}

void liberar_dsu(DSU *d) {
    free(d->pai);
    free(d->rank);
    free(d);
}

// Função de comparação para o qsort (ordena as arestas por peso)
int comparar_arestas(const void *a, const void *b) {
    Aresta *a1 = (Aresta *)a;
    Aresta *a2 = (Aresta *)b;
    return a1->peso - a2->peso;
}

void kruskal(Grafo *g) {
    qsort(g->arestas, g->E, sizeof(Aresta), comparar_arestas);
    DSU *d = criar_dsu(g->V);
    int custo_total = 0;
    
    printf("Arestas selecionadas (Kruskal):\n");
    for (int i = 0; i < g->E; i++) {
        int u = g->arestas[i].u;
        int v = g->arestas[i].v;
        int peso = g->arestas[i].peso;
        
        if (find(d, u) != find(d, v)) {
            unir(d, u, v);
            custo_total += peso;
            printf("(%d, %d) - Peso: %d\n", u, v, peso);
        }
    }
    printf("Custo Total Kruskal: %d\n", custo_total);
    liberar_dsu(d);
}


// ==========================================
// 2. PRIM (Min-Heap e Lista de Adjacência)
// ==========================================

typedef struct NoAdj {
    int v, peso;
    struct NoAdj* prox;
} NoAdj;

typedef struct {
    int v, chave;
} HeapNode;

typedef struct {
    int size, capacity;
    int *pos;
    HeapNode **array;
} MinHeap;

void adicionar_aresta(NoAdj **adj, int u, int v, int peso) {
    NoAdj *novo = malloc(sizeof(NoAdj));
    novo->v = v; novo->peso = peso;
    novo->prox = adj[u];
    adj[u] = novo;
}

HeapNode* novo_heap_node(int v, int chave) {
    HeapNode* n = malloc(sizeof(HeapNode));
    n->v = v; n->chave = chave;
    return n;
}

MinHeap* criar_min_heap(int capacity) {
    MinHeap* h = malloc(sizeof(MinHeap));
    h->pos = malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->array = malloc(capacity * sizeof(HeapNode*));
    return h;
}

void swap_node(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void min_heapify(MinHeap* h, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < h->size && h->array[esq]->chave < h->array[menor]->chave) menor = esq;
    if (dir < h->size && h->array[dir]->chave < h->array[menor]->chave) menor = dir;

    if (menor != idx) {
        HeapNode* noMenor = h->array[menor];
        HeapNode* noIdx = h->array[idx];
        
        h->pos[noMenor->v] = idx;
        h->pos[noIdx->v] = menor;
        
        swap_node(&h->array[menor], &h->array[idx]);
        min_heapify(h, menor);
    }
}

HeapNode* extract_min(MinHeap* h) {
    if (h->size == 0) return NULL;
    HeapNode* raiz = h->array[0];
    HeapNode* ultimo = h->array[h->size - 1];
    
    h->array[0] = ultimo;
    h->pos[raiz->v] = h->size - 1;
    h->pos[ultimo->v] = 0;
    
    --h->size;
    min_heapify(h, 0);
    return raiz;
}

void decrease_key(MinHeap* h, int v, int chave) {
    int i = h->pos[v];
    h->array[i]->chave = chave;
    while (i && h->array[i]->chave < h->array[(i - 1) / 2]->chave) {
        h->pos[h->array[i]->v] = (i - 1) / 2;
        h->pos[h->array[(i - 1) / 2]->v] = i;
        swap_node(&h->array[i], &h->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void prim(Grafo *g, int inicio) {
    int V = g->V;
    int *pai = malloc(V * sizeof(int));
    int *chave = malloc(V * sizeof(int));
    
    // Constrói lista de adjacência para O(E) na varredura
    NoAdj **adj = calloc(V, sizeof(NoAdj*));
    for (int i = 0; i < g->E; i++) {
        adicionar_aresta(adj, g->arestas[i].u, g->arestas[i].v, g->arestas[i].peso);
        adicionar_aresta(adj, g->arestas[i].v, g->arestas[i].u, g->arestas[i].peso); // Aresta bi-direcional
    }

    MinHeap* h = criar_min_heap(V);
    for (int v = 0; v < V; v++) {
        pai[v] = -1;
        chave[v] = INT_MAX;
        h->array[v] = novo_heap_node(v, chave[v]);
        h->pos[v] = v;
    }

    chave[inicio] = 0;
    h->array[inicio] = novo_heap_node(inicio, chave[inicio]);
    h->pos[inicio] = inicio;
    decrease_key(h, inicio, chave[inicio]);
    h->size = V;

    while (h->size > 0) {
        HeapNode* minNode = extract_min(h);
        int u = minNode->v;

        NoAdj* p = adj[u];
        while (p != NULL) {
            int v = p->v;
            if (h->pos[v] < h->size && p->peso < chave[v]) {
                chave[v] = p->peso;
                pai[v] = u;
                decrease_key(h, v, chave[v]);
            }
            p = p->prox;
        }
        free(minNode);
    }

    int custo_total = 0;
    printf("Arestas selecionadas (Prim):\n");
    for (int i = 0; i < V; ++i) {
        if (pai[i] != -1) {
            printf("(%d, %d) - Peso: %d\n", pai[i], i, chave[i]);
            custo_total += chave[i];
        }
    }
    printf("Custo Total Prim: %d\n", custo_total);

    // Limpeza de memória
    free(pai); free(chave); free(h->pos); free(h->array); free(h);
    for (int i = 0; i < V; i++) {
        NoAdj *atual = adj[i];
        while (atual) {
            NoAdj *apagar = atual;
            atual = atual->prox;
            free(apagar);
        }
    }
    free(adj);
}