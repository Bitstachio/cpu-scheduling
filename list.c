/**
 * Various list operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "task.h"

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    // add the new task to the list
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name, temp->task->name) == 0) {
        *head = (*head)->next;
    } else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority,
               temp->task->burst);
        temp = temp->next;
    }
}

void insertQueue(Queue *queue, Task *task) {
    Node *newNode = malloc(sizeof(Node));
    newNode->task = task;
    newNode->next = NULL;

    if (queue->tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

Node *removeQueue(Queue *queue) {
    if (queue->head == NULL) {
        return NULL;
    }

    Node *removedNode = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    return removedNode;
}

void insertSorted(Node **head, Task *task, const CompareFunc compare) {
    Node *newNode = malloc(sizeof(Node));
    newNode->task = task;
    newNode->next = NULL;

    if (*head == NULL || compare(newNode->task, (*head)->task) < 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *curr = *head;
    while (curr->next != NULL &&
           compare(curr->next->task, newNode->task) <= 0) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

Node *pop(Node **head) {
    if (*head == NULL) {
        return NULL;
    }

    Node *removedNode = *head;
    *head = (*head)->next;

    return removedNode;
}
