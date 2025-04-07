/*
    Ayush Karki
    Project 2 - Trees and Hashes
    Professor Tojeira
    CSCI 33500 Fall 2024
    Solution.cpp 
*/

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

#ifndef USE_VECTOR
#define USE_VECTOR
#endif

#include "FileTrie.hpp"
#include "File.hpp"
#include "FileAVL.hpp"
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>


/**
 * @brief Recursively deletes all nodes in the FileTrie to prevent memory leaks.
 * 
 * @param node Pointer to the current FileTrieNode being deleted.
 * 
 * This function traverses the trie structure, deleting each node starting from 
 * the children and working its way up to the root. This is called as part of the
 * destructor for the FileTrie class.
 */// Inline helper function to recursively delete all nodes in the trie

inline void deleteTrieNodes(FileTrieNode* node) {
    if (!node) return; // Base case: If the node is null, return (no action needed)

    // Recursively delete all children of the current node
    for (auto& pair : node->next) {
        deleteTrieNodes(pair.second); // Recursive call to delete each child node
    }

    // Delete the current node after all its children have been deleted
    delete node;
}

/**
 * @brief Destructor for the FileTrie class.
 * 
 * Cleans up all dynamically allocated memory in the trie by calling the helper 
 * function deleteTrieNodes starting from the root node (head).
 */// Implementation for FileTrie destructor

FileTrie::~FileTrie() {
    deleteTrieNodes(head); /// Start recursive cleanup from the root (head) of the trie
}


/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */// Query function for FileAVL class

/**
 * @brief Recursively queries the FileAVL to find all files within a size range.
 * 
 * @param node Pointer to the current node being processed in the AVL tree.
 * @param min The minimum size of files to include in the result.
 * @param max The maximum size of files to include in the result.
 * @param result The vector to store the files that match the size range.
 * 
 * This helper function recursively traverses the AVL tree and collects all files 
 * whose size is within the specified range. The function performs in-order traversal 
 * to maintain the sorted order of the files.
 */
void queryHelper(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    if (!node) return; // Base case: If the node is null, do nothing

    size_t fileSize = node->files_.front()->getSize(); // Get the size of the first file in the node

    // If the file size is greater than or equal to the min value, search in the left subtree
    if (fileSize >= min) queryHelper(node->left_, min, max, result);

    // If the file size is within the range [min, max], add files from this node to the result
    if (fileSize >= min && fileSize <= max) 
        result.insert(result.end(), node->files_.begin(), node->files_.end());

    // If the file size is less than or equal to the max value, search in the right subtree
    if (fileSize <= max) queryHelper(node->right_, min, max, result);
}

/**
 * @brief Queries the FileAVL for files whose sizes fall within the given range [min, max].
 * 
 * @param min The minimum size of files to include in the result.
 * @param max The maximum size of files to include in the result.
 * @return std::vector<File*> A vector containing pointers to the files within the range.
 * 
 * This function is the entry point for querying the FileAVL tree. It ensures that the 
 * range is valid (min <= max), then it calls the helper function to perform the traversal 
 * and gather the matching files.
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    if (min > max) std::swap(min, max); // Ensure the range is valid by swapping if necessary

    std::vector<File*> result; // Vector to hold the files that match the size range

    // Call the recursive helper function to start the query from the root
    queryHelper(root_, min, max, result);

    return result; // Return the result containing all files within the specified size range
}

/**
 * @brief Adds a file to the FileTrie based on its name.
 * 
 * @param file A pointer to the File object to be added.
 * 
 * This function inserts the file into the trie by creating new nodes as needed for 
 * each character in the file name. The function ensures that the file is added to 
 * both the root node's matching set and the sets of all nodes along the file name path.
 */// Adds a file to the FileTrie

void FileTrie::addFile(File* file) {
    if (file == nullptr) {
        return; // Ignore null input to avoid errors
    }

    const std::string& files = file->getName();  // Retrieve the file's name
    FileTrieNode* node = head; // Start traversal from the root node

    // Iterate through each character in the file name
    for (const char& ch : files) {
        char lowerCharacter = std::tolower((ch)); // Convert to lowercase

        // Check if the child node for this character exists; if not, create it
        if (!node->next.count(lowerCharacter)) {
            node->next[lowerCharacter] = new FileTrieNode(lowerCharacter);
        }

        // Move to the child node
        node = node->next[lowerCharacter];

        // Insert the file pointer into the matching set for the current node
        node->matching.insert(file);
    }

    // Ensure the root node's matching set contains the file
    head->matching.insert(file);
}


/**
 * @brief Retrieves all files whose names start with a given prefix.
 * 
 * @param prefix A string representing the prefix to search for.
 * @return std::unordered_set<File*> A set of pointers to all files with the given prefix.
 * 
 * This function traverses the trie following the prefix. If the prefix exists in the trie, 
 * it collects all files from the subtree rooted at the node corresponding to the last 
 * character of the prefix.
 */// Retrieves all files whose names start with a given prefix

std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::unordered_set<File*> result; // Store all matching files

    FileTrieNode* current = head; // Start traversal at the root node

    // Traverse the trie following the given prefix
    for (char c : prefix) {
        // Convert the current character 
        char lowerCharacter = std::tolower(c);

        // If the child node does not exist, return an empty set
        if (current->next.find(lowerCharacter) == current->next.end()) {
            return result;
        }

        // Move to the child node corresponding to the current character
        current = current->next[lowerCharacter];
    }

        // Collect files from the subtree rooted at the node corresponding to the prefix
    std::vector<FileTrieNode*> nodestovisit = {current}; // Stack for traversal

    while (!nodestovisit.empty()) {
        // Get the top node from the stack
        FileTrieNode* node = nodestovisit.back();
        nodestovisit.pop_back(); // Remove the processed node from the stack

        // Add all files in the current node's matching set to the result
        result.insert(node->matching.begin(), node->matching.end());

        // Push all children of the current node onto the stack for further traversal
        for (const auto& pair : node->next) {
            nodestovisit.push_back(pair.second);
        }
    }

    return result; // Return all matching files
}