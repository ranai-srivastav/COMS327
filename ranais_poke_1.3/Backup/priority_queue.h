// C code to implement Priority Queue
// using Linked List

#include "map.h"

// Node
typedef struct node
{
    point_t *data;
    // Lower values indicate higher priority
    int priority;
    struct node* next;

}Node;

// Function to Create A New Node
Node* newNode(point_t d, int p);

// Return the value at head
point_t peek(Node** head);

// Removes the element with the
// highest priority form the list
void pop(Node** head);

// Function to push according to priority
void push(Node** head, point_t d, int p);

// Function to check is list is empty
int isEmpty(Node** head);
