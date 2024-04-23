#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n; cin >> n;
    stack<int> rest;
    int prev = 0;
    rest.push(0);
    for (int i = 0; i < n; i++) {
        int ball; cin >> ball;
        if (ball > prev) {
            for (int j = prev + 1; j < ball; j++) rest.push(j);
            prev = ball;
        }
        else {
            if (rest.top() != ball) {
                cout << "Cheater";
                return 0;
            }
            rest.pop();
        }
    }
    cout << "Not a proof";
}