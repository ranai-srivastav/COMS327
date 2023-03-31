//
// Created by ranai on 10/3/22.
//

#ifndef RANAIS_POKE_1_1_PRIORITY_QUEUE_H
#define RANAIS_POKE_1_1_PRIORITY_QUEUE_H

/**
 * @author @ranais - Ranai Srivastav
 * @version 1
 * @date 28th Oct 2022
 */


typedef  struct node node_t;
// Node

struct node
{
    point_t *data;
    // Lower values indicate higher priority
    int priority;
    node_t *next;

};

typedef struct priority_queue
{
    node_t *head;
}priority_queue_t;

void priority_q_init(priority_queue_t *pq, point_t *point, int priority);

node_t* newNode(point_t *d, int p);

point_t* peek(priority_queue_t *pq);

void pop(priority_queue_t *pq);

void push(priority_queue_t *pq, point_t *d, int p);

void push_no_p(priority_queue_t *pq, point_t *d);

int isEmpty(priority_queue_t *pq);


#endif //RANAIS_POKE_1_1_PRIORITY_QUEUE_H