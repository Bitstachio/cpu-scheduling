#include "list.h"
#include "schedulers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *head = NULL;

int compareByPriority(const Task *a, const Task *b) {
    return b->priority - a->priority;
}

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;

    insertSorted(&head, task, compareByPriority);
}

void schedule() {
    Node *curr = NULL;
    for (int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--) {
        Queue queue = {.head = NULL, .tail = NULL};

        if (curr == NULL) {
            curr = pop(&head);
        }

        while (curr != NULL && curr->task->priority == i) {
            insertQueue(&queue, curr->task);
            curr = curr->next;
        }

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
}
