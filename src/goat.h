// Giang Doan - gdd33 - 14279443
// Drexel University - CS361 - Fall 2021-2022
// Assignment 4
// header file for goat.cpp

#include <string>
#include <thread>
#include <iostream>

#include "bridge.h"

// the goat thread function for starting a goat
void goat(std::string side, unsigned int index, bridge* b);

// print str each line at a time
void printString(std::string str);

// return a random wait time between a and b seconds (including a and b)
std::chrono::seconds waitTime(unsigned int a, unsigned int b);

// return a random number between and includes a and b (b needs to be > a)
int randrange(unsigned int a, unsigned int b);