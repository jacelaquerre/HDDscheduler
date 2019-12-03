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

    requests[0] = 50;
    requests[1] = 57;
    requests[2] = 47;
    requests[3] = 39;
    requests[4] = 65;
    requests[5] = 10;
    requests[6] = 150;
    requests[7] = 15;
    requests[8] = 160;
    requests[9] = 1;
    numRequests = 10;

    headPosition = 48;
    headDirection = 1;

    requestQueue = NULL;

    for (i=0; i<numRequests; ++i)
        addRequest(&requestQueue, requests[i]);

    printRequestQueue(requestQueue);
    printf("head position = %d; head direction = %d\n",
           headPosition, headDirection);

    if (schedType == SCHEDULER_SSTF)
        printf("SSTF: order of these should be 47 - 50 - 57 - 65 - 39 - 10 - 1 - 150 - 160\n");
    else if (schedType == SCHEDULER_FCFS)
        printf("FCFS: order of these should be 50 - 57 - 47 - 39 - 65 - 10 - 150 - 15 - 160 - 1\n");
    else if (schedType == SCHEDULER_SCAN)
        printf("SCAN: order of these should be 50 - 57 - 65 - 150 - 160 - 47 - 39 - 15 - 10 - 1\n");

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
        printf("total displacement should be 242; value is %d\n", displacementTotal);
    else if (schedType == SCHEDULER_FCFS)
        printf("total displacement should be 687; value is %d\n", displacementTotal);
    else if (schedType == SCHEDULER_SCAN)
        printf("total displacement should be 271; value is %d\n", displacementTotal);

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
        smallNode = currNode;

        while (currNode != NULL) {
            prevNode = currNode;
            if(abs(prevNode->trackNum - *headPosition) <= abs(smallNode->trackNum - *headPosition)) {
                smallNode = prevNode;
            }
            currNode = currNode->next;
        }
        prevNode = smallNode->prev;
        currNode = smallNode;
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

        if (*headDirection == 1) {

        }
        else if (*headDirection == -1) {

        }
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
