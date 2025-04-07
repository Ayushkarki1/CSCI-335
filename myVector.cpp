/*  Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    myVector.cpp 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "myVector.hpp"

//calculates medians of a sequence of numbers
void vectorMedian(const std::vector<int>* instructions) {
    const auto start_time = std::chrono::steady_clock::now(); // Record the start time of execution
    std::vector<int> numbers; //Initialize a vector to hold the numbers
    std::vector<int> medians; //Initialize a vector to hold the medians

    //Iterate through the instructions
    for(auto it = instructions->begin(); it < instructions->end(); it++) {
        if(*it == -1) { //If the instruction is -1, it indicates to calculate the median
            if(numbers.size() % 2 == 0) { //If the number of elements is even
                auto median_it = numbers.begin() + numbers.size() / 2 - 1; //Calculate the iterator to the middle element
                medians.push_back(*median_it); //Push back the median into the medians vector
                numbers.erase(median_it); //Erase the median element from the numbers vector
            }
            else {  //If the number of elements is odd
                auto median_it = numbers.begin() + numbers.size() / 2; //Calculate the iterator to the middle element
                medians.push_back(*median_it); //Push back the median into the medians vector
                numbers.erase(median_it); //Erase the median element from the numbers vector
            }
        } else { //If the instruction is not -1, it indicates to insert a number
            auto insert_pos = std::lower_bound(numbers.begin(), numbers.end(), *it); // Find the insertion position using lower_bound
            numbers.insert(insert_pos, *it); // Insert the number into the numbers vector at the calculated position
        }
    }

    // Print the calculated medians
    for(int i = 0; i < medians.size(); i++) {
        std::cout << medians[i] << " ";
    }

    // Record the end time of execution using the steady clock provided by the chrono library
    const auto end_time = std::chrono::steady_clock::now(); 
    // Calculate the execution time by subtracting the start time from the end time 
    int execution_time = std::chrono::duration <double, std::micro> (end_time - start_time).count();
    // Print the calculated execution time 
    std::cout << "\nExecution Time: " << execution_time << " microseconds." << std::endl;
}

