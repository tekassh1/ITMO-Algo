#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main() {
    int n; cin >> n;
    deque<int> first;
    queue<int> second;

    string s;
    getline(cin, s);

    for (int i = 0; i < n; i++) {
        getline(cin, s);
        if (s == "-") {
            if (!second.empty()) {
                cout << second.front() << endl;
                second.pop();

                if (first.size() - second.size() > 1) {
                    int mv_id = first.front();
                    first.pop_front();
                    second.push(mv_id);
                }
            }
            else {
                cout << first.front() << endl;
                first.pop_front();
            }
            continue;
        }

        int space_idx = s.find(' ');
        string op = s.substr(0, space_idx);
        int id = stoi(s.substr(space_idx, s.length() - space_idx));

        if (op == "+") {
            if (first.size() > second.size()) {
                int mv_id = first.front();
                first.pop_front();
                second.push(mv_id);
            }
            first.push_back(id);
        }
        else if (op == "*") {
            if (first.size() > second.size()) {
                int mv_id = first.front();
                first.pop_front();
                second.push(mv_id);
            }
            first.push_front(id);
        }
    }
}