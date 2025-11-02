#include "process.h"
#include <stdio.h>

enum QueueTypes {
    ROUNDROBIN, //priority 1
    STCF,       //priority 2
    FIFO,       //priority 3
    SJF         //priority 4
}

scheduleMain(struct process **procArray, int procArraySize, int maxTimesteps) {

    //array to keep track of empty/non-empty queues
    int emptyQueues[] = {
        0, //RoundRobin
        0, //STCF
        0, //FIFO
        0  //SJF
    };


    int t = 0; //central time counter
    while (t < maxTimesteps) {

        //simulate some queueing & scheduling

        //iterate through procArray to find newly arriving processes

        //add new processes to appropriate queue

        //

        t++; //increment time

    }


}