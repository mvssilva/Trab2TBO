#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(int argc, char* argv[]){
        if(argc < 3)
            exit(printf("ERRO\nrun ./main <input.txt> <output.txt>"));

    Graph *g = read_file(argv[1]);
    printf("\tread chek!\n");
    

    double ** minpath = algoritm_Dijkstra(g);


    graph_destruct(g);

    return 0;
}



