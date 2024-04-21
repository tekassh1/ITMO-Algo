#include <iostream>

using namespace std;

int main() {
    int curr, scale, destroy, save, days;
    cin >> curr; cin >> scale; cin >> destroy; cin >> save; cin >> days;
    days = min(days, 1000);

    for (int i = 0; i < days; i++) {
        curr *= scale;
        curr -= destroy;
        if (curr <= 0) {
            printf("0");
            return 0;
        }
        curr = (curr > save) ? save : curr;
    }
    printf("%d", curr);
    return 0;
}












// #include <iostream>
// #include <cmath>

// using namespace std;

// int main() {
//     int a, b, c, d, k;
//     cin >> a; cin >> b; cin >> c; cin >> d; cin >> k;

//     int a1 = a * b - c;
//     int a2 = a1 * b - c;
//     int a3 = a1 * b - c;

//     if (a3 < a2) {
//         long res = a * pow(b, k - 1) - c*((pow(b, k - 1) - 1)/(b - 1));
//         cout << res;
//     }
//     else {
//         cout << "Ne rabotayet, bro";
//     }

//     return 0;
// }

// #include <iostream>
// #include <cmath>

// typedef long long ll;
// using namespace std;

// int main() {
//     ll a, b, c, d, k;
//     cin >> a >> b >> c >> d >> k;

//     a = b * a - c;
//     a = min(a, d);
//     a = max(a, 0ll);
//     k--;

//     ll num_up   = d * b - d - c;
//     ll num_down =           - c;
//     ll den      = a * b - a - c;

//     double bk = pow(b, k);

//     if (den == 0) {
//         cout << a << '\n';
//         return 0;
//     }

//     int sign = den / abs(den);
//     if (num_down * sign >= den * sign && num_down * sign < bk * den * sign) {
//         cout << 0 << '\n';
//         return 0;
//     }

//     if (num_up * sign >= den * sign && num_up * sign < bk * den * sign) {
//         cout << d << '\n';
//         return 0;
//     }

//     if (b == 1) {
//         if (k > a / c)
//             cout << 0 << '\n';
//         else
//             cout << max(a - c * k, 0ll) << '\n';
//         return 0;
//     }

//     cout << ((ll) bk * (a * b - a - c) + c) / (b - 1) << '\n';
// }