//
// Created by ranai on 10/6/22.
// Credits: base code from GeeksForGeeks: https://www.geeksforgeeks.org/generic-linked-list-in-c-2/
// with additions from @author Ranai Srivastav
//

#include "linked_list.h"
#include "map.h"


// C program for generic linked list
#include<stdio.h>
#include<stdlib.h>

/* Function to add a node at the beginning of Linked List.
   This function expects a pointer to the data to be added
   and size of the data type */
void ll_push(linked_list_t *ll, ll_node_t *new_data, size_t data_size)
{
    ll->size += 1;
    new_data->next = ll->head;
    ll->head = new_data;
//     Allocate memory for node
//    ll_node_t* new_node = (ll_node_t*)malloc(sizeof(ll_node_t));

//    new_node->
//    new_node->next = ll->head;

//     Copy contents of new_data to newly allocated memory.
//     Assumption: char takes 1 byte.
//    int i;
//    for (i=0; i<data_size; i++)
//        *(char *)(new_node->data + i) = *(char *)(new_data + i);


}

/* Function to print nodes in a given linked list. fpitr is used
   to access the function to be used for printing current node data.
   Note that different data types need different specifier in printf() */
//void ll_printList(linked_list_t *ll, void (*fptr)(void *))
//{
//    ll_node_t *node = ll->head;
//    while (node != NULL)
//    {
//        (*fptr)(node->data);
//        node = node->next;
//    }
//}

// Function to print an integer
void ll_printInt(void *n)
{
    printf(" %d", *(int *)n);
}

// Function to print a float
void ll_printFloat(void *f)
{
    printf(" %f", *(float *)f);
}

ll_node_t* ll_get(linked_list_t *ll, int i)
{
    int j = 0;
    ll_node_t *node = ll->head;
    for(j = 0; j != i; j++)
    {
        node = node->next;
    }

    return node;
}
