#include "dijkstra.h"

// --- Implementação Básica do Grafo ---
GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado* g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->listas_adj = (Aresta**) malloc(num_vertices * sizeof(Aresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas_adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado* g, int origem, int destino, int peso) {
    Aresta* nova_aresta = (Aresta*) malloc(sizeof(Aresta));
    nova_aresta->destino = destino;
    nova_aresta->peso = peso;
    nova_aresta->prox = g->listas_adj[origem];
    g->listas_adj[origem] = nova_aresta;
}

void liberar_grafo(GrafoListaPonderado* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta* atual = g->listas_adj[i];
        while (atual != NULL) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas_adj);
    free(g);
}

// --- Funções do Min-Heap ---
MinHeap* criar_min_heap(int capacidade) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    return heap;
}

// Função auxiliar para trocar nós no heap e atualizar suas posições
void trocar_no_heap(MinHeap* heap, int i, int j) {
    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;

    // Atualiza o mapeamento de posições
    heap->posicao[heap->dados[i].vertice] = i;
    heap->posicao[heap->dados[j].vertice] = j;
}

// Restaura a propriedade do Min-Heap descendo o nó
void min_heapify(MinHeap* heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].distancia < heap->dados[menor].distancia)
        menor = esq;
    if (dir < heap->tamanho && heap->dados[dir].distancia < heap->dados[menor].distancia)
        menor = dir;

    if (menor != idx) {
        trocar_no_heap(heap, menor, idx);
        min_heapify(heap, menor);
    }
}

NoHeap extrair_minimo(MinHeap* heap) {
    if (heap->tamanho == 0) {
        NoHeap vazio = {-1, -1};
        return vazio;
    }

    NoHeap raiz = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];
    
    heap->dados[0] = ultimo;
    heap->posicao[raiz.vertice] = heap->tamanho - 1; // Move para o final (logicamente removido)
    heap->posicao[ultimo.vertice] = 0;
    
    heap->tamanho--;
    min_heapify(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap* heap, int vertice, int nova_distancia) {
    int i = heap->posicao[vertice];
    heap->dados[i].distancia = nova_distancia;

    // Sobe o nó enquanto a distância dele for menor que a do pai
    while (i != 0 && heap->dados[i].distancia < heap->dados[(i - 1) / 2].distancia) {
        trocar_no_heap(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// --- Funções de Caminho ---
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap* heap = criar_min_heap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        pred[v] = -1;
        heap->dados[v].vertice = v;
        heap->dados[v].distancia = INT_MAX;
        heap->posicao[v] = v;
    }

    // Inicializa a origem
    heap->dados[origem].distancia = 0;
    dist[origem] = 0;
    heap->tamanho = V;
    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0) {
        NoHeap minNo = extrair_minimo(heap);
        int u = minNo.vertice;

        Aresta* atual = g->listas_adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            
            // Se o vértice 'v' ainda está no heap e encontramos um caminho menor
            if (heap->posicao[v] < heap->tamanho && dist[u] != INT_MAX && 
                atual->peso + dist[u] < dist[v]) {
                
                dist[v] = dist[u] + atual->peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            atual = atual->prox;
        }
    }

    // Limpeza de memória
    free(heap->posicao);
    free(heap->dados);
    free(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Nao ha caminho de %d para %d", origem, destino);
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}