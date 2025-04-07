/*  
    Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    myAVLtree.cpp 
*/

#include "myAVLtree.hpp" 
#include <iostream> 
#include <vector>
#include <sstream>
#include <algorithm>

// to compute the median of a sequence of integers using AVL trees
void treeMedian(const std::vector<int> *instructions) {
    AVLtree small, large; // Create instances of AVL trees to maintain small and large halves of the sequence
    std::vector<int> medians; // Vector to store computed medians

    // Iterate through the instructions vector
    for (auto it : *instructions) {
        if (it != -1) { // If the instruction is not to find the median
            // Determine which AVL tree to insert the element based on its value
            if (small.getSize() == 0 || small.getMax() > it) {
                small.insert(it); // Insert into small AVL tree if it's empty or the value is smaller than the maximum in small
            }
            else {
                large.insert(it); // Otherwise, insert into large AVL tree
            }
        }
        else { // If the instruction is to find the median
            medians.push_back(small.popMaximum()); // Pop the maximum from small AVL tree and add it to medians vector
        }

        // Balance the sizes of small and large AVL trees
        if (small.getSize() > large.getSize() + 1) { // If small AVL tree has more elements than large AVL tree by more than 1
            large.insert(small.popMaximum()); // Move one element from small to large AVL tree
        }   
        else if (large.getSize() > small.getSize()) { // If large AVL tree has more elements than small AVL tree
            small.insert(large.popMinimum()); // Move one element from large to small AVL tree
        }
    }

    // Print the computed medians
    for (auto it : medians) {
        std::cout << it << " ";
    }

    std::cout << std::endl; // Print newline after printing medians
}
