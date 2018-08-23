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

int get_size(node *vert) {
    return vert == nullptr ? 0 : vert->size;
}

void update(node *vert) {
    if (vert == nullptr) {
        return;
    }
    vert->size = get_size(vert->left) + get_size(vert->right) + 1;
}

pair<node *, node *> split(node *root, int key) {
    if (root == nullptr) {
        return make_pair(nullptr, nullptr);
    } else if (root->key < key) {
        pair<node *, node *> splitted = split(root->right, key);
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

void insert(node *&root, node *vert) {
    pair<node *, node *> splitted = split(root, vert->key);
    root = merge(merge(splitted.first, vert), splitted.second);
}

void erase(node *&root, int key) {
    node *left = nullptr, *middle = nullptr, *right = nullptr;
    pair<node *, node *> splitted = split(root, key);
    left = splitted.first;
    splitted = split(splitted.second, key + 1);
    middle = splitted.first;
    right = splitted.second;
    if (middle != nullptr) {
        middle = merge(middle->left, middle->right);
    }
    root = merge(left, middle);
    root = merge(root, right);
}

int kth_maximum(node *root, int k) {
    if (root == nullptr) {
        return -1;
    }
    int right_size = get_size(root->right);
    if (right_size + 1 == k) {
        return root->key;
    } else if (right_size + 1 > k) {
        return kth_maximum(root->right, k);
    } else {
        return kth_maximum(root->left, k - right_size - 1);
    }
}
