#include <iostream>
#include <vector>

using namespace std;

vector<int> build(vector<int>& a) {
    int n = (int) a.size();
    vector<int> tree(2 * n);
    for (int i = 0; i < n; i++) {
        tree[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    return tree;
}

int query(vector<int>& tree, int l, int r) {
    int n = (int) tree.size() / 2;
    int ans = INT_MIN;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            ans = max(ans, tree[l++]);
        }
        if (r % 2 == 0) {
            ans = max(ans, tree[r--]);
        }
    }
    return ans;
}

void update(vector<int>& tree, int pos, int val) {
    int n = (int) tree.size() / 2;
    tree[pos += n] = val;
    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
    }
}
