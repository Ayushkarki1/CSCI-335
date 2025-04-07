#ifndef COUNTINGSORT_HPP
#define COUNTINGSORT_HPP

#include <string>
#include <vector>

/**
  @brief Sorts a given vector of integers using counting sort algorithm and calculates quartiles.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be sorted and analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void countingSort(const std::string &header, std::vector<int> data);

#endif // COUNTINGSORT_HPP
