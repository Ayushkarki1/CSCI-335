#ifndef STDSORT_HPP
#define STDSORT_HPP

#include <string>
#include <vector>

/**
  @brief Sorts a given vector of integers in ascending order and calculates quartiles.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be sorted and analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void stdSort(const std::string &header, std::vector<int> data);

#endif // STDSORT_HPP
