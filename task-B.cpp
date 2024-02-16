#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

typedef pair<int, char> node;

bool is_uppercase(char symb) { return (symb >= 'A' && symb <= 'Z'); }

int main() {
    stack<node> stack;
    vector<int> catched;

    char curr_symb;
    int animal_idx = 1;
    int trap_idx = 1;

    while (curr_symb = getchar()) {
        if (curr_symb == '\n') break;
        node curr_node;

        bool is_upper = is_uppercase(curr_symb); 
        if (!is_upper) {
            curr_node.first = animal_idx++;
        }
        else {
            catched.push_back(0);
            curr_node.first = trap_idx++;
        }
        curr_node.second = curr_symb;

        if (!stack.empty() && 
            curr_symb != stack.top().second && 
            (curr_symb == tolower(stack.top().second) || curr_symb == toupper(stack.top().second))) {
        
            node curr_trap = is_upper ? curr_node : stack.top();
            int trap_idx = curr_trap.first;
            int animal_catched_idx = is_upper ? stack.top().first : curr_node.first;

            catched[trap_idx - 1] = animal_catched_idx;
            stack.pop();
        }
        else {
            stack.push(curr_node);
        }
    }
    
    if (!stack.empty()) {
        cout << "Impossible";
    }
    else {
        cout << "Possible" << endl;
        for (int c : catched) cout << c << " ";
    }
}