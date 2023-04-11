#include <iostream>
#include <fstream>
#include <sstream>
#include "Node.h"
#include <string>

using namespace std;

//Delete all nodes in the tree
void clearTree(Node* n) {
    if (n != nullptr) {
        clearTree(n->left);
        clearTree(n->right);
        delete n;
    }
}

//Search for a node with key k in the tree rooted at x
void iterativeTreeSearch(Node* x, int k) {
    cout << "Looking for " << k << "... ";
    while (x != NULL && k != x->key) {
        cout << x->key << " ";
        if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    // If the value is found, print the tree in preorder and indicate that the value was found
    if (x != NULL) {
        cout << x->key << " ";
        cout << " : found" << endl;
    }
    // If the value is not found, print the tree in preorder and indicate that the value was not found
    else {
        cout << " : not found" << endl;
    }
}

//Insert a new node with key k into the tree rooted at root
void treeInsert(Node*& root, int k)
{
    Node* node = new Node(k);
    if (!root) {
        root = node;
        return;
    }
    Node* prev = NULL;
    Node* temp = root;
    //Find the correct position to insert the new node
    while (temp) {
        if (temp->key > k) {
            prev = temp;
            temp = temp->left;
        }
        else if (temp->key < k) {
            prev = temp;
            temp = temp->right;
        }
    }
    if (prev->key > k)
        prev->left = node;
    else
        prev->right = node;
}

//Traverse the tree in pre-order and print out the keys of each node
void preOrder(Node* n) {
    if (n != NULL) {
        cout << n->key << " ";
        preOrder(n->left);
        preOrder(n->right);
    }
}

//Traverse the tree in in-order and print out the keys of each node
void inOrder(Node* n) {
    if (n != NULL) {
        inOrder(n->left);
        cout << n->key << " ";
        inOrder(n->right);
    }
}

//Traverse the tree in post-order and print out the keys of each node
void postOrder(Node* n) {
    if (n != NULL) {
        postOrder(n->left);
        postOrder(n->right);
        cout << n->key << " ";
    }
}


int main(int argc, char** argv)
{
    //Check for command line error
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }

    //Check for file
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    // Get value of n
    string value;
    getline(ifs, value);
    int n = stoi(value);

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        string line;
        getline(ifs, line);         

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "ADD") {
            // Read the integer value to add to the tree
            int num;
            iss >> num;
            // Insert the value into the tree
            cout << "Adding " << num << endl;
            treeInsert(root, num);
        }
        else if (command == "FIND") {
            // Read the integer value to search for
            int num;
            iss >> num;
            // Search for the value in the tree
            iterativeTreeSearch(root, num);
        }
        else if (command == "CLEAR") {
            // Delete the entire tree and set the root pointer to null
            clearTree(root);
            cout << "(tree deleted!)" << endl;
            root = NULL;
        }
        else if (command == "PREORDER") {
            // Print the tree in preorder
            cout << "PREORDER: ";
            preOrder(root);
            cout << endl;
        }
        else if (command == "INORDER") {
            // Print the tree in inorder
            cout << "INORDER: ";
            inOrder(root);
            cout << endl;
        }
        else if (command == "POSTORDER") {
            // Print the tree in postorder
            cout << "POSTORDER: ";
            postOrder(root);
            cout << endl;
        }
        else {
            // If the command is not recognized, print an error message
            cout << "Invalid command: " << command << endl;
        }

    }

}
