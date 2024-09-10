#include "rtt.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct rtt
{
    int s;          //Nome do vertice do servidor
    int c;          //Nome do vertice do computador
    double value;   //Custo para passagem de informações, RTT* (inflacionado);
};


rtt *_rtt_create(int size){
    rtt * r = (rtt*) malloc (size * sizeof(rtt));
    return r;
}


int value_compare(const void *a, const void *b)
{
    rtt *rtt1 = (rtt *)a;
    rtt *rtt2 = (rtt *)b;

    if (rtt1->value < rtt2->value)
    {
        return -1;
    }
    else if (rtt1->value > rtt2->value)
    {
        return 1;
    }
    return 0;
}

void _rtt_vector_sort(rtt *r, int size)
{
    qsort(r, size, sizeof(rtt), value_compare);
}

/**
 * Calcula o custo de transmissão de informações entre os vértices críticos
 * do grafo, com foco em identificar a rota de menor custo entre servidores 
 * e computadores.
 * 
 * @param g Ponteiro para a estrutura 'Graph' representando o grafo de entrada.
 * @param cost Ponteiro para a matriz de custos representando os pesos das arestas.
 * @return Vetor de estruturas 'rtt', onde cada elemento armazena o menor custo
 *         encontrado para transmitir informações entre um servidor e um computador.
 */
rtt *calculate_inflation(Graph * g, double **cost)
{   
    int sizeS = graph_get_size_S(g);
    int sizeC = graph_get_size_C(g);
    int sizeM = graph_get_size_M(g);
    
    rtt * result = (rtt*) malloc ((graph_get_size_C(g) * graph_get_size_S(g)) * sizeof(rtt));
    int * vertex = graph_get_vector_v_import(g);
    
    int cont = 0, minS = -1, minC = -1, minM = -1;
    double minValue = INT_MAX;
    
    for(int s = 0; s < sizeS; s++)
    {   
        // Essa funcao tem o retorno de idx do servidor na mesma posição que no vetor de inteiros 'vertex'
        // Fiz dessa maneira pra conseguir guardar os nomes do vértices, sem ter que adicionar outra variavel no struct.
        int idxS = graph_get_idx_s_in_cost(g, s); 
            for(int c = 0; c < sizeC; c++)
            {   
                int idxC = graph_get_idx_c_in_cost(g, c);
                    
                    for(int m = 0; m < sizeM; m++)
                    {   
                        int idxM = graph_get_idx_m_in_cost(g, m);
                        double value = cost[idxS][idxM] + cost[idxM][idxS] + cost[idxM][idxC] + cost[idxC][idxM];
                        value /= cost[idxS][idxC] + cost[idxC][idxS];
                        if(minValue > value){
                            minValue = value;
                            minS = idxS;
                            minC = idxC;
                        }
                    }
                    
                    // Salva o menor.
                    result[cont].s = vertex[minS];
                    result[cont].c = vertex[minC];
                    result[cont].value = minValue;
                    cont++;

                    // Reinicialização das variáveis.
                    minValue = INT_MAX;
                    minS = -1;
                    minC = -1;
                    minM = -1;
            }
    }
    // Ordernar pelo custo inflacionado.
    _rtt_vector_sort(result, cont);
    
    // Libera memória de vetor auxiliar.
    graph_free_vector_v_import(vertex);
    return result;
}

void write_result(rtt * r, char * directory, int size)
{
    FILE *file = fopen(directory, "w");
    if (file == NULL)exit(1);
    
    for(int i = 0; i < size; i++){
        fprintf(file, "%d %d ", r[i].s, r[i].c);
        if (r[i].value == (int)r[i].value) 
            fprintf(file, "%.1f\n", r[i].value);
        else 
            fprintf(file, "%.16f\n", r[i].value);
    
    }
    fclose(file);
}

void rtt_destruct(rtt * r){
    free(r);
}
