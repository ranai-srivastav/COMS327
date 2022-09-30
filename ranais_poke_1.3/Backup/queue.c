/**
 * A C program to demonstrate linked list based implementation of queue
 * Credits GeeksForGeeks: https://www.geeksforgeeks.org/queue-linked-list-implementation/
 */
#include "queue.h"


q_node_t* newNode(point_t *point)
{
    q_node_t* temp = (q_node_t*)malloc(sizeof(q_node_t));
    temp->point = point;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
queue_t* createQueue()
{
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a key point to q
void enQueue(queue_t *q, point_t *point)
{
    // Create a new LL node
    q_node_t* temp = newNode(point);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->size = 1;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
    q->size += 1;
}

// Function to remove a key from given queue q
q_node_t* deQueue(queue_t *q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
    {
        return NULL;
    }


    // Store previous front and move front one node ahead
    q_node_t *temp = q->front;

    q->front = q->front->next;
    q->size -= 1;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    return temp;
}