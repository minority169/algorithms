#include <iostream>

using namespace std;

struct node {
    int priority, size;
    long long sum, key;
    node *left, *right;
    node(int value) {
        key = value;
        priority = rand();
        size = 1;
        sum = value;
        left = right = nullptr;
    }
};

int get_size(node *root) {
    return root == nullptr ? 0 : root->size;
}

long long get_sum(node *root) {
    return root == nullptr ? 0 : root->sum;
}

void update(node *root) {
    if (root == nullptr) {
        return;
    }
    root->size = get_size(root->left) + get_size(root->right) + 1;
    root->sum = get_sum(root->left) + get_sum(root->right) + root->key;
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

long long get_segment_sum(node *root, int l, int r) {
    pair<node *, node *> splitted = split(root, r + 1);
    node *right = splitted.second;
    splitted = split(splitted.first, l);
    long long ans = get_sum(splitted.second);
    root = merge(merge(splitted.first, splitted.second), right);
    return ans;
}

long long query(node *root0, node *root1, int l, int r) {
    int len0 = (r - l + 1) / 2, len1 = (r - l + 1) / 2;
    if (l % 2 == 0) {
        len0 += (r - l + 1) % 2;
    } else {
        len1 += (r - l + 1) % 2;
    }
    long long q0 = get_segment_sum(root0, (l + 1) / 2, (l + 1) / 2 + len0 - 1);
    long long q1 = get_segment_sum(root1, l / 2 + 1, l / 2 + len1);
    return q0 + q1;
}