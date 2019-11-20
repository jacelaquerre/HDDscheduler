// Jace Laquerre & Matt Zahar
// CS201 Assignment #6
// Some code taken from instructor Gitlab

#include <stdio.h>
#include <stdlib.h>
#include "HDDsimugrad.netid.h"

int main() {
    printf("Hello World!");
    return 0;
}

int addRequest(IORequestNode **listP, int trackNum) {
    IORequestNode *currNode, *prevNode, *newNode;
    newNode = (IORequestNode *) malloc(sizeof(IORequestNode));
    newNode->trackNum = trackNum;
    newNode->next = *listP;
    newNode->prev = NULL;
    if (*listP != NULL) {
        (*listP)->prev = newNode;
    }
    *listP = newNode;
    return(0);
}

// will select and delete only one node at a time
int serviceNextRequest(IORequestNode **listP, int *headPosition, int *headDirection,
                       SchedulerType schedType, int *displacement) {

    IORequestNode *currNode, *prevNode, *nextNode;
    int rtnval;
    if (*listP == NULL) {
        return -1;
    }
    rtnval = 1;
    prevNode = NULL;
    currNode = *listP;
    while (currNode != NULL) {
        nextNode = currNode->next;
        if (schedType == SCHEDULER_FCFS) {

        }
        if (schedType == SCHEDULER_SSTF) {

        }
        if (schedType == SCHEDULER_SCAN) {

        }
    }

    // Return next track to be serviced
}

void printRequestQueue(IORequestNode *list) {
    IORequestNode *node;
    if (list == NULL)
        printf("[empty]\n");
    else {
        printf("[ ");
        node = list;
        while (node != NULL) {
            printf("%d ", node->trackNum);
            node = node->next;
        }
        printf("]\n");
    }
}
