#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
struct Heap{
    Item ** pq;
    int * map;
    int size;
    int sizemax;
};

Heap * heap_init(int v)
{
    Heap * h = (Heap*)malloc(sizeof(Heap));
    h->pq = (Item **) malloc((v) * sizeof (Item*));
    h->map = (int *) malloc((v) * sizeof (int));

    for(int i = 0; i < v; i++)
        h->map[i] = -1;

    h->size = 0;
    h->sizemax = v;
    return h;
}

void heap_insert(Item * v, Heap * h){
    if(h->map[v->id] == -1){
        h->pq[h->size] = v;
        h->map[v->id] = h->size;
        heap_fix_up(h, h->size);
        h->size++;
    }else{
        if(h->pq[v->id]->value > v->value)
            heap_decrease_key(h, v->id, v->value);
    }

}

void _swap(Heap * h, int i, int j){
    Item *temp = h->pq[i];
    h->pq[i] = h->pq[j];
    h->pq[j] = temp;

    h->map[h->pq[i]->id] = i;
    h->map[h->pq[j]->id] = j;

}

Item *heap_delete_min(Heap * h)
{   
    if (h->size == 0) exit(printf("Heap underflow\n"));
    Item *min = h->pq[0];
    _swap(h, h->size -1, 0);
    h->map[min->id] = -1;
    h->size--;
    heap_fix_down(h, 0);
    return min;
}

void heap_fix_up(Heap * h, int k){

    while(k > 0){

        int parent = (k - 1) / 2;
        Item *a = h->pq[parent];
        Item *b = h->pq[k];

        if(a->value > b->value){
            _swap(h, k, parent);
            k = parent;
        }
        else
            break;
    }
}

void heap_fix_down(Heap * h, int k){
    int parent = k; 
    while (2 * parent + 1 < h->size) {
        int j = 2 * parent + 1;

        if (j + 1 < h->size && h->pq[j]->value > h->pq[j + 1]->value) 
            j++;  
        
        if (h->pq[parent]->value <= h->pq[j]->value) 
            break;  
        
        _swap(h, parent, j);
        parent = j;
    }

}

void heap_decrease_key(Heap * h, int id, double value){
    int i = h->map[id];
    h->pq[i]->value = value;
    heap_fix_up(h, i);
}

Item * heap_min(Heap * h)
{
    return h->pq[0];
}

int heap_empty(Heap * h)
{
    if(h->size == 0)
        return 0;

    return 1;
}

int heap_size(Heap *h){
    return h->size;
}

void heap_destruct(Heap *h){
    free(h->map);
    free(h->pq);
    free(h);
}

int heap_size_get_id(Heap *h, int i)
{
    return h->pq[i]->id;
}

double heap_size_get_value(Heap *h, int i)
{
    return h->pq[i]->value;
}
