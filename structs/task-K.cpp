#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

multimap<int, pair<int, bool>, greater<int>> blocks_heap; // size, (start_cell, is_free)
map<int, pair<int, bool>> cells;                          // start_cell, (size, is_free)

void free_block_by_cell(int alloc_size, int cell) {
    multimap<int, pair<int, bool>, greater<int>>::iterator it = blocks_heap.find(alloc_size);
    while (it->second.first != cell) it++;
    blocks_heap.erase(it);
}

void insert(int start_cell, int size, bool is_free) {
    pair<int, bool> new_block = {start_cell, is_free};
    pair<int, bool> new_cell = {size, is_free};

    blocks_heap.insert(make_pair(size, new_block));
    cells.insert(make_pair(start_cell, new_cell));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int cells_am; cin >> cells_am;
    int req_am; cin >> req_am;

    vector<pair<int, int>> alloc_requests;  // start_cell, size

    pair<int, bool> main_block = {1, true};
    blocks_heap.insert(make_pair(cells_am, main_block));

    vector<int> res;

    for (int i = 0; i < req_am; i++) {
        int req; cin >> req;

        if (req > 0) {
            multimap<int, pair<int, bool>, greater<int>>::iterator it = blocks_heap.begin();
            if (it->first < req || it == blocks_heap.end()) {
                cout << -1;
                continue;
            }
            int size = it->first;
            int start_cell = it->second.first;

            blocks_heap.erase(it);
            cells.erase(start_cell);

            insert(start_cell, req, false);

            int rest_size = size - req;
            if (rest_size != 0){
                int rest_start_cell = start_cell + req;
                insert(rest_start_cell, rest_size, true);
            }

            alloc_requests.push_back({start_cell, size});
            res.push_back(start_cell);
        }
        else {
            req = (abs(req)) - 1;
            int alloc_size = alloc_requests[req].second;
            int alloc_start_cell = alloc_requests[req].first;
            free_block_by_cell(alloc_size, alloc_start_cell);
            
            map<int, pair<int, bool>>::iterator it = cells.find(alloc_start_cell);
            map<int, pair<int, bool>>::iterator prev = it--;
            map<int, pair<int, bool>>::iterator next = it++;

            if (it != cells.begin() && it != --cells.end() && 
                prev->second.second && next->second.second) {
                    
                int new_size = prev->second.first + next->second.first + alloc_size;
                int new_start_cell = prev->first;

                cells.erase(prev); cells.erase(it); cells.erase(next);
                insert(new_start_cell, new_size, true);
            }
            else if (it != cells.begin() && prev->second.second) {
                int new_size = prev->second.first + it->second.first;
                int new_start_cell = prev->first;
                cells.erase(prev); cells.erase(it);
                insert(new_start_cell, new_size, true);
            }
            else if (it != --cells.end() && next->second.second) {
                int new_size = it->second.first + next->second.first;
                int new_start_cell = it->first;
                cells.erase(it); cells.erase(next);
                insert(new_start_cell, new_size, true);
            }
        }
    }

    cout << endl;
    for (int cell : res) {
        cout << cell << endl;
    }
}