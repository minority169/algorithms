#include <iostream>
#include <vector>

using namespace std;

void update(vector<long long>& tree, int pos, long long val) {
    for (int i = pos; i < tree.size(); i |= i + 1) {
        tree[i] += val;
    }
}

void build(vector<long long>& tree, vector<long long>& a) {
    for (int i = 0; i < a.size(); i++) {
        update(tree, i, a[i]);
    }
}

long long get_sum(vector<long long>& tree, int pos) {
    long long ans = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

long long get_sum(vector<long long>& tree, int l, int r) {
    return get_sum(tree, r) - get_sum(tree, l - 1);
}
