#include "heap.h"

typedef struct Item Item;

struct Item{
    int id;
    double value;
};

struct binary_heap{
    Item* pq;
    int* map;
    int maxN;
    int n;
};

static void print_map(binary_heap* h){
    int i;
    for(i = 0; i < h->maxN; i++){
        printf("index: %d, in the heap: %d\n", i, h->map[i]);
    }
}


//=======================Static============================
//otimização futura: não usar função more, passar o ponteiro é bobagem
static int more(Item* a, Item* b){
    return (a->value > b->value);
}

static void swap(binary_heap* h, int i, int j) {
    int map_i = h->map[h->pq[i].id];
    int map_j = h->map[h->pq[j].id];

    //troca conteúdos
    Item temp = h->pq[i];
    h->pq[i] = h->pq[j];
    h->pq[j] = temp;


    h->map[h->pq[i].id] = map_i;
    h->map[h->pq[j].id] = map_j;

}


static void fix_up(binary_heap* h,  int k){
    while ( k > 1 && more( &(h->pq[k/2]), &(h->pq[k]) ) ){
        swap(h, k, k/2);
        k = k/2;
    }
}

static void fix_down(binary_heap* h, int sz, int k){
    while (2*k <= sz) {
        int j = 2*k;
        if (j < sz && more( &(h->pq[j]), &(h->pq[j+1]) ) ){
            j++;
        }
        if (!more( &(h->pq[k]), &(h->pq[j]) ) ) {
            break;
        }
        swap(h, k, j);
        k = j;
  }
}



static Item remove_min(binary_heap* h){
    Item min = h->pq[1];
    swap(h, 1, h->n);
    h->n--;
    fix_down(h, h->n, 1);
    
    return min;
}

static Item pq_min(binary_heap* h){
    return h->pq[1];
}

static void print_item(Item a){
    printf("Item ( id = %d, value = %.2lf )\n", a.id, a.value);
}

/*static void print_map(binary_heap* h){
    int i;
    for(i = 0; i < h->maxN; i++){
        printf("index: %d, in the heap: %d\n", i, h->map[i]);
    }
}*/


//===========================================================

Item new_item(int id, double value){
    Item i;
    i.id = id;
    i.value = value;
    return i;
}

binary_heap* new_binary_heap(int size){
    binary_heap* h = malloc(sizeof(binary_heap));
    assertx(h!=NULL, "HEAP NULL");
    h->pq = malloc((size+1)*sizeof(Item));
    assertx(h->pq != NULL, "ITEM ARRAY NULL");
    h->map = malloc((size)*sizeof(int));
    assertx(h->map != NULL, "MAP IS NULL");
    for(int i = 0; i < size; i++){
        h->map[i] = -1;
    }
    h->n = 0;
    h->maxN = size;
    return h;
}


void insert(binary_heap* h, int x, double value){
    assertx(h!=NULL, "HEAP NULL");
   
    Item v = new_item(x, value);
    h->n++;
    h->pq[h->n] = v;
    h->map[x] = h->n;
    fix_up(h, h->n);
}


double heap_get_priority_top(binary_heap* h){
    return pq_min(h).value;
}

int top_heap(binary_heap* h){
    return pq_min(h).id;
}

int remove_(binary_heap* h){
    Item t = remove_min(h);
    return t.id;
}

int get_size_binary_heap(binary_heap* h){
    return h->n;
}

bool pq_empty(binary_heap* h){
    return h->n == 0;
}

void decrease_key(binary_heap* h, int id, double value){
    int i = h->map[id];
    h->pq[i].value = value;

    fix_up(h, i);

}


/*static void print_item(Item a){
    printf("Item ( id = %d, value = %.2lf )\n", a.id, a.value);
}*/

void show_binary_heap(binary_heap* h){
    for(int i = 1; i <= h->n; i++){
        printf("Posicao %d :", i);
        print_item(h->pq[i]);
    }
}


void delete_binary_heap(binary_heap* h){
    free(h->map);
    free(h->pq);
    free(h);
}