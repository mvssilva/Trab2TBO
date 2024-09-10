#if !defined(GRAPH_H_)
#define GRAPH_H_

typedef struct Graph Graph;
typedef struct AdjList AdjList;
typedef struct Node Node;

Graph * graph_construct(int, int, int, int, int);
Graph * read_file(char *);

void graph_add_node(AdjList*, int, double);
void print_graph(Graph*);

int graph_get_size_C_M_S(Graph*);
int graph_get_size_C(Graph*);
int graph_get_size_V(Graph*);
int graph_get_size_S(Graph*);
int graph_get_size_M(Graph*);

int * graph_get_vector_v_import(Graph*);
int graph_get_type_v(Graph*, int);
char graph_get_type_vertex(Graph*, int);

int graph_get_idx_s_in_cost(Graph*, int);
int graph_get_idx_c_in_cost(Graph*, int);
int graph_get_idx_m_in_cost(Graph*, int);

int graph_get_size_adj(Graph*, int);
int graph_get_idx_adj(Graph*, int, int);
double graph_get_value_adj(Graph*, int, int);

void graph_free_vector_v_import(int*);
void graph_destruct(Graph *);

#endif // GRAPH_H_
