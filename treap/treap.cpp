#include <iostream>

using namespace std;

struct node {
    int key, priority;
    node *left, *right;
    
    node(int value) {
        key = value;
        priority = rand();
        left = right = nullptr;
    }
};

pair<node *, node *> split(node *root, int key) {
    if (root == nullptr) {
        return make_pair(nullptr, nullptr);
    } else if (root->key < key) {
        pair<node *, node *> splitted = split(root->right, key);
        root->right = splitted.first;
        return make_pair(root, splitted.second);
    } else {
        pair<node *, node *> splitted = split(root->left, key);
        root->left = splitted.second;
        return make_pair(splitted.first, root);
    }
}

node *merge(node *left, node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    } else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void insert(node *&root, node *vert) {
    if (root == nullptr) {
        root = vert;
        return;
    } else if (root->priority > vert->priority) {
        if (vert->key < root->key) {
            insert(root->left, vert);
        } else {
            insert(root->right, vert);
        }
    } else {
        pair<node *, node *> splitted = split(root, vert->key);
        vert->left = splitted.first;
        vert->right = splitted.second;
        root = vert;
    }
}

void erase(node *&root, int key) {
    if (root == nullptr) {
        return;
    }
    if (key < root->key) {
        erase(root->left, key);
    } else if (key > root->key) {
        erase(root->right, key);
    } else {
        root = merge(root->left, root->right);
    }
}
