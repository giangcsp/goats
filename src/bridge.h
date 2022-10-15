// Giang Doan - gdd33 - 14279443
// Drexel University - CS361 - Fall 2021-2022
// Assignment 4
// header file for bridge.cpp

#include <mutex>
#include <condition_variable>

#ifndef __BRIDGE_H__
#define __BRIDGE_H__

// the semaphore for this program, only permit goats from one side to move accross the bridge at a time
class bridge
{
    private:
        // main lock for the bridge (one goat can perform action on the bridge at a time)
        mutable std::mutex bridgeLock;
        // conditional variable for the bridge
        std::condition_variable bridgeCond;
        // east and west counters for number of goats currently crossing the bridge
        unsigned int eastCounter;
        unsigned int westCounter;
        // east and west number of goats currently queuing to cross the bridge
        unsigned int eastQueue;
        unsigned int westQueue;
        // current side crossing the bridge
        std::string currentSide;
    public:
        // constructor
        bridge();
        // signal functions for each side
        void signalEast();
        void signalWest();
        // wait functions for each side
        void waitEast();
        void waitWest();
};

#endif