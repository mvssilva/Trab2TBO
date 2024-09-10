#if !defined(ALGORITHM_H_)
#define ALGORITHM_H_

#include "graph.h"
#include "item.h"

double ** algoritm_Dijkstra(Graph *g);
void array_destruct(double ** cost, int size);

#endif // ALGORITHM_H_
