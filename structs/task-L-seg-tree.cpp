#include <climits>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

size_t MAX_ARRAY_SIZE = 150000;
vector<int> tree(2 * MAX_ARRAY_SIZE);

void build_tree(vector<int> arr, size_t v, size_t tl, size_t tr) {
    if (tl == tr) {
        tree[v] = arr[tl];
    }
    else {
        size_t tm = (tl + tr) / 2;
        build_tree(arr, v * 2, tl, tm);
        build_tree(arr, v * 2 + 1, tm + 1, tr);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

void update_element(vector<int> arr, size_t idx, int val, size_t v, size_t tl, size_t tr) {
    if (idx == tl && tr == idx) {
        tree[v] = val;
        arr[idx] = val;
    }
    else if ((idx < tl) || (idx > tr)) {
        return;
    }
    else {
        size_t tm = (tl + tr) / 2;
        update_element(arr, idx, val, v * 2, tl, tm);
        update_element(arr, idx, val, v * 2 + 1, tm + 1, tr);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

int get_min(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
    if (l <= tl && tr <= r)
        return tree[v];
    if ((r < tl) || (l > tr))
        return INT_MAX;

    size_t tm = (tl + tr) / 2;
    return min(get_min(l, r, v * 2, tl, tm),
           get_min(l, r, v * 2 + 1, tm + 1, tr));
}

int main() {
    vector<int> arr;
    vector<int> tree;

    size_t n; cin >> n;
    size_t window; cin >> window;

    for (size_t i = 0; i < n; i++) {
        int num; cin >> num;
        arr.push_back(num);
    }

    build_tree(arr, 1, 0, arr.size() - 1);

    vector<int> res;  
    for (size_t i = 0; i <= arr.size() - window; i++) {
        res.push_back(get_min(i, i + window - 1, 1, 0, n - 1));
    }

    for (int mi : res) {
        cout << mi << " ";
    }
}