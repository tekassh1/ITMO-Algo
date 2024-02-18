#include <iostream>

using namespace std;

int main() {
    int a, c, h, f;
    int b, g, e, d;

    cin >> a; cin >> b; cin >> c; cin >> d;
    cin >> e; cin >> f; cin >> g; cin >> h;

    if ((a + c + h + f) != (b + g + e + d)) cout << "IMPOSSIBLE";
    else {
        while (true) {
            if (a != 0) {
                if (d != 0)      { a--; d--; cout << "AD-" << endl;}
                else if (b != 0) { a--; b--; cout << "AB-" << endl;}
                else if (e != 0) { a--; e--; cout << "AE-" << endl;}
                else if (g != 0) { b++; f++; cout << "BF+" << endl;}
            }
            else if (c != 0) {
                if (b != 0)      { c--; b--; cout << "CB-" << endl;}
                else if (d != 0) { c--; d--; cout << "CD-" << endl;}
                else if (g != 0) { c--; g--; cout << "CG-" << endl;}
                else if (e != 0) { b++; f++; cout << "BF+" << endl;}
            }
            else if (h != 0) {
                if (g != 0)      { h--; g--; cout << "HG-" << endl;}
                else if (e != 0) { h--; e--; cout << "HE-" << endl;}
                else if (d != 0) { h--; d--; cout << "HD-" << endl;}
                else if (b != 0) { a++; e++; cout << "AE+" << endl;}
            }
            else if (f != 0) {
                if (e != 0)      { f--; e--; cout << "FE-" << endl;}
                else if (g != 0) { f--; g--; cout << "FG-" << endl;}
                else if (b != 0) { f--; b--; cout << "FB-" << endl;}
                else if (d != 0) { a++; e++; cout << "AE+" << endl;}
            }
            else {
                break;
            }
        }
    }
}