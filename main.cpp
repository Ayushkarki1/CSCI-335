#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "StdSort.hpp"
#include "QuickSelect1.hpp"
#include "QuickSelect2.hpp"
#include "CountingSort.hpp"

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::string head;
    std::vector<int> df;
    std::string line;
    bool ishead = true;

    while (std::getline(inputFile, line)) {
        if (ishead) {
            head = line;
            ishead = false;
        } else {
            std::istringstream iss(line);
            int value;
            while (iss >> value) {
                df.push_back(value);
            }
        }
    }

    inputFile.close();

    stdSort(head, df);
    quickSelect1(head, df);
    quickSelect2(head, df);
    countingSort(head, df);

    return 0;
}
