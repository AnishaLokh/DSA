#include <iostream>
#include <vector>

using namespace std;

#define MIN_DEGREE 3

// BPlusTreeNode Structure
struct BPlusTreeNode {
    vector<int> keys;
    vector<BPlusTreeNode*> children;
    BPlusTreeNode* next;  // For linked list of leaf nodes
    bool leaf;

    BPlusTreeNode(bool isLeaf);
    void insertNonFull(int key, int minDegree);
    void splitChild(int i, BPlusTreeNode* y, int minDegree);
};

// BPlusTree Structure
struct BPlusTree {
    BPlusTreeNode* root;

    BPlusTree();
    void insert(int key, int minDegree);
    void traverse(BPlusTreeNode* node);
};

BPlusTreeNode::BPlusTreeNode(bool isLeaf) {
    leaf = isLeaf;
    next = nullptr;
}

void BPlusTreeNode::insertNonFull(int key, int minDegree) {
    int i = keys.size() - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > key) i--;
        keys.insert(keys.begin() + i + 1, key);
    } else {
        while (i >= 0 && keys[i] > key) i--;
        i++;

        if (children[i]->keys.size() == 2 * minDegree - 1) {
            splitChild(i, children[i], minDegree);
            if (keys[i] < key) i++;
        }
        children[i]->insertNonFull(key, minDegree);
    }
}

void BPlusTreeNode::splitChild(int i, BPlusTreeNode* y, int minDegree) {
    BPlusTreeNode* z = new BPlusTreeNode(y->leaf);
    int mid = minDegree - 1;

    z->keys.assign(y->keys.begin() + mid, y->keys.end());
    if (!y->leaf) z->children.assign(y->children.begin() + mid, y->children.end());

    keys.insert(keys.begin() + i, y->keys[mid]);
    children.insert(children.begin() + i + 1, z);

    y->keys.resize(mid);
    y->children.resize(minDegree);
}

BPlusTree::BPlusTree() {
    root = new BPlusTreeNode(true);
}

void BPlusTree::insert(int key, int minDegree) {
    if (root->keys.size() == 2 * minDegree - 1) {
        BPlusTreeNode* s = new BPlusTreeNode(false);
        s->children.push_back(root);
        s->splitChild(0, root, minDegree);
        root = s;
    }
    root->insertNonFull(key, minDegree);
}

void BPlusTree::traverse(BPlusTreeNode* node) {
    if (node != nullptr) {
        for (int key : node->keys) cout << key << " ";
        if (node->leaf) {
            cout << " | ";  // Indicating end of leaf level
            if (node->next) traverse(node->next);  // Follow linked list of leaves
        } else {
            for (BPlusTreeNode* child : node->children) traverse(child);
        }
    }
}

int main() {
    BPlusTree tree;

    tree.insert(10, MIN_DEGREE);
    tree.insert(20, MIN_DEGREE);
    tree.insert(5, MIN_DEGREE);
    tree.insert(6, MIN_DEGREE);
    tree.insert(12, MIN_DEGREE);
    tree.insert(30, MIN_DEGREE);
    tree.insert(7, MIN_DEGREE);
    tree.insert(17, MIN_DEGREE);

    cout << "B+ Tree traversal (Leaf nodes linked): ";
    tree.traverse(tree.root);
    cout << endl;

    return 0;
}
