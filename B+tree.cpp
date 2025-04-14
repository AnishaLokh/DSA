#include <iostream>
#include <vector>

using namespace std;

#define MIN_DEGREE 3

// Node structure for B+ Tree
struct BPlusTreeNode {
    vector<int> keys;               // Store keys in the node
    vector<BPlusTreeNode*> children; // Pointers to child nodes
    BPlusTreeNode* next;            // For linked list of leaf nodes
    bool leaf;                      // Flag to check if it's a leaf node
};

// Function to create a new B+ Tree Node
BPlusTreeNode* createNode(bool isLeaf) {
    BPlusTreeNode* newNode = new BPlusTreeNode();
    newNode->leaf = isLeaf;
    newNode->next = nullptr;
    return newNode;
}

// Function to insert a key into a non-full node
void insertNonFull(BPlusTreeNode* node, int key, int minDegree);

// Function to split a child node when it's full
void splitChild(BPlusTreeNode* parent, int i, BPlusTreeNode* fullChild);

// Function to traverse the B+ Tree
void traverse(BPlusTreeNode* node);

// Insertion function for B+ Tree
void insert(BPlusTreeNode*& root, int key) {
    // If the root is full, split it
    if (root->keys.size() == 2 * MIN_DEGREE - 1) {
        BPlusTreeNode* newRoot = createNode(false);
        newRoot->children.push_back(root);  // Old root becomes the first child
        splitChild(newRoot, 0, root);       // Split the old root
        root = newRoot;                     // New root becomes the updated root
    }
    insertNonFull(root, key, MIN_DEGREE);
}

// Function to insert a key into a non-full node
void insertNonFull(BPlusTreeNode* node, int key, int minDegree) {
    int i = node->keys.size() - 1;

    if (node->leaf) {
        // Find the position to insert the key in the leaf node
        while (i >= 0 && node->keys[i] > key) i--;
        node->keys.insert(node->keys.begin() + i + 1, key);
    } else {
        // Find the child where the key should go
        while (i >= 0 && node->keys[i] > key) i--;
        i++;

        // If the child is full, split it
        if (node->children[i]->keys.size() == 2 * minDegree - 1) {
            splitChild(node, i, node->children[i]);
            if (node->keys[i] < key) i++;
        }

        // Recur for the child
        insertNonFull(node->children[i], key, minDegree);
    }
}

// Function to split a full child node
void splitChild(BPlusTreeNode* parent, int i, BPlusTreeNode* fullChild) {
    BPlusTreeNode* newNode = createNode(fullChild->leaf);
    int mid = MIN_DEGREE - 1;

    // Move half of the keys and children to the new node
    newNode->keys.assign(fullChild->keys.begin() + mid, fullChild->keys.end());
    if (!fullChild->leaf) {
        newNode->children.assign(fullChild->children.begin() + mid, fullChild->children.end());
    }

    // Insert the middle key into the parent node
    parent->keys.insert(parent->keys.begin() + i, fullChild->keys[mid]);
    parent->children.insert(parent->children.begin() + i + 1, newNode);

    // Remove the middle key from the full child
    fullChild->keys.resize(mid);
    fullChild->children.resize(MIN_DEGREE);
}

// Function to traverse and print the B+ Tree (leaf nodes linked)
void traverse(BPlusTreeNode* node) {
    if (node != nullptr) {
        for (int key : node->keys) cout << key << " ";
        if (node->leaf) {
            cout << "| ";  // Indicating the leaf level
            if (node->next) traverse(node->next);  // Traverse through linked leaf nodes
        } else {
            for (BPlusTreeNode* child : node->children) traverse(child);
        }
    }
}

int main() {
    BPlusTreeNode* root = createNode(true);

    // Insert elements into the B+ Tree
    insert(root, 10);
    insert(root, 20);
    insert(root, 5);
    insert(root, 6);
    insert(root, 12);
    insert(root, 30);
    insert(root, 7);
    insert(root, 17);

    cout << "B+ Tree traversal (Leaf nodes linked): ";
    traverse(root);
    cout << endl;

    return 0;
}
