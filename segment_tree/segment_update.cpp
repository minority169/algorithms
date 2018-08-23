#include <iostream>
#include <vector>

using namespace std;

struct node {
    long long val = 0;
    long long tba = -1;
};

long long get_value(int v, int vl, int vr, vector<node>& tree) {
    return tree[v].tba == -1 ? tree[v].val : tree[v].tba * (vr - vl + 1);
}

void push(int v, int vl, int vr, vector<node>& tree) {
    if (tree[v].tba == -1) {
        return;
    }
    tree[2 * v + 1].tba = tree[2 * v + 2].tba = tree[v].tba;
    tree[v].tba = -1;
}

void build(int v, int vl, int vr, vector<node>& tree, vector<int> a) {
    if (vl == vr) {
        tree[v].val = a[vl];
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v + 1, vl, vm, tree, a);
    build(2 * v + 2, vm + 1, vr, tree, a);
    tree[v].val = tree[2 * v + 1].val + tree[2 * v + 2].val;
}

long long query(int v, int vl, int vr, vector<node>& tree, int l, int r) {
    if (l <= vl && vr <= r) {
        return get_value(v, vl, vr, tree);
    } else if (l > vr || vl > r) {
        return 0;
    }
    push(v, vl, vr, tree);
    int vm = vl + (vr - vl) / 2;
    tree[v].val = get_value(2 * v + 1, vl, vm, tree) + get_value(2 * v + 2, vm + 1, vr, tree);
    long long ql = query(2 * v + 1, vl, vm, tree, l, r);
    long long qr = query(2 * v + 2, vm + 1, vr, tree, l, r);
    return ql + qr;
}

void segment_update(int v, int vl, int vr, vector<node>& tree, int l, int r, int delta) {
    if (l <= vl && vr <= r) {
        tree[v].tba = delta;
        return;
    } else if (l > vr || vl > r) {
        return;
    }
    push(v, vl, vr, tree);
    int vm = vl + (vr - vl) / 2;
    segment_update(2 * v + 1, vl, vm, tree, l, r, delta);
    segment_update(2 * v + 2, vm + 1, vr, tree, l, r, delta);
    tree[v].val = get_value(2 * v + 1, vl, vm, tree) + get_value(2 * v + 2, vm + 1, vr, tree);
}
