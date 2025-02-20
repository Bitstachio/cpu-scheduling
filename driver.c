/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "schedulers.h"
#include "task.h"

#include <ctype.h>
#include <stdbool.h>

#define SIZE 100

bool isFileEmpty(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1], "r");
    if (argc < 2 || !in || isFileEmpty(in)) {
        fprintf(stderr, "Invalid Tasks in Input File");
        exit(EXIT_FAILURE);
    }

    rewind(in);
    while (fgets(task, SIZE, in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp, ",");
        priority = atoi(strsep(&temp, ","));
        burst = atoi(strsep(&temp, ","));

        // add the task to the scheduler's list of tasks
        add(name, priority, burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule();

    return 0;
}
