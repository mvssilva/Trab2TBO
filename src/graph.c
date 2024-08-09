#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Graph{
    AdjList * array;
    char *typeNode;

    int sizeV;
    int sizeE;
    int sizeC;
    int sizeS;
    int sizeM;   
};

struct AdjList{
    Node * head;
    int sizeList;
};

struct Node{
    int dest;
    double weight;
    Node * next;
};

Graph *graph_construct(int v, int e, int s, int c, int m)
{
    Graph * g = (Graph*) malloc(sizeof(Graph));
    g->sizeV = v;
    g->sizeE = e;
    g->sizeS = s;
    g->sizeC = c;
    g->sizeM = m;

    g->typeNode = (char*)calloc(v, sizeof(char));

    for (int i = 0; i < v; i++) 
        g->typeNode[i] = '\n';
    

    g->array = (AdjList*)malloc(v * sizeof(AdjList));

    for (int i = 0; i < v; i++){
        g->array[i].head = NULL;
        g->array[i].sizeList = 0;
    }
    

    return g;
}

Graph *read_file(char * directory)
{
    FILE *file = fopen(directory, "r");
    if (file == NULL)
        exit(1);
    
    int v, e, s, c, m;
    fscanf(file, "%d %d\n", &v, &e);
    fscanf(file, "%d %d %d\n", &s, &c, &m);

    Graph * G = graph_construct(v, e, s, c, m);

    char *line = NULL;
    size_t size = 0;
    int len;

    int tam = s + c + m;

    for(int i = 0; i < tam ; i ++){
        len = getline(&line, &size, file);
        if(i < s){
            int vertex = atoi(line);
            G->typeNode[vertex] =  's';
        }
        else if(i < s + c){
            int vertex = atoi(line);
            G->typeNode[vertex] =  'c';
        }
        else{
            int vertex = atoi(line);
            G->typeNode[vertex] =  'm';
        }
    }
    
    while ((len = getline(&line, &size, file)) != -1)
    {   
        line[len - 1] = '\0';

        char * src = strtok(line, " ");
        char * dest = strtok(NULL, " ");
        char * weight = strtok(NULL, " ");

        int src1 = atoi(src);
        int dest1 = atoi(dest);
        double weight1 = atof(weight);
        graph_add_node(&(G->array[src1]), dest1, weight1);
        
    }
    free(line);
    fclose(file);
    return G;
}

Node * node_construct(int dest, double weight){
    Node * node = (Node *) malloc (sizeof(Node));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;

    return node;
}

void graph_add_node(AdjList *src, int dest, double weight)
{   
    Node * new = node_construct(dest, weight);
    
    src->sizeList++;
    
    if(src->head == NULL)
    {
        src->head = new;
    }
    else
    {   
        Node * current = src->head;
        while (current->next != NULL)
        {   
            current = current->next;
        }
        current->next = new;
    }
}

int graph_get_qtd_M(Graph* g){
   return g->sizeM;
}

int graph_get_type_v(Graph *g, int idx)
{
    if(g->typeNode[idx] == '\n')
        return 0;

    return 1;
}

int graph_get_qtd_S(Graph* g){
   return g->sizeS;
}

int graph_get_qtd_C(Graph* g){
   return g->sizeC;
}

int graph_get_qtd_V(Graph* g){
   return g->sizeV;
}

void print_graph(Graph* g){
    int n = g->sizeV;
    for(int i = 0; i < n; i++){
        AdjList src = g->array[i];
        Node * n = src.head;
        for(int j = 0; j < src.sizeList; j++){
            printf("%d %d %.17f\n", i, n->dest, n->weight);
            n = n->next;
        }
    }
}

void graph_destruct(Graph * g){
    int n = g->sizeV;
    for(int i = 0; i < n; i++){
        AdjList src = g->array[i];
        Node * n = src.head;
        for(int j = 0; j < src.sizeList; j++){
            Node * aux = n->next;
            free(n);
            n = aux;
        }
    }

    free(g->array);
    free(g->typeNode);
    free(g);
}


