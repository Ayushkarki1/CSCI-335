/*  Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    myHeap.cpp 
*/
#include <iostream>
#include <vector>
#include <queue>

#include "myHeap.hpp"

// calculates medians of a sequence of numbers
void heapMedian(const std::vector<int>* instructions) {
    std::priority_queue<int> maxHeap; //Holds elements less than or equal to the median
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; //Holds elements greater than the median
    std::vector<int> medians;//Holds the medians

    // Iterate through the instructions
    for (auto it = instructions->begin(); it != instructions->end(); ++it) {
        if (maxHeap.empty() && *it != -1) { //If both heaps are empty and instruction is not -1
            maxHeap.push(*it); //Add the number to the max heap
        } else if (*it == -1) { //If the instruction is -1
            if (maxHeap.empty()) { //Check if maxHeap is empty
                std::cerr << "Error: Container is empty!" << std::endl; // Print an error 
                continue; //Continue to the next instruction
            } 

            medians.push_back(maxHeap.top()); //Push back the top element of maxHeap as the median
            maxHeap.pop(); //Remove the top element from maxHeap
  
            if (minHeap.size() > maxHeap.size()) { //If minHeap has more elements than maxHeap
                maxHeap.push(minHeap.top()); //Move the top element of minHeap to maxHeap
                minHeap.pop(); //Remove the top element from minHeap
            } 
        } else { //If the instruction is not -1
            if (*it < maxHeap.top()) { //If the number is less than the top element of maxHeap
                maxHeap.push(*it); //Add the number to maxHeap
                if (maxHeap.size() > minHeap.size() + 1) { //If maxHeap has more elements than minHeap
                    minHeap.push(maxHeap.top()); //Move the top element of maxHeap to minHeap
                    maxHeap.pop(); //Remove the top element from maxHeap
                }
            } else { //If the number is greater than or equal to the top element of maxHeap
                minHeap.push(*it); //Add the number to minHeap
                if (minHeap.size() > maxHeap.size()) { //If minHeap has more elements than maxHeap
                    maxHeap.push(minHeap.top()); //Move the top element of minHeap to maxHeap
                    minHeap.pop(); //Remove the top element from minHeap
                }
            }
        }
    }

    // Print medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
