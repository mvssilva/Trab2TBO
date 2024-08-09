#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

static Item *pq;
static int *map;
static int N;

static void swap(int i, int j) {
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j);
    k = j;
  }
}

void PQ_init(int maxN) {
    pq = (Item *) malloc((maxN+1) * sizeof (Item));
    map = (int *) malloc((maxN+1) * sizeof (int));
    N = 0;
}

void PQ_insert(Item v) {
    N++;
    pq[N] = v;
    map[id(v)] = N;
    fix_up(pq, N);
}

Item PQ_delmin() {
    Item min = pq[1];
    swap(1, N);
    N--;
    fix_down(pq, N, 1);
    return min;
}

Item PQ_min() {
    return pq[1];
}

void PQ_decrease_key(int id, double value) {
    int i = map[id];
    value(pq[i]) = value;
    fix_up(pq, i);
}

bool PQ_empty() {
    return N == 0;
}

int  PQ_size() {
    return N;
}

void PQ_finish() {
    free(pq);
    free(map);
}


// #include <stdio.h>
// #include "PQ.h"
// #include "item.h"

// Item make_item(int id, double value) {
//     Item t;
//     id(t) = id;
//     value(t) = value;
//     return t;
// }

// int main() {

//     // inicializando a PQ
//     PQ_init(10);

//     // inserindo alguns elementos na PQ
//     PQ_insert(make_item(1, 10.0));
//     PQ_insert(make_item(6, 5.0));
//     PQ_insert(make_item(3, 3.0));
//     PQ_insert(make_item(4, 4.0));
//     PQ_insert(make_item(7, 7.0));
//     PQ_insert(make_item(2, 1.0));

//     // alterando a prioridade de alguns elementos
//     PQ_decrease_key(4, 0.5); // agora o nó 4 tem valor 0.5, sua posição no heap deve mudar
//     PQ_decrease_key(6, 0.1); // agora o nó 6 tem valor 0.1, sua posição no heap deve mudar

//     // removendo o menor elemento e imprimindo
//     while (!PQ_empty()) {
//         Item p = PQ_delmin();
//         printf("Identificador %d, prioridade %lf\n", id(p), value(p));
//     }
// }