#include "list.h"
#include "schedulers.h"

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
        Task *task = node->task;

        const int slice = node->next == NULL       ? task->burst
                          : task->burst >= QUANTUM ? QUANTUM
                                                   : task->burst;
        run(node->task, slice);

        task->burst -= slice;
        if (task->burst > 0) {
            insertQueue(&queue, task);
        }
    }
}