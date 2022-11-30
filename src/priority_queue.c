
#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

priority_queue* new_priority_queue(int size){
       return new_binary_heap(size); 
}

void push(priority_queue* q, int id, double value){
        insert(q, id, value);
}

double get_priority_top(priority_queue* q){
        return heap_get_priority_top(q);
}

void set_priority(priority_queue* q, int id, double value){
        decrease_key(q, id, value);
}

int pop(priority_queue* q){
        return remove_(q);
}


int top(priority_queue* q){
        return top_heap(q);
}

int size_queue(priority_queue* q){
        return get_size_binary_heap(q);
}

void clear(priority_queue* q){
        clear_binary_heap(q);
}

void show_inside_priority_queue(priority_queue* q){
        show_binary_heap(q);
}

void delete_priority_queue(priority_queue* q){
        delete_binary_heap(q);
}


