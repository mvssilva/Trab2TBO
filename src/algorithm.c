#include "algorithm.h"
#include "PQ.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

struct Dist{
    int dest;
    double weight;
};

double ** _aloca_array(int size){
    double ** a = (double **) malloc(size * sizeof(double*));
    
    for(int i = 0; i < size; i ++)
        a[i] = (double *) malloc(size * sizeof(double));
    return a;
}

Dist * _creat_vector_dist(int qtd){

    
}

void _distance_calculation(Graph * g, double * dist){

}

double **algoritm_Dijkstra(Graph *g)
{   
    int qtdC = graph_get_qtd_C(g);
    int qtdM = graph_get_qtd_M(g);
    int qtdS = graph_get_qtd_S(g);
    int qtdV = graph_get_qtd_V(g);

    int vertexImportant = qtdC + qtdM + qtdS;

    double ** result = _aloca_array(vertexImportant);
    Dist * dist = _creat_vector_dist(qtdV);
    PQ_init(qtdV);


    for(int i = 0; i < qtdV; i ++){
        if(graph_get_type_v(g, i)){
            _distance_calculation(g, dist);
        }
    }


}