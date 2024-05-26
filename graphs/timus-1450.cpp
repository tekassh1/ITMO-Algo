// Bellman–Ford Algorithm modified - SPFA - modified to max cost

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = 1e9;

typedef struct {
    int to;
    int revenue;
} node;

int main() {
    int n, m; cin >> n >> m;

    vector<vector<node>> links(n);

    for (int i = 0; i < m; i++) {
        int s_v, d_v, revenue; cin >> s_v >> d_v >> revenue;
        links[s_v - 1].push_back({.to = d_v - 1, .revenue = revenue});
    }

    int start, end; cin >> start >> end;

    vector<int> dist(n, -INF);
    dist[start - 1] = 0;

    queue<int> q;
    q.push(start - 1);

    vector<bool> in_queue(n, false);
    in_queue[start - 1] = false;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        in_queue[v] = false;

        for (node nd: links[v]) {
            if (dist[nd.to] < dist[v] + nd.revenue) {
                dist[nd.to] = dist[v] + nd.revenue;

                if (!in_queue[nd.to]) {
                    q.push(nd.to);
                    in_queue[nd.to] = true;
                }
            }
        }
    }

    if (dist[end - 1] == -INF) cout << "No solution";
    else cout << dist[end - 1];

    return 0;
}