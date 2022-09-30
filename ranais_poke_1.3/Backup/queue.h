#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "map.h"

// A linked list (LL) node to store a queue entry
typedef struct QNode q_node_t;

struct QNode
{
    point_t *point;
    q_node_t *next;
};

// The queue, front stores the front node of LL and rear stores the
// last node of LL
typedef struct Queue
{
    q_node_t *front, *rear;
    int size;
} queue_t;

// A utility function to create a new linked list node.
q_node_t* newNode(point_t *point);

// A utility function to create an empty queue
queue_t* createQueue();

// The function to add a key point to q
void enQueue(queue_t *q, point_t *point);

// Function to remove a key from given queue q
q_node_t* deQueue(queue_t *q);

#endif