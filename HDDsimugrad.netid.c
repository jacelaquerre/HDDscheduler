// Jace Laquerre & Matt Zahar
// CS201 Assignment #6
// Some code taken from instructor Gitlab

#include <stdio.h>
#include <stdlib.h>
#include "HDDsimugrad.netid.h"

int main() {
    IORequestNode *requestQueue;
    SchedulerType schedType = SCHEDULER_SSTF;
    int i, trackNum, headPosition, headDirection, displacement;
    int displacementTotal;
    int requests[200];
    int numRequests;

    requests[0] = 5;
    requests[1] = 3;
    requests[2] = 7;
    requests[3] = 2;
    numRequests = 4;

    requestQueue = NULL;

    headPosition = 0;
    headDirection = 1;

    for (i=0; i<numRequests; ++i)
        addRequest(&requestQueue, requests[i]);

    printRequestQueue(requestQueue);
    printf("head position = %d; head direction = %d\n",
           headPosition, headDirection);

    if (schedType == SCHEDULER_SSTF)
        printf("SSTF: order of these should be 2 - 3 - 5 - 7\n");
    else if (schedType == SCHEDULER_FCFS)
        printf("FCFS: order of these should be 5 - 3 - 7 - 2\n");
    else if (schedType == SCHEDULER_SCAN)
        printf("SCAN: order of these should be 2 - 3 - 5 - 7\n");

    displacementTotal = 0;

    trackNum = serviceNextRequest(&requestQueue, &headPosition,
                                  &headDirection, schedType, &displacement);
    while (trackNum >= 0) {
        displacementTotal = displacementTotal + displacement;
        printf("next request: %d; displacement = %d; pos = %d  dir = %d\n",
               trackNum, displacement, headPosition, headDirection);
        trackNum = serviceNextRequest(&requestQueue, &headPosition,
                                      &headDirection, schedType, &displacement);
    }

    if (schedType == SCHEDULER_SSTF)
        printf("total displacement should be 7; value is %d\n", displacementTotal);
    else if (schedType == SCHEDULER_FCFS)
        printf("total displacement should be 16; value is %d\n", displacementTotal);
    else if (schedType == SCHEDULER_SCAN)
        printf("total displacement should be 7; value is %d\n", displacementTotal);

    return(0);

}
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
    IORequestNode *currNode, *prevNode, *nextNode, *smallNode;

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
        //int headNode = 0;
        prevNode = NULL;
        nextNode = NULL;
        currNode = *listP;
        nextNode = currNode;

        while (currNode != NULL) {
            prevNode = currNode;
            if(abs(prevNode->trackNum - *headPosition) <= abs(nextNode->trackNum - *headPosition)) {
                nextNode = prevNode;
            }
            currNode = currNode->next;
        }
        prevNode = nextNode->prev;
        currNode = nextNode;
        nextNode = currNode->next;

        *displacement = abs(currNode->trackNum - *headPosition);
        if (currNode->trackNum - *headPosition >= 1) {
            *headDirection = 1;

        }
        else {
            *headDirection = -1;
        }
        *headPosition = currNode->trackNum;
        if (prevNode == NULL && nextNode == NULL){
            *listP = NULL;
        }else if (prevNode == NULL){
            *listP = currNode->next;
            nextNode->prev = NULL;
        }else if(nextNode == NULL){
            *listP = currNode->prev;
            prevNode->next = NULL;
        }else{
            prevNode->next = currNode->next;
            currNode->next->prev = prevNode;

        }

        return(currNode->trackNum);
    }
    if (schedType == SCHEDULER_SCAN) {
        prevNode = NULL;
        smallNode = NULL;
        currNode = *listP;
        while (currNode->next != NULL) {
            nextNode = currNode->next;
            if (*headDirection == 1) {
                if (currNode->trackNum > *headPosition) {
                    if ((currNode->trackNum - *headPosition) < (nextNode->trackNum - *headPosition)) {
                        if (currNode->trackNum < smallNode->trackNum || (smallNode == NULL)) {
                            smallNode = currNode;
                        }
                        currNode = nextNode;
                    }
                    else {
                        if (nextNode->trackNum < smallNode->trackNum || smallNode == NULL) {
                            smallNode = nextNode;
                        }
                        currNode = nextNode;
                    }
                }
            }
            else if (*headDirection == -1) {
                if(nextNode->trackNum < *headPosition) {
                    return(nextNode->trackNum);
                }
            }
        }
        *displacement = abs(currNode->trackNum - *headPosition);
        if (prevNode == NULL) {
            // there's only one node in the list
            *listP = NULL;
        }
        else {
            prevNode->next = NULL;
        }
        return (smallNode->trackNum);
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
