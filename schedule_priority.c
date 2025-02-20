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
    Node *node;
    int numProcesses = 0;

    double turnAroundTime = 0;
    double turnAroundTimeTotal = 0;
    double waitTimeTotal = 0;

    while ((node = pop(&head)) != NULL) {
        run(node->task, node->task->burst);

        waitTimeTotal += turnAroundTime;
        turnAroundTime += node->task->burst;
        turnAroundTimeTotal += turnAroundTime;

        numProcesses++;
    }

    printf("\nAverage waiting time = %.2f", waitTimeTotal / numProcesses);
    printf("\nAverage turnaround time = %.2f", turnAroundTimeTotal / numProcesses);
    printf("\nAverage response time = %.2f", waitTimeTotal / numProcesses);
}