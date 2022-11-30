#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#include <stdlib.h>
#include "assertx.h"
#include <math.h>
#include <limits.h>
#include <stdbool.h>
typedef struct binary_heap binary_heap;
typedef struct Item Item;

binary_heap* new_binary_heap(int size);

void insert(binary_heap* h, int x, double value);

double heap_get_priority_top(binary_heap* h);

void decrease_key(binary_heap* h, int id, double value);

int remove_(binary_heap* h);

int top_heap(binary_heap* h);

int get_size_binary_heap(binary_heap* h);

void clear_binary_heap(binary_heap* h);

void show_binary_heap(binary_heap* h);

void delete_binary_heap(binary_heap* h);




#endif //HEAP_H
