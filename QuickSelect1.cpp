/* Ayush Karki
CSCI 33500 Project 3
Spring 2024
QuickSelect1.cpp */
#include <iostream>
#include <vector>
#include "QuickSelect1.hpp"
#include <algorithm>
using namespace std;
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
 * Function to find the kth smallest element using quick select algorithm.
 * It partitions the array around a pivot element and recursively
 * sorts the left or right partition based on the pivot position until
 * the kth element is found.
 *
 * @param arr The input array to find the kth smallest element from.
 * @param left The starting index of the subarray.
 * @param right The ending index of the subarray.
 * @param k The index of the element to find (kth smallest).
 * @return The kth smallest element in the array.
 */


/**
  @brief function for the quick select algorithm to find the kth smallest element in an array.
  @param array A reference to the vector of integers to be searched.
  @param min The minimum index of the subarray to be searched.
  @param max The maximum index of the subarray to be searched.
  @param k The index of the desired smallest element.
  @return The value of the kth smallest element.
*/
int quickSelect(std::vector<int>& array, int min, int max, int k) {
    if (min <= max) {
        int piv = partition(array, min, max);// Partition the array

        if (piv == k) {
            return array[piv];// Return the value of the kth smallest element
        } else if (piv < k) {
            return quickSelect(array, piv + 1, max, k);// Search in the right subarray
        } else {
            return quickSelect(array, min, piv - 1, k);// Search in the left subarray
        }}
    return -1;// Return an error condition if the kth smallest element is not found
}

/**
  @brief Uses the quick select algorithm to find quartiles and prints a summary of the data.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void quickSelect1(const std::string &header, std::vector<int> data) {
    // const auto time_begin = std::chrono::steady_clock::now(); begin timer
    int n = data.size();
    int k = n / 2;// Find the index of the median element
    int med = quickSelect(data, 0, n - 1, k);// Find the median value using quick select
    // Find quartiles using quick select
    int percentile25 = quickSelect(data, 0, n - 1, n / 4);
    int percentile75 = quickSelect(data, 0, n - 1, 3 * n / 4);
    // Print header and summary
    std::cout << header << std::endl;
    std::cout << "Min: " << *min_element(data.begin(), data.end()) << std::endl;// Find minimum element
    std::cout << "P25: " << percentile25 << std::endl;// 25th percentile
    std::cout << "P50: " << med << std::endl;// Median
    std::cout << "P75: " << percentile75 << std::endl;// 75th percentile
    std::cout << "Max: " << *max_element(data.begin(), data.end()) << std::endl;// Find maximum element
    /* End timer
    const auto time_end = std::chrono::steady_clock::now();
    int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();
    std::cout << "\n\nTime quickSelect2: " << duration_ << " miliseconds\n" << std::endl;*/
}