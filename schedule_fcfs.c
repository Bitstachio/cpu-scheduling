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

    if (task->priority < MIN_PRIORITY || task->priority > MAX_PRIORITY ||
        task->burst < 0) {
        fprintf(stderr, "Invalid Tasks in Input File");
        exit(EXIT_FAILURE);
    }

    insertQueue(&queue, task);
}

void schedule() {
    Node *node;
    int numProcesses = 0;

    double turnAroundTime = 0;
    double turnAroundTimeTotal = 0;
    double waitTimeTotal = 0;

    while ((node = removeQueue(&queue)) != NULL) {
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