/*  Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    myList.cpp 
*/

#include <iostream>
#include <list>
#include <algorithm>

#include "myList.hpp"

//calculates medians of a sequence of numbers
void listMedian(const std::vector<int>* instructions) {
    std::list<int> container; //Initialize a list to hold the numbers
    std::vector<int> medians; //Initialize a vector to hold the medians

    // Iterate through the instructions
    for (auto it = instructions->begin(); it != instructions->end(); ++it) {
        if (container.empty() && *it != -1) { // If container is empty and instruction is not -1
            container.push_back(*it); // Add the number to the container
        } else if (*it == -1) { //If the instruction is -1
            if (container.empty()) { //Check if container is empty
                std::cerr << "Error: Container is empty!" << std::endl; // Print an error message
                continue; //Continue to the next instruction
            }
            auto copy = container.begin(); //Create a copy iterator to manipulate
            std::advance(copy, (container.size() - 1) / 2); // Move the copy iterator to the middle element
            medians.push_back(*copy); // Push back the median into the medians vector
            container.erase(copy); // Erase the median element from the container
        } else { // If the instruction is not -1
            auto low = std::lower_bound(container.begin(), container.end(), *it); // Find the insertion position using lower_bound
            container.insert(low, *it); // Insert the number into the container at the calculated position
        }}
    // Print medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
