#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "heap.h"

typedef binary_heap priority_queue;

priority_queue* new_priority_queue(int size);

void push(priority_queue* q, int id, double value);



void set_priority(priority_queue* q, int id, double value);

int pop(priority_queue* q);

int top(priority_queue* q);

double get_priority_top(priority_queue* q);

int size_queue(priority_queue* q);

void show_inside_priority_queue(priority_queue* q);

void delete_priority_queue(priority_queue* q);


#endif