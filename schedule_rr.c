#include "list.h"
#include "schedulers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Queue queue = {.head = NULL, .tail = NULL};
int id = 0;
int numProcesses = 0;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = strdup(name);
    task->priority = priority;
    task->burst = burst;
    task->tid = id++;

    insertQueue(&queue, task);
    numProcesses++;
}

void schedule() {
    Node *node;
    double completionTimes[numProcesses];

    int burstTimes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        burstTimes[i] = -1;
    }

    double startTimes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        startTimes[i] = -1;
    }

    double turnAroundTime = 0;
    double turnAroundTimeTotal = 0;
    double responseTimeTotal = 0;
    double waitTimeTotal = 0;

    while ((node = removeQueue(&queue)) != NULL) {
        Task *task = node->task;

        if (burstTimes[task->tid] < 0) {
            burstTimes[task->tid] = task->burst;
        }

        if (startTimes[task->tid] < 0) {
            startTimes[task->tid] = turnAroundTime;
        }

        const int slice = task->burst >= QUANTUM ? QUANTUM : task->burst;
        run(node->task, slice);

        turnAroundTime += slice;
        completionTimes[task->tid] = turnAroundTime;

        task->burst -= slice;
        if (task->burst > 0) {
            insertQueue(&queue, task);
        }
    }

    for (int i = 0; i < numProcesses; i++) {
        turnAroundTimeTotal += completionTimes[i];
        waitTimeTotal += completionTimes[i] - burstTimes[i];
    }

    for (int i = 0; i < numProcesses; i++) {
        responseTimeTotal += startTimes[i];
    }

    printf("\nAverage waiting time = %.2f", waitTimeTotal / numProcesses);
    printf("\nAverage turnaround time = %.2f",
           turnAroundTimeTotal / numProcesses);
    printf("\nAverage response time = %.2f", responseTimeTotal / numProcesses);
}