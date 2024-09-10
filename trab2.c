#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "algorithm.h"
#include "heap.h"
#include "rtt.h"

int main(int argc, char* argv[]){
        if(argc < 3)
            exit(printf("ERRO\nrun ./trab2 <input.txt> <output.txt>"));

    Graph *g = read_file(argv[1]);
    double ** cost = algoritm_Dijkstra(g);
    rtt * result = calculate_inflation(g, cost);
    write_result(result, argv[2], graph_get_size_C(g)*graph_get_size_S(g));
    
    rtt_destruct(result);
    array_destruct(cost, graph_get_size_C_M_S(g));
    graph_destruct(g);
    return 0;
}



