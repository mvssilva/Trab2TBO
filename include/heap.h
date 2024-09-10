#if !defined(HEAP_H_)
#define HEAP_H_

#include "item.h"

typedef struct Heap Heap;

Heap * heap_init(int);
void heap_fix_up(Heap *, int);
void heap_fix_down(Heap *, int );
void heap_insert(Item *, Heap *);
Item *heap_delete_min(Heap *);
void heap_decrease_key(Heap *, int, double);
Item *heap_min(Heap *);
int heap_empty(Heap *);
int heap_size(Heap *);
void heap_destruct(Heap *);
int heap_size_get_id(Heap *, int);
double heap_size_get_value(Heap *, int);


#endif // HEAP_H_
