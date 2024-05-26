// Optimized torequest for O(1) using dfs and memorized entering in vertex and exit from vertex while dfs.

#include <iostream>
#include <vector>

using namespace std;

struct interval {
    int entry_time;
    int exit_time;
};

vector<vector<int>> vertexes(40000 + 1);
vector<interval> times;
vector<bool> lca_dfs_used;

int max_v;
int last_time = -1;

void dfs(int v) {
    last_time++;
    lca_dfs_used[v] = 1;
    times[v].entry_time = last_time;

    vector<int> childs = vertexes[v];
    for (auto ver : childs) {
        if (!lca_dfs_used[ver]) {
            dfs(ver);
        }
    }
    last_time++;
    times[v].exit_time = last_time;
}

void prepare(int root) {
    lca_dfs_used.assign(max_v + 1, 0);

    interval interv = {.entry_time = -1, .exit_time = -1};
    times.assign(max_v + 1, interv);

    dfs(root);
}

int request(int f, int s) {
    if ((times[f].entry_time <= times[s].entry_time) && (times[f].exit_time >= times[s].exit_time))
        return 1;
    else if ((times[s].entry_time <= times[f].entry_time) && (times[s].exit_time >= times[f].exit_time))
        return 2;
    else return 0;
}

int main() {
    int n;
    cin >> n;

    int root = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        max_v = max(max_v, a);
        max_v = max(max_v, b);
        if (b != -1) vertexes[b].push_back(a);
        else root = a;
    }

    prepare(root);

    int req_am; cin >> req_am;
    for (int i = 0; i < req_am; i++) {
        int f, s;
        cin >> f >> s;
        cout << request(f, s) << endl;
    }

    return 0;
}