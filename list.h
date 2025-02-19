/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

typedef struct node {
    Task *task;
    struct node *next;
} Node;

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

// insert and delete operations.
void insert(Node **head, Task *task);
void delete(Node **head, Task *task);
void traverse(Node *head);

void insertQueue(Queue *queue, Task *task);
Node *removeQueue(Queue *queue);

void insertSorted(Node **head, Task *task);
Node *pop(Node **head);