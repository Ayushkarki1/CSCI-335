/* Ayush Karki
CSCI 33500 Project 3
Spring 2024
QuickSelect2.cpp */
#include <iostream>
#include <vector>
#include <cstdlib> 

/**
  @brief Partitions a subarray of integers around a pivot element for use in the quick select algorithm.
  @param array A reference to the vector of integers to be partitioned.
  @param min The minimum index of the subarray to be partitioned.
  @param max The maximum index of the subarray to be partitioned.
  @return The index of the pivot element after partitioning.
*/
int partition(std::vector<int>& array, int min, int max) {
    int pivotIndex = min + rand() % (max - min + 1);// Choose a random pivot index
    int pivot = array[pivotIndex];// Select the pivot element
    std::swap(array[pivotIndex], array[max]);// Move the pivot to the end
    int i = min - 1;
    for (int j = min; j < max; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }}
    std::swap(array[i + 1], array[max]);// Move the pivot to its final sorted position
    return i + 1;// Return the index of the pivot
}

/**
  @brief insertion sort on a subarray of integers.
  @param array A reference to the vector of integers to be sorted.
  @param left The minimum index of the subarray to be sorted.
  @param right The maximum index of the subarray to be sorted.
  @return None
*/
void insertionSort(std::vector<int>& array, int left, int right) {
    for (int p = left + 1; p <= right; ++p) {
        int tmp = std::move(array[p]);
        int j;
        for (j = p; j > left && tmp < array[j - 1]; --j)
            array[j] = std::move(array[j - 1]);
        array[j] = std::move(tmp);
    }
}

/**
  @brief function to perform quick select on a subarray of integers.
  @param array A reference to the vector of integers to be searched.
  @param left The minimum index of the subarray to be searched.
  @param right The maximum index of the subarray to be searched.
  @param keys A reference to a vector containing the positions of interest.
  @return None
*/
void quickSelect(std::vector<int>& array, int left, int right, std::vector<int>& keys) {
    // Calculate the size of the subarray
    int n = right - left + 1;
    // Check if quick select should be used or if the subarray is small enough for insertion sort
    if (n > 20) {
        // Perform quick select if the subarray is large enough
        if (left <= right) {
            // Partition the subarray and get the pivot index
            int piv = partition(array, left, right);
            // Check if any of the keys fall within the current range
            std::vector<int> keys_in_range;
            for (int key : keys) {
                if (key >= left && key <= right) {
                    keys_in_range.push_back(key);
                }}
            // Recurse on both sides if necessary
            if (!keys_in_range.empty()) {
                std::vector<int> keys_left, keys_right;
                for (int key : keys_in_range) {
                    if (key < piv) {
                        keys_left.push_back(key);
                    } else if (key > piv) {
                        keys_right.push_back(key);
                    }}
                // Recurse on the left subarray
                if (!keys_left.empty()) {
                    quickSelect(array, left, piv - 1, keys_left);
                }
                // Recurse on the right subarray 
                if (!keys_right.empty()) {
                    quickSelect(array, piv + 1, right, keys_right);
                }} else { // Otherwise, recurse on the side containing the median
                if (!keys.empty() && keys.back() < piv) {
                    quickSelect(array, left, piv - 1, keys);
                } else {
                    quickSelect(array, piv + 1, right, keys);
                }}}} else {
        // Use insertion sort if the subarray is small enough
        insertionSort(array, left, right);
    }}


/**
  @brief Uses the quick select algorithm to find quartiles and prints a summary of the data.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void quickSelect2(const std::string &header, std::vector<int> data) {
    // Get the size of the data vector
    int n = data.size();
    // Defining a vector 'keys' containing the positions of interest: 0 (start), n/4 - 1 (25th percentile), n/2 (50th percentile or median), n*3/4 - 1 (75th percentile), and n-1 (end).
    std::vector<int> keys = {0, n / 4 - 1, n / 2, n * 3 / 4 - 1, n - 1}; // Positions of interest
    quickSelect(data, 0, n - 1, keys);
    // Print header and summary
    std::cout << header << std::endl; // Print the header
    // Print minimum value
    std::cout << "Min: " << data[keys[0]] << std::endl;
    // Print 25th percentile value
    std::cout << "P25: " << data[keys[1]] << std::endl;
    // Print median (50th percentile) value
    std::cout << "P50: " << data[keys[2]] << std::endl;
    // Print 75th percentile value
    std::cout << "P75: " << data[keys[3]] << std::endl;
    // Print maximum value
    std::cout << "Max: " << data[keys[4]] << std::endl;
    /* End timer
    const auto time_end = std::chrono::steady_clock::now();
    int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();
    std::cout << "\n\nTime quickSelect2: " << duration_ << " miliseconds\n" << std::endl;*/
}