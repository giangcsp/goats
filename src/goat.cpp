// Giang Doan - gdd33 - 14279443
// Drexel University - CS361 - Fall 2021-2022
// Assignment 4
// implementation for the goat thread function

#include "goat.h"

void goat(std::string side, unsigned int index, bridge *b)
{
    // init name of the goat and current side the goat is in currently
    std::string name = side + std::to_string(index);
    std::string currentSide = side;

    // main loop for the goat
    while (true)
    {
        // Foraging at home
        printString("Goat " + name + " is foraging on the " + ((currentSide == "W") ? "west" : "east") + " side");
        std::this_thread::sleep_for(waitTime(0, 4));

        // cross the bridge to other side
        // I did not comment all of the watiing stuff since they are the same
        if (currentSide == "W")
        {
            b->waitWest();
            currentSide = "W";
            // print the initial message and wait
            printString("Goat " + name + " is crossing the bridge from the east side to the west side.");
            std::this_thread::sleep_for(waitTime(0, 2));
            // done waiting, print the finish message
            printString("Goat " + name + " got to the " + ((currentSide == "W") ? "west" : "east") + " side after starting on the " + ((currentSide == "W") ? "east" : "west") + " side.");
            b->signalWest();
        }
        else
        {
            b->waitEast();
            currentSide = "E";
            printString("Goat " + name + " is crossing the bridge from the west side to the east side.");
            printString("Goat " + name + " got to the " + ((currentSide == "W") ? "west" : "east") + " side after starting on the " + ((currentSide == "W") ? "east" : "west") + " side.");
            b->signalEast();
        }

        // Foraging at other side and sleep for random time
        printString("Goat " + name + " is foraging on the " + ((currentSide == "W") ? "west" : "east") + " side");
        std::this_thread::sleep_for(waitTime(0, 4));

        // cross the bridge back home
        // this is the same as crossing the bridge to the other side
        if (currentSide == "W")
        {
            b->waitWest();
            currentSide = "W";
            printString("Goat " + name + " is crossing the bridge from the east side to the west side.");
            std::this_thread::sleep_for(waitTime(0, 2));
            printString("Goat " + name + " got to the " + ((currentSide == "W") ? "west" : "east") + " side after starting on the " + ((currentSide == "W") ? "east" : "west") + " side.");
            b->signalWest();
        }
        else
        {
            b->waitEast();
            currentSide = "E";
            printString("Goat " + name + " is crossing the bridge from the west side to the east side.");
            printString("Goat " + name + " got to the " + ((currentSide == "W") ? "west" : "east") + " side after starting on the " + ((currentSide == "W") ? "east" : "west") + " side.");
            b->signalEast();
        }

        // take a nap
        printString("Goat " + name + " is taking a nap on the " + ((currentSide == "W") ? "west" : "east") + " side.");
        std::this_thread::sleep_for(waitTime(0, 2));
    }
}
// init the mutex for io
std::mutex ioLock;

void printString(std::string str)
{
    // lock the mutex and print
    std::lock_guard lk(ioLock);
    std::cout << str << std::endl;
    return;
}

std::chrono::seconds waitTime(unsigned int a, unsigned int b)
{
    return std::chrono::seconds(randrange(a, b));
}

int randrange(unsigned int a, unsigned int b)
{
    // calculate difference between b and a
    unsigned int numNum = b - a + 1;

    // return a random number between a and b (including a and b)
    return std::rand() % numNum + a;
}