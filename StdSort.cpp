/* Ayush Karki
CSCI 33500 Project 3
Spring 2024
StdSort.cpp */
#include <iostream>
#include <algorithm>
#include "StdSort.hpp"
/**
  @brief Sorts a given vector of integers in ascending order and calculates quartiles.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be sorted and analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void stdSort(const std::string &header, std::vector<int> data) {
    // const auto time_begin = std::chrono::steady_clock::now(); begin timer
    std::sort(data.begin(), data.end());
    // Calculate quartiles and print the five-number summary
    int n = data.size(); // Total number of elements in the sorted data vector
    int p25 = data[n / 4]; // First quartile (25th percentile)
    int p50 = data[n / 2]; // Second quartile (50th percentile, median)
    int p75 = data[3 * n / 4]; // Third quartile (75th percentile)
    // Print header and summary
    std::cout << header << std::endl; // Printing header string
    std::cout << "Min: " << data.front() << std::endl; // Printing minimum value (first element)
    std::cout << "P25: " << p25 << std::endl; // Printing first quartile 
    std::cout << "P50: " << p50 << std::endl; // Printing median (second quartile)
    std::cout << "P75: " << p75 << std::endl; // Printing third quartile
    std::cout << "Max: " << data.back() << std::endl; // Printing maximum value (last element)
    /* End timer
    const auto time_end = std::chrono::steady_clock::now();
    int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();
    std::cout << "\n\nTime quickSelect2: " << duration_ << " miliseconds\n" << std::endl;*/
}
