#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int ORDER = 3; // Max keys in a node = ORDER - 1

class BPTreeNode {
public:
    bool isLeaf;
    vector<int> keys;
    vector<BPTreeNode*> children;
    BPTreeNode* next; // for leaf node linkage

    BPTreeNode(bool leaf) {
        isLeaf = leaf;
        next = nullptr;
    }
};

class BPTree {
    BPTreeNode* root;

public:
    BPTree() {
        root = new BPTreeNode(true);
    }

    void insert(int key);
    void display();

private:
    void insertInternal(int key, BPTreeNode* cursor, BPTreeNode* child);
    void displayLeafNodes();
};

// Traverse all leaf nodes (for B+ Tree)
void BPTree::display() {
    cout << "Leaf Nodes: ";
    displayLeafNodes();
    cout << endl;
}

void BPTree::displayLeafNodes() {
    BPTreeNode* cursor = root;
    while (!cursor->isLeaf)
        cursor = cursor->children[0];

    while (cursor != nullptr) {
        for (int key : cursor->keys)
            cout << key << " ";
        cursor = cursor->next;
    }
}

// Insert a key
void BPTree::insert(int key) {
    BPTreeNode* cursor = root;

    // Traverse to leaf
    while (!cursor->isLeaf) {
        int i = 0;
        while (i < cursor->keys.size() && key >= cursor->keys[i])
            i++;
        cursor = cursor->children[i];
    }

    // Insert key in leaf
    cursor->keys.push_back(key);
    sort(cursor->keys.begin(), cursor->keys.end());

    // Split if overflow
    if (cursor->keys.size() < ORDER)
        return;

    BPTreeNode* newLeaf = new BPTreeNode(true);
    int mid = (ORDER + 1) / 2;

    newLeaf->keys.assign(cursor->keys.begin() + mid, cursor->keys.end());
    cursor->keys.resize(mid);

    newLeaf->next = cursor->next;
    cursor->next = newLeaf;

    // Insert into parent
    if (cursor == root) {
        root = new BPTreeNode(false);
        root->keys.push_back(newLeaf->keys[0]);
        root->children.push_back(cursor);
        root->children.push_back(newLeaf);
    } else {
        insertInternal(newLeaf->keys[0], root, newLeaf);
    }
}

// Insert key into internal nodes
void BPTree::insertInternal(int key, BPTreeNode* cursor, BPTreeNode* child) {
    // If current is leaf level, root must be updated already
    if (cursor->isLeaf)
        return;

    // Traverse to internal node just above leaf
    BPTreeNode* parent = nullptr;
    vector<BPTreeNode*> path;
    BPTreeNode* temp = cursor;

    while (!temp->isLeaf) {
        path.push_back(temp);
        int i = 0;
        while (i < temp->keys.size() && key >= temp->keys[i])
            i++;
        parent = temp;
        temp = temp->children[i];
    }

    int pos = 0;
    while (pos < parent->keys.size() && key >= parent->keys[pos])
        pos++;

    parent->keys.insert(parent->keys.begin() + pos, key);
    parent->children.insert(parent->children.begin() + pos + 1, child);

    // Split internal if needed
    if (parent->keys.size() >= ORDER) {
        BPTreeNode* newInternal = new BPTreeNode(false);
        int mid = ORDER / 2;

        int upKey = parent->keys[mid];

        newInternal->keys.assign(parent->keys.begin() + mid + 1, parent->keys.end());
        newInternal->children.assign(parent->children.begin() + mid + 1, parent->children.end());

        parent->keys.resize(mid);
        parent->children.resize(mid + 1);

        if (parent == root) {
            root = new BPTreeNode(false);
            root->keys.push_back(upKey);
            root->children.push_back(parent);
            root->children.push_back(newInternal);
        } else {
            insertInternal(upKey, root, newInternal);
        }
    }
}

int main() {
    BPTree tree;

    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    tree.insert(55);

    tree.display();

    return 0;
}
