#include <iostream>
#include <vector>

using namespace std;

void build(int v, int vl, int vr, vector<long long>& tree, vector<long long>& a) {
    if (vl == vr) {
        tree[v] = a[vl];
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v + 1, vl, vm, tree, a);
    build(2 * v + 2, vm + 1, vr, tree, a);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

long long query(int v, int vl, int vr, vector<long long>& tree, int l, int r) {
    if (l <= vl && vr <= r) {
        return tree[v];
    } else if (l > vr || vl > r) {
        return 0;
    }
    int vm = vl + (vr - vl) / 2;
    long long ql = query(2 * v + 1, vl, vm, tree, l, r);
    long long qr = query(2 * v + 2, vm + 1, vr, tree, l, r);
    return ql + qr;
}

void update(int v, int vl, int vr, vector<long long>& tree, int pos, int val) {
    if (vl == vr) {
        tree[v] = val;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    if (pos <= vm) {
        update(2 * v + 1, vl, vm, tree, pos, val);
    } else {
        update(2 * v + 2, vm + 1, vr, tree, pos, val);
    }
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}
