/*  
    Ayush Karki
    Project 1 - Move Semantics
    Professor Tojeira
    CSCI 33500 Fall 2024
    MyTests.cpp 
*/
#include "File.hpp"
#include "Folder.hpp"
#include <cassert>

int main() {
    // Test file creation and content modification
    File file1("TestFile.txt", "Hello World");
    assert(file1.getName() == "TestFile.txt");
    assert(file1.getContents() == "Hello World");
    // Test file copy
    File file2 = file1;
    assert(file2.getName() == "TestFile.txt");
    // Test folder creation and adding a file
    Folder folder1("TestFolder");
    folder1.addFile(std::move(file1));
    // Test file removal
    assert(folder1.removeFile("TestFile.txt"));
    return 0;
}
