/* Ayush Karki
CSCI 33500 Project 3
Spring 2024
CountingSort.cpp */
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "CountingSort.hpp"
/**
  @brief Sorts a given vector of integers using counting sort algorithm and calculates quartiles.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be sorted and analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void countingSort(const std::string &header, std::vector<int> data) {
    // const auto time_begin = std::chrono::steady_clock::now(); begin timer
    // Step 1: Count occurrences of each value in the data
    std::unordered_map<int, int> counter; // Stores the count of each distinct value
    for (int val : data) {
        if (counter.find(val) == counter.end()) { // If the value is not in the counter
            counter[val] = 1; // Initialize its count to 1
        } else {
            counter[val]++; // Otherwise, increment its count
        }}
    // Step 2: Extract unique values from the counter
    std::vector<int> value;// Stores the unique values extracted from the counter
    for (const auto &twin : counter) {
        value.push_back(twin.first); // Push each unique value into the vector
    }
    // Step 3: Sort the unique values
    std::sort(value.begin(), value.end());
    // Print the header
    std::cout << header << std::endl;
    std::cout << "Min: " << value.front() << std::endl;
    // Calculate quartiles
    int n = data.size(); // Number of elements in the original data vector
    int percentile25 = n / 4; // Index for the first quartile (25th percentile)
    int percentile50 = n / 2; // Index for the second quartile (50th percentile)
    int percentile75 = 3 * n / 4; // Index for the third quartile (75th percentile)
    int percentile25_, percentile50_, percentile75_;// Variables to store the quartile values
    int count = 0;// Counter to keep track of the cumulative count of elements
    for (int val : value) { 
        count += counter[val];// Increment the cumulative count by the count of the current value
        // Update quartiles when the cumulative count exceeds the respective percentiles
        if (count >= percentile25 && percentile25 != 0) {
            percentile25_ = val;
            percentile25 = 0;
        }if (count >= percentile50 && percentile50 != 0) {
            percentile50_ = val;
            percentile50 = 0;
        }if (count >= percentile75 && percentile75 != 0) {
            percentile75_ = val;
            percentile75 = 0;
        }}
    // Find the maximum value (last value in sorted vector)
    int max = value.back();
    // Print quartiles and maximum value
    std::cout << "P25: " << percentile25_ << std::endl;
    std::cout << "P50: " << percentile50_ << std::endl;
    std::cout << "P75: " << percentile75_ << std::endl;
    std::cout << "Max: " << max << std::endl;
    // Print the number of unique values
    std::cout << "Unique: " << value.size() << std::endl;
    /* End timer
    const auto time_end = std::chrono::steady_clock::now();
    int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();
    std::cout << "\n\nTime quickSelect2: " << duration_ << " miliseconds\n" << std::endl;*/
}


