/**
 *  Priority Queue
 *  Base Code: GeeksForGeeks.org https://www.geeksforgeeks.org/priority-queue-using-linked-list/
 *  @author: Ranai Srivastav - @ranais
 *  @version: 1
 */
#include <stdio.h>
#include "priority_queue.h"
#include "stdlib.h"


void priority_q_init(priority_queue_t *pq, point_t *point, int priority)
{
    pq->head = malloc(sizeof(node_t));
    pq->head->data = point;
    pq->head->priority = priority;
    pq->head->next = NULL;
}

/**
 * Function to Create A New Node
 * @param d
 * @param p
 * @return
 */
node_t* newNode(point_t *d, int p)
{
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}

/**
 * Return the value at head
 * @param pq
 * @return
 */
point_t* peek(priority_queue_t *pq)
{
    return (pq->head->data);
}

/**
 * Removes the element with the highest priority from the list.
 * This will always be the head
 * @param pq
 */
void pop(priority_queue_t* pq)
{
    node_t* temp = pq->head;
    pq->head = pq->head->next;
    free(temp);
}

/**
 * Function to push according to priority
 * @param pq
 * @param d
 * @param p
 */
void push(priority_queue_t* pq, point_t *d, int p)
{
    node_t* start = pq->head;

    // Create new Node
    node_t* temp = newNode(d, p);

    if( !temp->priority && temp->data)
    {
        printf("===================================\n"
               "THE CODE IS ATTEMPTING TO ADD A NULL DATA ELEMENT. WTF. WTOP IT RIGHT HERE\n"
               "============================================");

    }

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if (pq->head->priority > p)
    {
        // Insert New Node before head
        temp->next = pq->head;
        pq->head = temp;
    }
    else {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL && start->next->priority < p)
        {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

/**
 * // Function to check is list is empty
 * @param pq
 * @return
 */
int isEmpty(priority_queue_t *pq)
{
    return pq->head == NULL;
}
