#include <iostream>
#include <cstddef>
#include <map>

using namespace std;

int main() {
    int len;
    cin >> len;

    size_t i = 0, j = 0;
    size_t curr_sz = 0, max_sz = 0;
    size_t start = 0, end = 0;
    size_t counter = 0;

    int curr_nm = 0;
    int prev_nm = 0;

    while (j < len) {
        cin >> curr_nm;

        if (curr_nm == prev_nm) counter++;
        else counter = 0;

        curr_sz++;

        if (counter >= 2) {
            i = j - 1;
            curr_sz = 2;
        }

        if (curr_sz > max_sz) {
            max_sz = curr_sz;
            start = i + 1;
            end = j + 1;
        }

        prev_nm = curr_nm;
        j++;
    }
    
    cout << start << " " << end;
}