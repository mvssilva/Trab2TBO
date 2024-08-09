#if !defined(GRAPH_H_)
#define GRAPH_H_

typedef struct Graph Graph;
typedef struct AdjList AdjList;
typedef struct Node Node;


Graph * graph_construct(int, int, int, int, int);
Graph * read_file(char *);
void graph_add_node(AdjList*, int, double);
void print_graph(Graph*);
int graph_get_qtd_C(Graph*);
int graph_get_qtd_V(Graph*);
int graph_get_qtd_S(Graph*);
int graph_get_qtd_M(Graph*);
int graph_get_type_v(Graph*, int);


void graph_destruct(Graph *);

#endif // GRAPH_H_
