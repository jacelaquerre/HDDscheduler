//
// Created by jacel on 11/18/2019.
//

#ifndef ASSIGNMENT_6_HDDSIMUGRAD_NETID_H
#define ASSIGNMENT_6_HDDSIMUGRAD_NETID_H

#define NUM_TRACKS 200

typedef enum {
    SCHEDULER_FCFS,
    SCHEDULER_SSTF,
    SCHEDULER_SCAN
} SchedulerType;

typedef struct IORequestNodeStruct {
    int trackNum;
    struct IORequestNodeStruct *prev;
    struct IORequestNodeStruct *next;
} IORequestNode;

int addRequest(IORequestNode **listP, int trackNum);
int serviceNextRequest(IORequestNode **listP, int *headPosition,
                       int *headDirection, SchedulerType schedType, int *displacement);
void printRequestQueue(IORequestNode *list);

#endif //ASSIGNMENT_6_HDDSIMUGRAD_NETID_H
