#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef struct letter {
    char symb;
    int weight;
    int cnt;
} letter;

bool letter_comparator(letter l1, letter l2) {
    return l1.weight > l2.weight;
}

int main() {
    int weights[26];
    unordered_map<char, letter> map;

    string str; cin >> str;

    for (int i = 0; i < 26; i++) {
        cin >> weights[i];
    }

    for (char symb : str) {
        if (map.find(symb) != map.end()) {
            map[symb].cnt++;

            if (map[symb].cnt == 2) 
                map[symb].weight = weights[symb - 'a'];
        }
        else {
            map[symb].symb = symb;
            map[symb].cnt = 1;
        }

    }

    vector<letter> vec;
    
    for (auto i = map.begin(); i != map.end(); i++) {
        vec.push_back(i -> second);
    }

    sort(vec.begin(), vec.end(), letter_comparator);

    string ansstart = "";
    for (int i = 0; i < vec.size(); i++) {
        ansstart += vec[i].symb;
        vec[i].cnt--;
    }

    string ansend = "";
    for (int i = vec.size() - 1; i >= 0; i--) {
        if (vec[i].cnt != 0) {
            ansend += vec[i].symb;
            vec[i].cnt--;
        }
    }
    
    string ansmid = "";
    for (int i = 0; i < vec.size(); i++) {
        while (vec[i].cnt != 0) {
            ansmid += vec[i].symb;
            vec[i].cnt--;
        }
    }

    cout << ansstart + ansmid + ansend;

    return 0;
}