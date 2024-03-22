#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    int s; cin >> s;

    int sum = 0;

    vector<int> prices;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        prices.push_back(p);
        sum += p;
    }

    if (s > n) {
        cout << sum;
        return 0;
    }

    sort(prices.begin(), prices.end(), greater<int>());

    int cntr = 1;
    for (auto price : prices) {
        if (cntr % s == 0) sum -= price;
        cntr++;
    }

    cout << sum;

    return 0;
}