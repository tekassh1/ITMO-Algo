#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

int MAX_ENTRY_AM = 500000;

int main() {
    priority_queue<pair<int, int>, vector<pair<int,int>>, less<>> prediction;
    unordered_set<int> cache;

    int n, k, p, actions = 0;
    cin >> n >> k >> p;

    int values[p];
    vector<stack<int>> rest_entries(n);

    for (int i = p - 1; i >= 0; i--) {
        int car; cin >> car;
        values[i] = car;
        rest_entries[car - 1].push(i); 
    }

    for (int i = 0; i < p; i++) {
        int car = values[i];

        if (cache.find(car) == cache.end()) {
            actions++;

            if (cache.size() >= k) {
                cache.erase(prediction.top().second);
                prediction.pop();
            }
            cache.insert(car);
        }
        rest_entries[car - 1].pop();
        if (!rest_entries[car - 1].empty()) {
            prediction.push({rest_entries[car - 1].top(), car});
        }
        else {
            prediction.push({MAX_ENTRY_AM, car});
        }
    }
    cout << actions;
}