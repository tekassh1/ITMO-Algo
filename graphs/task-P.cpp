/*
Условия сильной связности
    1. Из любой вершины можно достигнуть любую другую вершину (прямая достижимость).
    2. В любую вершину можно попасть из любой другой вершины (обратная достижимость).
*/ 

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>> &data, vector<int> &visited, int tank_size, int vertex, bool transposed) {
    visited[vertex] = 1;

    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i] && ((transposed ? data[i][vertex] : data[vertex][i]) <= tank_size))
            dfs(data, visited, tank_size, i, transposed);
    }
}

bool is_all_visited(vector<int> &visited) {
    for (int vertex : visited)
        if (!vertex) return false;
    return true;
}

bool check_for_strong_connection(vector<vector<int>> &data, int tank_size) {
    vector<int> visited(data[0].size());

    dfs(data, visited, tank_size, 0, 0);
    bool not_transposed = is_all_visited(visited);

    fill(visited.begin(), visited.end(), 0);

    dfs(data, visited, tank_size, 0, 1);
    bool transposed = is_all_visited(visited);

    return not_transposed && transposed;
}

int main() {
    int n; cin >> n;
    vector<vector<int>> data(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> data[i][j];
        }
    }

    int l = -1, r = pow(10, 9);
    while (l + 1 < r) {
        int m = (l + r) / 2;

        if (check_for_strong_connection(data, m)) r = m;
        else l = m;
    }

    cout << r;
    return 0;
}