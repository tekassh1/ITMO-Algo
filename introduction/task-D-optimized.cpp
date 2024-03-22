#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b, c, d, k;
    cin >> a; cin >> b; cin >> c; cin >> d; cin >> k;

    int a1 = a * b - c;
    int a2 = a1 * b - c;
    int a3 = a1 * b - c;

    if (a3 < a2) {
        long res = a * pow(b, k - 1) - c*((pow(b, k - 1) - 1)/(b - 1));
        cout << res;
    }
    else {
        cout << "Ne rabotayet, bro";
    }

    return 0;
}