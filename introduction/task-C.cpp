#include <iostream>
#include <string>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    unordered_map<string, stack<int>> state;
    stack<unordered_set<string>> changed;

    unordered_set<string> set;
    changed.push(set);

    string s;
    while (getline(cin, s)) {
        if (s == "\n" || s == "") break;
        if (s == "{") {
            unordered_set<string> set;
            changed.push(set);
        }
        else if (s == "}") {
            for (auto var : changed.top()) {
                state[var].pop();
                if (state[var].empty()) state.erase(var);
            }
            changed.pop();
        }
        else {
            int del_idx = s.find('=');
            string f_arg = s.substr(0, del_idx);
            string s_arg = s.substr(del_idx + 1, s.length());

            bool f_arg_layer_changed = changed.top().find(f_arg) != changed.top().end();

            if (isdigit(s_arg[0]) || s_arg[0] == '-') {
                if (f_arg_layer_changed) state[f_arg].pop();
                state[f_arg].push(stoi(s_arg));
            }
            else {
                if (state.find(s_arg) == state.end()) {
                    if (f_arg_layer_changed) state[f_arg].pop();
                    state[f_arg].push(0);
                }
                else {
                    int s_arg_val = state[s_arg].top();
                    if (f_arg_layer_changed) state[f_arg].pop();
                    state[f_arg].push(s_arg_val);
                }
                cout << state[f_arg].top() << endl;
            }
            changed.top().insert(f_arg);
        }
    }
}