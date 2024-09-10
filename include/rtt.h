#if !defined(RTT_H)
#define RTT_H

#include "graph.h"

typedef struct rtt rtt;

rtt * calculate_inflation(Graph * g, double ** cost);
void write_result(rtt *, char*, int);
void rtt_destruct(rtt *);
#endif