#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "heap.h"

//O objetivo da priority_queue é fornecer um TAD com operações fixas.
//Foi necessário especialmente para o desenvolvimento do trabalho em equipe,
//sem alterar a interface fornecida aos colegas.

typedef binary_heap priority_queue;
/// @brief Create pq (priority queue)
/// @param size 
/// @return allocated priority queue
priority_queue* new_priority_queue(int size);

/// @brief Push a element to pq
/// @param q 
/// @param id 
/// @param value 
void push(priority_queue* q, int id, double value);

/// @brief Return the priority o first element of pq
/// @param q 
/// @return 
double get_priority_top(priority_queue* q);

/// @brief Change the priority o element
/// @param q 
/// @param id 
/// @param value 
void set_priority(priority_queue* q, int id, double value);

/// @brief Pop the first element
/// @param q 
/// @return id o top element
int pop(priority_queue* q);

/// @brief Get top element without removing
/// @param q 
/// @return top element
int top(priority_queue* q);

/// @brief Size of pq
/// @param q 
/// @return size
int size_queue(priority_queue* q);

/// @brief Set size of pq to 0
/// @param q 
void clear(priority_queue* q);

/// @brief Print all elements
/// @param q 
void show_inside_priority_queue(priority_queue* q);


/// @brief Free memory
/// @param q 
void delete_priority_queue(priority_queue* q);


#endif