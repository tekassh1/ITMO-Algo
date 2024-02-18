#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

int find_min(vector<int> &data, size_t idx, int heap1, int heap2) {
    if (idx == data.size()) return abs(heap1 - heap2);
    
    int to_first_heap = find_min(data, idx + 1, heap1 + data[idx], heap2);
    int to_second_heap = find_min(data, idx + 1, heap1, heap2 + data[idx]);

    return min(to_first_heap, to_second_heap);
}

int main() {
    size_t n; cin >> n;

    vector<int> data;
    for (int i = 0; i < n; i++) {
        int num; cin >> num; data.push_back(num);
    }

    cout << find_min(data, 0, 0, 0);
}