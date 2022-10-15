// Giang Doan - gdd33 - 14279443
// Drexel University - CS361 - Fall 2021-2022
// Assignment 4
// implementation for the bridge semaphore

#include "bridge.h"
#include <iostream>

// constructor for bridge, init all counters to 0 and side to "E"
// We are favoring East side here since is there an easier way to do this ? :/
bridge::bridge()
{
    std::scoped_lock<std::mutex> lock(bridgeLock);

    eastCounter = 0;
    westCounter = 0;
    eastQueue = 0;
    westQueue = 0;
    currentSide = "E";
}

// signal function for the East side
// should flip the currentSide to another side if there are goats waiting on the other side (goats are nice)
// Although the first goat who crossed bridge would flip the sign for other goats to wait in the queue
//      I can't stop other goats from joining the previous goats on the bridge while the first goat has not reached the other side
void bridge::signalEast()
{
    // lock the bridgeLock and decrease the counter for goats currently crossing the bridge
    std::lock_guard<std::mutex> lock(bridgeLock);
    eastCounter -= 1;

    // if there are goats on the other side, stop the other goats from this side from entering the bridge
    if (westQueue > 0)
        currentSide = "W";

    bridgeCond.notify_all();
}

// signal function for the West side
// same stuff, nothing different
void bridge::signalWest()
{
    std::lock_guard<std::mutex> lock(bridgeLock);
    westCounter -= 1;

    if (eastQueue > 0)
        currentSide = "E";

    bridgeCond.notify_all();
}

// wait east function for the bridge
// first add the goat to the queue (outside of the bridge) then remove it from that queue and move it to currently crossing bridge queue
void bridge::waitEast()
{
    // lock the bridge lock and put the goat in waiting queue (outside of the bridge)
    std::unique_lock<std::mutex> lock(bridgeLock);
    eastQueue += 1;

    // wait till a goat from the other side flip the direction
    bridgeCond.wait(lock, [this]
                    { return currentSide == "E" && westCounter == 0; });

    // remove the goat from waiting queue, add it to the currently crossing bridge queue
    eastCounter += 1;
    eastQueue -= 1;

    // unlock the lock and return so other goats can join the queue
    lock.unlock();
    return;
}

// wait west function for the bridge
// same thing as waitEast
void bridge::waitWest()
{
    std::unique_lock<std::mutex> lock(bridgeLock);
    westQueue += 1;

    bridgeCond.wait(lock, [this]
                    { return currentSide == "W" && eastCounter == 0; });

    westCounter += 1;
    westQueue -= 1;

    lock.unlock();
    return;
}