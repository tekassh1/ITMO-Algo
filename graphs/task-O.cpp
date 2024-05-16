#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

enum color {
    black,
    white
};

typedef struct {
    bool visited;
    color col;
} status;

int main() {
    int n, m; cin >> n; cin >> m;
    vector<status> nodes(n + 1);
    vector<unordered_set<int>> links(n + 1);

    for (int i = 0; i < m; i++) {
        int f, s; cin >> f >> s;
        links[f].insert(s);
        links[s].insert(f);
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!nodes[i].visited) {
            nodes[i].col = black;
            q.push(i);
        }

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            nodes[vertex].visited = 1;

            for (int elem: links[vertex]) {
                if (nodes[elem].visited && (nodes[elem].col == nodes[vertex].col)) {
                    cout << "NO";
                    return 0;
                }
                if (!nodes[elem].visited) {
                    nodes[elem].col = (nodes[vertex].col == black) ? white : black;
                    q.push(elem);
                }
                
            }
        }
    }
    cout << "YES";
    return 0;
}