// Jace Laquerre & Matt Zahar
// CS201 Assignment #6
// Some code taken from instructor Gitlab

#include <stdio.h>
#include <stdlib.h>
#include "HDDsimugrad.netid.h"

int addRequest(IORequestNode **listP, int trackNum) {
    IORequestNode *currNode, *prevNode, *newNode;

    newNode = (IORequestNode *) malloc(sizeof(IORequestNode));
    newNode->trackNum = trackNum;
    newNode->next = *listP;
    newNode->prev = NULL;
    if (*listP != NULL)
        (*listP)->prev = newNode;
    *listP = newNode;
    return(0);

}
// will select and delete only one node at a time
int serviceNextRequest(IORequestNode **listP, int *headPosition, int *headDirection, SchedulerType schedType, int *displacement) {
    IORequestNode *currNode, *prevNode, *nextNode;

    if (schedType == SCHEDULER_FCFS) {
        if (*listP == NULL)
            return(-1);

        prevNode = NULL;
        currNode = *listP;
        // now find last node in list
        while (currNode->next != NULL) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        *displacement = abs(currNode->trackNum - *headPosition);
        if (currNode->trackNum - *headPosition > 1){
            *headDirection = 1;
        }
        else
            *headDirection = -1;

        if (prevNode == NULL) {
            // there's only one node in the list
            free(currNode);
            *listP = NULL;

        } else {
            free(currNode);
            prevNode->next = NULL;
        }



        *headPosition = currNode->trackNum;

        return(currNode->trackNum);
    }

    if (schedType == SCHEDULER_SSTF) {

    }
    if (schedType == SCHEDULER_SCAN) {

    }
    return 0;
}
// Return next track to be serviced
void printRequestQueue(IORequestNode *list) {
    IORequestNode *node;
    if (list == NULL) {
        printf("[empty]\n");
    }
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
