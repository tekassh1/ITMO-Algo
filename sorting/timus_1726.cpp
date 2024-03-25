#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

bool sort_by_second(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}

int main() {
    size_t n; cin >> n;

    vector<pair<int, int>> coords;

    for (size_t i = 0; i < n; i++) {
        int x;
        int y;
        cin >> x; cin >> y;

        coords.push_back(make_pair(x, y));
    }

    long long sum = 0;
    
    sort(coords.begin(), coords.end());
    for (size_t i = 0; i < n; i++) {
        long long substractions = coords.size() - i - 1;
        sum += 2 * (coords[i].first * i) - 2 * (substractions * coords[i].first);
    }
    
    sort(coords.begin(), coords.end(), sort_by_second);
    for (size_t i = 0; i < n; i++) {
        long long substractions = coords.size() - i - 1;
        sum += 2 * (coords[i].second * i) - 2 * (substractions * coords[i].second);
    }

    long long cntr = n * (n - 1);
    cout << sum / cntr;
}