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

    if (*listP == NULL)
        return(-1);

    if (schedType == SCHEDULER_FCFS) {
        prevNode = NULL;
        currNode = *listP;
        // now find last node in list
        while (currNode->next != NULL) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        *displacement = abs(currNode->trackNum - *headPosition);
        if ((currNode->trackNum - *headPosition) >= 1){
            *headDirection = 1;
        }
        else {
            *headDirection = -1;
        }
        *headPosition = currNode->trackNum;

        if (prevNode == NULL) {
            // there's only one node in the list
            *listP = NULL;
        } else {
            prevNode->next = NULL;
        }
        //free(currNode);

        return(currNode->trackNum);
    }

    if (schedType == SCHEDULER_SSTF) {
        prevNode = NULL;
        currNode = *listP;
        nextNode = currNode;

        while (currNode->next != NULL) {
            prevNode = currNode;
            if(abs(prevNode->trackNum - *headPosition) < abs(nextNode->trackNum - *headPosition))
                nextNode = prevNode;
            currNode = currNode->next;
        }

        prevNode = nextNode->prev;
        currNode = nextNode;

        *displacement = abs(currNode->trackNum - *headPosition);
        if (currNode->trackNum - *headPosition >= 1){
            *headDirection = 1;
        }
        else {
            *headDirection = -1;
        }

        *listP = currNode->next;
        currNode = NULL;

        *headPosition = nextNode->trackNum;
        return(nextNode->trackNum);
    }
//    if (schedType == SCHEDULER_SCAN) {
//
//    }
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
