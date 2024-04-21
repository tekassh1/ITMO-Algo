#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> values;
    multiset<int> st;

    size_t n; cin >> n;
    size_t window; cin >> window;

    for (size_t i = 0; i < n; i++) {
        int num; cin >> num;
        values.push_back(num);
    }

    for (size_t i = 0; i < n ; i++) {
        if (!st.empty() && i >= window)
            st.erase(st.find(values[i - window]));

        st.insert(values[i]);
        if (i + 1 >= window)
            cout << *st.begin() << " ";
    }
}