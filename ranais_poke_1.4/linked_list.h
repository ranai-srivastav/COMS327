//
// Created by ranai on 10/6/22.
//

#ifndef RANAIS_POKE_1_4_LINKED_LIST_H
#define RANAIS_POKE_1_4_LINKED_LIST_H

//
// Created by ranai on 10/6/22.
// Credits: base code from GeeksForGeeks: https://www.geeksforgeeks.org/generic-linked-list-in-c-2/
// with additions from @author Ranai Srivastav
//


// C program for generic linked list
#include<stdio.h>
#include<stdlib.h>
//#include "map.h"


typedef struct ll_node ll_node_t;
/* A linked list node */

typedef enum player
{
    NONE,
    PLAYER_CHARACTER,
    RIVAL, // 2
    HIKER,
    PACER,
    WANDERER,
    SENTRIES,
    EXPLORERS // 7
} player_type;

struct ll_node
{
    //    point_t *vector;
    int curr_pos_x;
    int curr_pos_y;
    player_type type;
    int index;
    ll_node_t *next;
};

typedef struct linked_l
{
    ll_node_t *head;
    int size;
}linked_list_t;

void ll_push(linked_list_t *ll, ll_node_t *new_data, size_t data_size);

void ll_printList(linked_list_t *ll, void (*fptr)(void *));

void ll_printInt(void *n);

void ll_printFloat(void *f);

ll_node_t* ll_get(linked_list_t *ll, int i);

#endif //RANAIS_POKE_1_4_LINKED_LIST_H
