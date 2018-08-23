#include <iostream>

using namespace std;

struct node {
    int key, priority, size;
    node *left, *right;
    node(int value) {
        key = value;
        priority = rand();
        size = 1;
        left = right = nullptr;
    }
};

int get_size(node *root) {
    return root == nullptr ? 0 : root->size;
}

void update(node *root) {
    if (root == nullptr) {
        return;
    }
    root->size = get_size(root->left) + get_size(root->right) + 1;
}

pair<node *, node *> split(node *root, int key) {
    if (root == nullptr) {
        return make_pair(nullptr, nullptr);
    }
    int left_size = get_size(root->left);
    if (left_size + 1 < key) {
        pair<node *, node *> splitted = split(root->right, key - left_size - 1);
        root->right = splitted.first;
        update(root);
        return make_pair(root, splitted.second);
    } else {
        pair<node *, node *> splitted = split(root->left, key);
        root->left = splitted.second;
        update(root);
        return make_pair(splitted.first, root);
    }
}

node *merge(node *left, node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    } else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

void insert(node *&root, int key) {
    root = merge(root, new node(key));
}
