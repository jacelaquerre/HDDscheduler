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
    IORequestNode *currNode, *prevNode, *nextNode, *smallNode;

    if (*listP == NULL) {
        return (-1);
    }
////////////////////////////////////////////////////
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
////////////////////////////////////////////////////
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
////////////////////////////////////////////////////
    if (schedType == SCHEDULER_SCAN) {
        prevNode = NULL;
        smallNode = NULL;
        currNode = *listP;
        smallNode = currNode;
        int minDist = 100000;

        if (*headDirection == 1) {
            while (currNode != NULL) {
                prevNode = currNode;
                if (prevNode->trackNum >= *headPosition) {
                    //printf("check tn  %d\n", prevNode->trackNum); // last is 65
                    //printf("check headpos  %d\n", *headPosition); // last is 65
//                    if (abs(prevNode->trackNum - *headPosition) < abs(smallNode->trackNum - *headPosition) ) { //changed
                    if (abs(prevNode->trackNum - *headPosition) < minDist ) { //changed
                        minDist = abs(prevNode->trackNum - *headPosition);
                        smallNode = prevNode;
                        //printf("small node tn %d\n", smallNode->trackNum); // last is 65
                    }
                }
                currNode = currNode->next;
            }

            //Flips the head direction
            if (smallNode->trackNum < *headPosition) {
                *headDirection = 1;
                smallNode = prevNode;
                if (abs(prevNode->trackNum - *headPosition) < minDist) {
                    smallNode = prevNode;
                }
            }


            prevNode = smallNode->prev;
            currNode = smallNode;
            nextNode = currNode->next;

            *displacement = abs(currNode->trackNum - *headPosition);
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
        }
        else if (*headDirection == -1) {
            while (currNode != NULL) {
                prevNode = currNode;
                if (prevNode->trackNum <= *headPosition) {
                    if (abs(prevNode->trackNum - *headPosition) < minDist) {
                        minDist = abs(prevNode->trackNum - *headPosition);
                        smallNode = prevNode;
                    }
                }
                currNode = currNode->next;
            }

            //Flips the head direction
            if (smallNode->trackNum > *headPosition) {
                *headDirection = 1;
                smallNode = prevNode;
                if (abs(prevNode->trackNum - *headPosition) > minDist) {
                    smallNode = prevNode;
                }
            }

            prevNode = smallNode->prev;
            currNode = smallNode;
            nextNode = currNode->next;

            *displacement = abs(currNode->trackNum - *headPosition);
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
        }
        return(currNode->trackNum);
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
