#include "algorithm.h"
#include "heap.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

double ** _aloca_array(int size){
    double ** a = (double **) malloc(size * sizeof(double*));
    
    for(int i = 0; i < size; i ++)
        a[i] = (double *) malloc(size * sizeof(double));
    return a;
}

void _miniun_distance(Graph * g, int idxV, Item * dist, Heap * h, int size){

    int sizeV = graph_get_size_V(g);
    
    for(int i = 0; i < sizeV; i++){
        if(i == idxV){
            dist[idxV].value = 0; // Inicializar o vertice de origem com custo 0;
            dist[idxV].id = idxV;

        }else{
            dist[i].value = INT_MAX;
            dist[i].id = i;
        }

        heap_insert(&dist[i], h);
    }

    while (heap_empty(h)) {
        Item * min = heap_delete_min(h);
        int sizeAdj = graph_get_size_adj(g, min->id); // Retorna a quantidade de ligações tem o vertice atual.
    
        for(int i = 0; i < sizeAdj; i++){ // Passa por todas esses vertices adjacentes.
            int idxDest = graph_get_idx_adj(g, min->id, i); // Consulto e pego os dados do vértice b/destino.
            double value = graph_get_value_adj(g, min->id, i);  

            //Verifico se para chegar no vertice b, passando pelo 'min' tem um custo menor do que o atual salvo em dist.
            Item * b = &dist[idxDest];
            if(min->value + value < b->value){ 
                b->value = min->value + value;
                heap_insert(b, h);                           
            }
        }
    }


}

/**
 * Implementa o algoritmo de Dijkstra no contexto de um grafo esparso, 
 * focando especificamente nos vértices identificados como críticos durante a leitura.
 *
 * @param graph Ponteiro para a estrutura 'Graph', representando o grafo processado.
 * @return Uma matriz de doubles onde cada par de índices {i, j} armazena o custo mínimo 
 * necessário para atravessar do vértice i ao vértice j no grafo original.
 */
double **algoritm_Dijkstra(Graph *g)
{   
    int sizeV = graph_get_size_V(g); // Quantidade de vertices totais do grafo.
    int sizeCSM = graph_get_size_C_M_S(g); // Quantida de vertices classificados como importantes/necessários.

    double ** cost = _aloca_array(sizeCSM); 

    Item * dist = (Item*)malloc(sizeV*sizeof(Item)); 
    int * vertex = graph_get_vector_v_import(g);

    Heap * h = heap_init(sizeV);

    for(int i = 0; i < sizeCSM; i ++){
        /*
            Passa por todos os vertices classificados na leitura como diferentes, os = (c, s, m);
            Faz o calculo da distancia da origem, um desses vértices diferentes, para todos os outros vertices no grafo.
            Salva as menores distancias, da origem para todos os outros vertices, na matriz result.
        */
        _miniun_distance(g, vertex[i], dist, h, sizeCSM);

        for(int j = 0; j < sizeCSM; j++){
            if(vertex[i] == vertex[j])
                continue;
            cost[i][j] = dist[vertex[j]].value;
        }
    }

    // for(int i = 0; i < sizeCSM; i ++){
    //     for(int j = 0; j < sizeCSM; j++){
    //         if(vertex[i] == vertex[j])
    //             continue;
    //         printf("[%d %d %f]", vertex[i], vertex[j], cost[i][j]);
    //     }
    //         printf("\n");
    // }

    // Liberação de memoria de estruturas auxiliares necessárias.
    free(dist);
    graph_free_vector_v_import(vertex);
    heap_destruct(h);

    return cost;
}


void array_destruct(double **a, int size) {
    for (int i = 0; i < size; i++) {
        free(a[i]);
    }
    free(a);
}