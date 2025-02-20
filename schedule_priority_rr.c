#include "list.h"
#include "schedulers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *head = NULL;
int id = 0;
int numProcesses = 0;

int compareByPriority(const Task *a, const Task *b) {
    return b->priority - a->priority;
}

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;
    task->tid = id++;

    if (task->priority < MIN_PRIORITY || task->priority > MAX_PRIORITY ||
        task->burst < 0) {
        fprintf(stderr, "Invalid Tasks in Input File");
        exit(EXIT_FAILURE);
    }

    insertSorted(&head, task, compareByPriority);
    numProcesses++;
}

void schedule() {
    Node *curr = NULL;
    double completionTimes[numProcesses];

    int burstTimes[numProcesses];
    double startTimes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        burstTimes[i] = -1;
        startTimes[i] = -1;
    }

    double turnAroundTime = 0;
    double turnAroundTimeTotal = 0;
    double responseTimeTotal = 0;
    double waitTimeTotal = 0;

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

            // first encounter with task
            if (burstTimes[node->task->tid] < 0) { // also: startTimes[task->tid] < 0
                burstTimes[node->task->tid] = node->task->burst;
                startTimes[task->tid] = turnAroundTime;
            }

            const int slice = node->next == NULL       ? task->burst
                              : task->burst >= QUANTUM ? QUANTUM
                                                       : task->burst;
            run(node->task, slice);

            turnAroundTime += slice;
            completionTimes[task->tid] = turnAroundTime;

            task->burst -= slice;
            if (task->burst > 0) {
                insertQueue(&queue, task);
            }
        }
    }

    for (int i = 0; i < numProcesses; i++) {
        turnAroundTimeTotal += completionTimes[i];
        waitTimeTotal += completionTimes[i] - burstTimes[i];
        responseTimeTotal += startTimes[i];
    }

    printf("\nAverage waiting time = %.2f", waitTimeTotal / numProcesses);
    printf("\nAverage turnaround time = %.2f", turnAroundTimeTotal / numProcesses);
    printf("\nAverage response time = %.2f", responseTimeTotal / numProcesses);
}
