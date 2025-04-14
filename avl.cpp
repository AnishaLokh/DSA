#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data, height;
    Node* left, * right;
};

// Utility functions
int height(Node* n) { return n ? n->height : 0; }
int balanceFactor(Node* n) { return height(n->left) - height(n->right); }

Node* createNode(int key) {
    Node* node = new Node{key, 1, nullptr, nullptr};
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return createNode(key);
    if (key < root->data) root->left = insert(root->left, key);
    else if (key > root->data) root->right = insert(root->right, key);

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = balanceFactor(root);

    if (balance > 1 && key < root->left->data) return rightRotate(root);
    if (balance < -1 && key > root->right->data) return leftRotate(root);
    if (balance > 1 && key > root->left->data) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (balance < -1 && key < root->right->data) { root->right = rightRotate(root->right); return leftRotate(root); }

    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->data) root->left = deleteNode(root->left, key);
    else if (key > root->data) root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = root->right;
        while (temp && temp->left) temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0) return rightRotate(root);
    if (balance < -1 && balanceFactor(root->right) <= 0) return leftRotate(root);
    if (balance > 1 && balanceFactor(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (balance < -1 && balanceFactor(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }

    return root;
}

int main() {
    Node* root = nullptr;
    int choice, value;

    while (true) {
        cout << "\n1. Insert\n2. Delete\n3. Inorder\n4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;
            case 3:
                cout << "Inorder traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
