#include <iostream>
#include <vector>

using namespace std;

vector<int> lca_h, lca_dfs_list, lca_pos;
vector<bool> lca_dfs_used;
vector<int> lca_tree;

int max_v;

void lca_dfs(const vector<vector<int>> &vertexes, int v, int h) {
    lca_dfs_used[v] = 1;
    lca_h[v] = h;
    lca_dfs_list.push_back(v);

    vector<int> childs = vertexes[v];
    for (auto ver : childs) {
        if (!lca_dfs_used[ver]) {
            lca_dfs(vertexes, ver, h + 1);
            lca_dfs_list.push_back(v);
            lca_h[v] = h;
        }
    }
}

void lca_build_tree(int i, int l, int r) {
    if (l == r)
        lca_tree[i] = lca_dfs_list[l];
    else {
        int m = (l + r) >> 1;
        lca_build_tree(2 * i, l, m);
        lca_build_tree(2 * i + 1, m + 1, r);
        if (lca_h[lca_tree[2 * i]] < lca_h[lca_tree[2 * i + 1]])
            lca_tree[i] = lca_tree[2 * i];
        else
            lca_tree[i] = lca_tree[2 * i + 1];
    }
}

int lca_tree_min(int i, int sl, int sr, int l, int r) {
	if (sl == l && sr == r)
		return lca_tree[i];

	int sm = (sl + sr) >> 1;

	if (r <= sm)
		return lca_tree_min (2 * i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min (2 * i + 1, sm + 1, sr, l, r);

	int ans1 = lca_tree_min (2 * i, sl, sm, l, sm);
	int ans2 = lca_tree_min (2 * i + 1, sm + 1, sr, sm + 1, r);
    
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca(int a, int b) {
    lca_dfs_used.resize(max_v + 1);

    int left = lca_pos[a], right = lca_pos[b];
    if (left > right) swap(left, right);
    return lca_tree_min(1, 0, lca_dfs_list.size() - 1, left, right);
}

void lca_prepare(const vector<vector<int>> &vertexes, int vertexes_am, int root) {
    lca_pos.assign(max_v + 1, -1);
    lca_dfs_used.assign(max_v + 1, 0);
    lca_h.assign(max_v + 1, -1);

    lca_dfs(vertexes, root, 1);
    lca_tree.assign(lca_dfs_list.size() * 4 + 1, -1);

    lca_build_tree(1, 0, lca_dfs_list.size() - 1);

    for (int i = 0; i < lca_dfs_list.size(); ++i) {
        int v = lca_dfs_list[i];
        if (lca_pos[v] == -1)
            lca_pos[v] = i;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> vertexes(40000 + 1);
    int root = 0;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        max_v = max(max_v, a);
        max_v = max(max_v, b);
        if (b != -1) vertexes[b].push_back(a);
        else root = a;
    }

    lca_prepare(vertexes, n, root);

    int l;
    cin >> l;
    for (int i = 0; i < l; i++) {
        int a,b;
        cin >> a >> b;
        int v = lca(a, b);
        if (v == a) cout << 1 << endl;
        else if (v == b) cout << 2 << endl;
        else cout << 0 << endl;
    }
}