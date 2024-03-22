#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool compare_strings(string s1, string s2) {
    if (s1.length() > s2.length()) {
        int rest = s1.length() - s2.length();
        s2 += s1.substr(0, rest);

        if (s1 == s2)
            return s2.substr(0, s2.length() - rest) > s2.substr(rest, s1.length());
    }
    else if (s1.length() < s2.length()) {
        int rest = s2.length() - s1.length();
        s1 += s2.substr(0, rest);

        if (s1 == s2) {
            return s2.substr(rest, s2.length()) > s1.substr(0, s2.length() - rest);
        }
    }

    return s1 > s2;
}

int main() {
    vector<string> nums;
    
    string s;
    while (getline(cin, s)) {
        if (s == "" || s == "\n") break;
        nums.push_back(s);
    }

    sort(nums.begin(), nums.end(), compare_strings);
    for (string num : nums) cout << num;
    return 0;
}

// 432
// 43243