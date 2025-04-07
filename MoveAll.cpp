/* 
Ayush Karki 
Project 1 - Move Semantics and Iterators
CSCI 33500 Spring 2024
*/

#include "MoveAll.hpp"
#include "Book.hpp"
using namespace std;

// Moves all Books in "source" with the specified keyword to "dest".
// A Book is moved if any of its keywords match the one specified in this function.
// Use iterator s whenever appropriate.
// Hint: you need a const iterator for a const vector, but this will be automatically handled using "auto".

void moveAll (const std::string keyword, std::vector<Book> &source, std::vector<Book> &dest){
  const auto t1_start = std::chrono::steady_clock::now();
  int books_moved=0; // counts books moved
  // DO NOT ALTER ABOVE HERE
  
  // Iterate over the source vector
     for (auto iterator = source.begin(); iterator != source.end();) {
        // Check if any of the book's keywords match the specified keyword
        bool found = false;
        for (const auto& kw : iterator->getKeywords()) {
            if (kw == keyword) {
                found = true;
                break;
            }
        }
        // If a match is found, move the book to the destination vector
        if (found) {
            dest.push_back(std::move(*iterator)); // Move the book
            iterator = source.erase(iterator); // Erase the book from the source vector
            books_moved++; // Increment the count of books moved
        } else {
            iterator++; // Move to the next book in the source vector
        }
    }
  // DO NOT ALTER BELOW HERE
  const auto t1_end = std::chrono::steady_clock::now();
  int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();
  std::cout << "Moved " << books_moved << " books in " << t1 << " microseconds." << std::endl;
}