/*  Ayush Karki
    Project 2 - Pop Median
    Professor Tojeira
    CSCI 33500 Spring 2024
    myAVLtree.hpp 
*/

#include <iostream>
#include <vector>

//a structure for AVL node containing object, height, and pointers to left and right children
struct AvlNode {
    int object, height;
    AvlNode *left, *right;

    // Constructor to initialize an AVL node with given object and nullptr for left and right children, height set to 1
    AvlNode(int object) : object{object}, left{nullptr}, right{nullptr}, height{1} {}
};

// to compute the median of a sequence of integers using AVL trees
void treeMedian(const std::vector<int> *instructions);
// a structure for AVL tree operations
struct AVLtree {
public:
    // Constructor to initialize an AVL tree with root set to nullptr and node_count set to 0
    AVLtree() : root{nullptr}, node_count{0} {}

    //to get the size of the AVL tree
    int getSize() {
        return node_count;
    }
    
    //to insert a node with given object into the AVL tree
    void insert(int num) {
        node_count++; // Increment the node count
        root = insertN(root, num); // Call the private insertN function to insert the node
    }

    //to remove and return the minimum object from the AVL tree
    int popMinimum() {
        if (root == nullptr) { // If the tree is empty
            return -1;
        }

        node_count--; // Decrement the node count
        AvlNode *node = root;

        // Traverse to the leftmost node to find the minimum object
        while (node->left != nullptr) {
            node = node->left;
        }
        int num = node->object; // Store the minimum object
        root = deleteNode(root, node->object); // Call the private deleteNode function to delete the node

        return num; // Return the minimum object
    }

    //to remove and return the maximum object from the AVL tree
    int popMaximum() {
        if (root == nullptr) { // If the tree is empty
            return -1;
        }

        node_count--; // Decrement the node count
        AvlNode *node = root;

        // Traverse to the rightmost node to find the maximum object
        while (node->right != nullptr) {
            node = node->right;
        }
        int num = node->object; // Store the maximum object
        root = deleteNode(root, node->object); // Call the private deleteNode function to delete the node

        return num; // Return the maximum object
    }


    //to get the maximum object from the AVL tree
    int getMax() {
        AvlNode *node = root;

        // Traverse to the rightmost node to find the maximum object
        while (node->right != nullptr) {
            node = node->right;
        }

        return node->object; // Return the maximum object
    }

    //to insert a node with given object into the AVL tree recursively
AvlNode* insertN(AvlNode* node, int object) {
    if (node == nullptr) { // If the node is nullptr, create a new node
        return new AvlNode(object);
    }

    //Insert the object based on the comparison with node's object
    if (object <= node->object) {
        node->left = insertN(node->left, object); // Recursively insert into the left subtree
    }
    else if (object > node->object) {
        node->right = insertN(node->right, object); // Recursively insert into the right subtree
    }

    //Update the height of the current node
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    //Check and balance the AVL tree
    int balance = balancefact(node);

    if (balance > 1) { // Left heavy
        if (object <= node->left->object) {
            return rightRotate(node); // Perform right rotation
        }
        else if (object > node->left->object) {
            node->left = leftRotate(node->left); // Perform left rotation on left child
            return rightRotate(node); // Perform right rotation on the current node
        }
    }
    if (balance < -1) { // Right heavy
        if (object > node->right->object) {
            return leftRotate(node); // Perform left rotation
        }
        else if (object <= node->right->object) {
            node->right = rightRotate(node->right); // Perform right rotation on right child
            return leftRotate(node); // Perform left rotation on the current node
        }
    }

    return node; // Return the updated node
}

// to delete a node with given object from the AVL tree recursively
AvlNode* deleteNode(AvlNode* node, int object) {
    if (node == nullptr) {
        return node;
    }

    // Delete the node based on the comparison with node's object
    if (object < node->object) {
        node->left = deleteNode(node->left, object); // Recursively delete from the left subtree
    }
    else if (object > node->object) {
        node->right = deleteNode(node->right, object); // Recursively delete from the right subtree
    }
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) { // If node has one or no child
            AvlNode* temp;
            if (node->left != nullptr) {
                temp = node->left;
            }
            else {
                temp = node->right;
            }

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp; // Replace node with its child
            }

            delete temp; // Delete the temporary node
        }
        else { // If node has two children
            AvlNode* temp = minimumNode(node->right); // Find the minimum node in the right subtree
            node->object = temp->object; // Replace the node's object with minimum node's object
            node->right = deleteNode(node->right, temp->object); // Delete the minimum node from right subtree
        }
    }

    if (node == nullptr) {
        return node;
    }

    // Update the height of the current node
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    // Check and balance the AVL tree
    int balance = balancefact(node);

    if (balance > 1) { // Left heavy
        if (balancefact(node->left) >= 0) {
            return rightRotate(node); // Perform right rotation
        }
        else {
            node->left = leftRotate(node->left); // Perform left rotation on left child
            return rightRotate(node); // Perform right rotation on the current node
        }
    }
    if (balance < -1) { // Right heavy
        if (balancefact(node->right) <= 0) {
            return leftRotate(node); // Perform left rotation
        }
        else {
            node->right = rightRotate(node->right); // Perform right rotation on right child
            return leftRotate(node); // Perform left rotation on the current node
        }
    }

    return node; // Return the updated node
}



private:
    AvlNode* root; // Pointer to the root node of the AVL tree
    int node_count;  // Count of nodes in the AVL tree

    // to get the height of a node
    int getHeight(AvlNode* node) {
        if (node == nullptr)  { 
            return 0;
        }
        
        return node->height;
    }

     // to find the minimum node in a subtree
    AvlNode* minimumNode(AvlNode* node) {
        AvlNode *ptr = node;

        while (ptr->left != nullptr) {
            ptr = ptr->left;
        }

        return ptr;
    }  

    // to calculate the balance factor of a node
    int balancefact (AvlNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        return getHeight(node->left) - getHeight(node->right);
    }    

    // to perform left rotation on a node
    AvlNode* leftRotate(AvlNode* x) {
        AvlNode* y = x->right;
        AvlNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // to perform right rotation on a node
    AvlNode* rightRotate(AvlNode* y) {
        AvlNode* x = y->left;
        AvlNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }      
};
