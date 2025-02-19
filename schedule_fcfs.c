#include "schedulers.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Queue queue = {.head = NULL, .tail = NULL};

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;

    insertQueue(&queue, task);
}

void schedule() {
    Node *node;
    while ((node = removeQueue(&queue)) != NULL) {
        run(node->task, node->task->burst);
    }
}