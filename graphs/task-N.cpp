#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n; cin >> n;
    if (n == 1) {
        cout << 1;
        return 0;
    }

    vector<bool> visited(n + 1);
    vector<unordered_set<int>> links(n + 1);
    
    for (int i = 1; i <= n; i++) {
        int in; cin >> in;
        links[i].insert(in);
        links[in].insert(i);
    }

    queue<int> q;
    int cntr = 0;
    for (int i = 1; i < links.size(); i++) {
        if (!visited[i]) {
            q.push(i);
            cntr++;
        }
        while (!q.empty()) {
            int elem = q.front();
            q.pop();
            visited[elem] = 1;

            for (int num : links[elem]) {
                if (!visited[num]) q.push(num);
            }
        }
    }
    cout << cntr;
}