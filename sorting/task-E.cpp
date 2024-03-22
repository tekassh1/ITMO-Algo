#include <iostream>
#include <vector>

using namespace std;

bool check(vector<int> arr, int dist, int cows) {
    int last_coord = arr[0];
    int cntr = 1;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] - last_coord >= dist) {
            cntr++;
            last_coord = arr[i];
        }
        if (cntr >= cows) return true;
    }

    return false;
}

int main() {
    int s; cin >> s;
    int c; cin >> c;

    vector<int> vec;

    for (int i = 0; i < s; i++) {
        int inp; cin >> inp;
        vec.push_back(inp);
    }

    int l = 0;
    int r = vec[vec.size() - 1] - vec[0] + 1;

    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(vec, m, c)) {
            l = m;
        }
        else {
            r = m;
        }
    }
    cout << l;
    return 0;
}