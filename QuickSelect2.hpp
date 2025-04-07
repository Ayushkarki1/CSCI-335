#ifndef QUICKSELECT2_HPP
#define QUICKSELECT2_HPP

#include <string>
#include <vector>

/**
  @brief Uses the quick select algorithm to find quartiles and prints a summary of the data.
  @param header A constant reference to a string representing the header to be printed before the summary.
  @param data A vector of integers containing the data to be analyzed.
  @post The input data vector remains unchanged. Quartiles are calculated based on the sorted data vector.
  @return None
*/
void quickSelect2(const std::string &header, std::vector<int> data);

#endif // QUICKSELECT2_HPP
