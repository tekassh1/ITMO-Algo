// Optimized from SPFA - we are looking for shortest path in DAG using toposort for O(V + E)

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int INF = 1e9;

struct node {
    int to;
    int revenue;
};

typedef vector<vector<node>> links;

void toposort(links& lks, vector<bool>& visited, int v, stack<int>& res) {
    visited[v] = true;

    for (node nd : lks[v]) {
        if (!visited[nd.to]) toposort(lks, visited, nd.to, res);
    }
    res.push(v);
}

int main() {
    int n, m; cin >> n >> m;

    links lks(n);

    for (int i = 0; i < m; i++) {
        int s_v, d_v, revenue; cin >> s_v >> d_v >> revenue;
        lks[s_v - 1].push_back({.to = d_v - 1, .revenue = revenue});
    }

    int start, end; cin >> start >> end;
    vector<bool> visited(n, false);
    stack<int> res;

    for (int i = 0; i < n; i++)
        if (!visited[i]) toposort(lks, visited, i, res);

    vector<int> sorted;
    while (!res.empty()) {
        sorted.push_back(res.top());
        res.pop();
    }

    vector<int> dist(n, -INF);
    dist[start - 1] = 0;

    for (int i = 0; i < n; i++) {
        if (dist[sorted[i]] != -INF) {
            for (node nd: lks[sorted[i]]) {
                if (dist[nd.to] < dist[sorted[i]] + nd.revenue) 
                    dist[nd.to] = dist[sorted[i]] + nd.revenue;
            }
        }
    }

    if (dist[end - 1] == -INF) cout << "No solution";
    else cout << dist[end - 1];

    return 0;
}