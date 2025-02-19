#include "list.h"
#include "schedulers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *head = NULL;

int compareByBurst(const Task *a, const Task *b) { return a->burst - b->burst; }

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;

    insertSorted(&head, task, compareByBurst);
}

void schedule() {
    Node *node;
    while ((node = pop(&head)) != NULL) {
        run(node->task, node->task->burst);
    }
}