// Giang Doan - gdd33 - 14279443
// Drexel University - CS361 - Fall 2021-2022
// Assignment 4
// main file

#include <iostream>
#include <vector>
#include <tuple>
#include <thread>

#include "goat.h"
#include "bridge.h"

// parse user arg and return numbers of goats on each side in a tuple
std::tuple<int, int> parseUserInput(int argv, char **argc)
{
    // args need to be exactly 2
    if (argv != 3)
    {
        std::cerr << "Wrong number of argument.\nUsage: ./bin/goats <number of goats on the west> <number of goats on the east" << std::endl;
        std::exit(1);
    }
    // return a tuple containing number of goats on each side
    return std::make_tuple(atoi(argc[1]), atoi(argc[2]));
}

int main(int argv, char **argc)
{
    // Get number of goats on each side and assign to numWest and numEast
    unsigned int numWest, numEast;
    std::tie(numWest, numEast) = parseUserInput(argv, argc);

    // initialize goatPool and the bridge
    std::thread goatPool[numEast + numWest];
    bridge *b = new bridge();

    // init goats on the west
    for (int i = 0; i < numWest; i++)
        goatPool[i] = std::thread(goat, "W", i, b);

    // init goats on the east
    for (int j = numWest; j < numWest + numEast; j++)
        goatPool[j] = std::thread(goat, "E", j - numWest, b);

    // join all the goats
    for (int k = 0; k < numWest + numEast; k++)
        goatPool[k].join();

    return 0;
}