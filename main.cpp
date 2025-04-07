/*  Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    main.cpp 
*/
#include "myAVLtree.hpp"
#include "myHeap.hpp"
#include "myList.hpp"
#include "myVector.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int main() {
  // openfile
  std::ifstream file("testinput.txt");
  std::vector<int> numbers;
  std::string line;

  if (!file) {
    std::cerr << "Unable to open file" << std::endl;
    return 1;
  }

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string operation;
    iss >> operation;

    if (operation == "pop") {
      numbers.push_back(-1);
    } else if (operation == "insert") {
      int number;
      iss >> number;
      numbers.push_back(number);
    }
  }

  file.close();
  vectorMedian(&numbers);
  std::cout << std::endl;
  listMedian(&numbers);
  std::cout << std::endl;
  heapMedian(&numbers);
  std::cout << std::endl;
  treeMedian(&numbers);
  std::cout << std::endl;
}