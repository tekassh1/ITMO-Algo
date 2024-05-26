#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    int start_l, start_c, end_l, end_c;
    cin >> n >> m;
    cin >> start_l >> start_c >> end_l >> end_c;

    vector<vector<int>> graph(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char s; cin >> s;

            if (s == '.') graph[i][j] = 1;
            else if (s == 'W') graph[i][j] = 2;
            else graph[i][j] = -1;
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<char>> prev(n, vector<char>(m));
    dist[start_l - 1][start_c - 1] = 0;

    set<pair<int, pair<int, int>>> q;
    q.insert({0, {start_l - 1, start_c - 1}});

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        pair<int, int> nr = q.begin()->second;
        q.erase(q.begin());

        for (const auto& dir : directions) {
            int new_row = nr.first + dir.first;
            int new_col = nr.second + dir.second;

            if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < m && graph[new_row][new_col] != -1) {
                if (dist[new_row][new_col] > dist[nr.first][nr.second] + graph[new_row][new_col]) {
                    q.erase({dist[new_row][new_col], {new_row, new_col}});
                    dist[new_row][new_col] = dist[nr.first][nr.second] + graph[new_row][new_col];
                    q.insert({dist[new_row][new_col], {new_row, new_col}});

                    if (dir.first == -1 && dir.second == 0) prev[new_row][new_col] = 'N';
                    else if (dir.first == 1 && dir.second == 0) prev[new_row][new_col] = 'S';
                    else if (dir.first == 0 && dir.second == -1) prev[new_row][new_col] = 'W';
                    else prev[new_row][new_col] = 'E';
                }
            }
        }
    }

    int path_row = end_l - 1;
    int path_col = end_c - 1;

    if (dist[path_row][path_col] == INF) {
        cout << -1;
        return 0;
    }

    vector<char> path;
    while (!((path_row == start_l - 1) && (path_col == start_c - 1))) {
        path.push_back(prev[path_row][path_col]);

        if (prev[path_row][path_col] == 'N') path_row++;
        else if (prev[path_row][path_col] == 'S') path_row--;
        else if (prev[path_row][path_col] == 'W') path_col++;
        else path_col--;
    }

    cout << dist[end_l - 1][end_c - 1] << endl;
    for (int i = path.size() - 1; i >= 0; i--) cout << path[i];
    return 0;
}