#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Graph{
    AdjList * array;
    char *typeNode;

    int sizeV;

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

    //Quantidade de vértices diferentes
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

/**
 * Função que lê os dados de um arquivo e constrói uma estrutura de grafo (`Graph`) a partir deles.
 * O arquivo de entrada deve conter as especificações do grafo, incluindo vértices, arestas, seus tipos e seus custos.
 * 
 * @param directory Caminho do arquivo de entrada que contém a definição do grafo.
 * @return Ponteiro para a estrutura `Graph`, criada a partir dos dados lidos do arquivo.
 */
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
        int src = atoi(line);

        if(i < s)
            G->typeNode[src] =  's';
        else if(i < s + c)
            G->typeNode[src] =  'c';
        else
            G->typeNode[src] =  'm';
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

int graph_get_size_M(Graph* g){
   return g->sizeM;
}

int graph_get_type_v(Graph *g, int idx)
{
    if(g->typeNode[idx] == '\n')
        return 0;

    return 1;
}

int graph_get_size_adj(Graph *g, int x)
{
    return g->array[x].sizeList;
}

char graph_get_type_vertex(Graph * g, int idx)
{
    return g->typeNode[idx];
}

int graph_get_idx_adj(Graph * g, int idx, int cont)
{
    Node * n = g->array[idx].head;

    for(int i = 0; i < cont; i++){
        n = n->next;
    }

    if(n == NULL)
        exit(printf("Error : funcao de retorno dos indices dos adjacentes!\n"));

    return n->dest;
}

int graph_get_idx_s_in_cost(Graph * g, int position)
{
    int size = graph_get_size_V(g);
    int cont  = 0;
    int x = 0;
    for(int i = 0; i < size; i++){
        if(g->typeNode[i] == '\n')
            continue;

        if(g->typeNode[i] == 's')
            cont++;
        
        if(cont - 1 == position){
            return x;
        }
        x++;
    }

    return -1;
}

int graph_get_idx_m_in_cost(Graph * g, int position)
{
    int size = graph_get_size_V(g);
    int cont  = 0;
    int x = 0;
    for(int i = 0; i < size; i++){
        if(g->typeNode[i] == '\n')
            continue;
        if(g->typeNode[i] == 'm')
            cont++;
        
        if(cont - 1 == position){
            return x;
        }
        x++;
    }

    return -1;
}

int graph_get_idx_c_in_cost(Graph * g, int position)
{
    int size = graph_get_size_V(g);
    int cont  = 0;
    int x = 0;
    for(int i = 0; i < size; i++){
         if(g->typeNode[i] == '\n')
            continue;
        if(g->typeNode[i] == 'c')
            cont++;
        
        if(cont - 1 == position){
            return x;
        }
        x++;
    }

    return -1;
}

double graph_get_value_adj(Graph * g, int idx, int cont)
{
    Node * n = g->array[idx].head;

    for(int i = 0; i < cont; i++){
        n = n->next;
    }

    if(n == NULL)
        exit(printf("Error : funcao de retorno dos values dos adjacentes!\n"));

    return n->weight;
}

void graph_free_vector_v_import(int * a)
{
    free(a);
}

int graph_get_size_C_M_S(Graph* g){
   return g->sizeS + g->sizeC + g->sizeM;
}

int graph_get_size_S(Graph* g){
   return g->sizeS;
}

int graph_get_size_C(Graph* g){
   return g->sizeC;
}

int graph_get_size_V(Graph* g){
   return g->sizeV;
}

int * graph_get_vector_v_import(Graph* g){
    int * r = (int*)malloc(graph_get_size_C_M_S(g) * sizeof(int));
    int idx = 0;
    int size = g->sizeV;
    for ( int i = 0; i < size; i++ ){
        if(g->typeNode[i] == 'c' || g->typeNode[i] == 's' || g->typeNode[i] == 'm')
            r[idx++] = i; 
    }

    return r;
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


