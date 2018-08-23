#include <iostream>
#include <vector>

using namespace std;

void update(vector<vector<long long>>& tree, int posx, int posy, long long val) {
    for (int i = posx; i < tree.size(); i |= i + 1) {
        for (int j = posy; j < tree[i].size(); j |= j + 1) {
            tree[i][j] += val;
        }
    }
}

void build(vector<vector<long long>>& tree, vector<vector<long long>>& a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            update(tree, i, j, a[i][j]);
        }
    }
}

long long get_sum(vector<vector<long long>>& tree, int posx, int posy) {
    long long ans = 0;
    for (int i = posx; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = posy; j >= 0; j = (j & (j + 1)) - 1) {
            ans += tree[i][j];
        }
    }
    return ans;
}

long long get_sum(vector<vector<long long>>& tree, int x1, int y1, int x2, int y2) {
    return get_sum(tree, x2, y2) - get_sum(tree, x1 - 1, y2) - get_sum(tree, x2, y1 - 1) + get_sum(tree, x1 - 1, y1 - 1);
}
