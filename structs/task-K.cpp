#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

multimap<int, pair<int, bool>, greater<int>> blocks_heap; // size, (start_cell, is_free)
map<int, pair<int, bool>> cells;                          // start_cell, (size, is_free)
vector<pair<int, int>> alloc_requests;                    // start_cell, size

auto find_block_by_cell(int cell, int alloc_size) {
    auto it = blocks_heap.find(alloc_size);
    while (it->second.first != cell) it++;
    return it;
}

void insert_cell(int start_cell, int size, bool is_free) {
    pair<int, bool> new_cell = {size, is_free};
    cells.insert(make_pair(start_cell, new_cell));
}

void insert_block(int start_cell, int size) {
    pair<int, bool> new_block = {start_cell, true};
    blocks_heap.insert(make_pair(size, new_block));
}

void insert(int start_cell, int size) {
    insert_block(start_cell, size);
    insert_cell(start_cell, size, true);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int cells_am; cin >> cells_am;
    int req_am; cin >> req_am;

    pair<int, bool> main_block = {1, true};
    blocks_heap.insert(make_pair(cells_am, main_block));

    vector<int> res;

    for (int i = 0; i < req_am; i++) {
        int req; cin >> req;

        if (req > 0) {
            auto it = blocks_heap.begin();
            if (it->first < req || it == blocks_heap.end()) {
                res.push_back(-1);
                alloc_requests.push_back({-1, 0});
                continue;
            }
            int size = it->first;
            int start_cell = it->second.first;

            blocks_heap.erase(it);
            cells.erase(start_cell);

            insert_cell(start_cell, req, false);

            int rest_size = size - req;
            if (rest_size != 0){
                int rest_start_cell = start_cell + req;
                insert(rest_start_cell, rest_size);
            }
            res.push_back(start_cell);
            alloc_requests.push_back({start_cell, req});
        }
        else {
            req = (abs(req)) - 1;

            int alloc_size = alloc_requests[req].second;
            int alloc_start_cell = alloc_requests[req].first;
            
            if (alloc_requests[req].first == -1) {
                alloc_requests.push_back({-1, 0});
                continue;
            }

            auto it = cells.find(alloc_start_cell);
            auto prev = it;
            auto next = it;
            prev--;
            next++;

            if (it != cells.begin() && it != --cells.end() && 
                prev->second.second && next->second.second) {
                    
                int new_size = prev->second.first + next->second.first + alloc_size;
                int new_start_cell = prev->first;

                auto prev_block = find_block_by_cell(prev->first, prev->second.first);
                auto next_block = find_block_by_cell(next->first, next->second.first);

                cells.erase(prev); cells.erase(it); cells.erase(next);
                blocks_heap.erase(prev_block); blocks_heap.erase(next_block);

                insert(new_start_cell, new_size);
            }
            else if (it != cells.begin() && prev->second.second) {
                int new_size = prev->second.first + it->second.first;
                int new_start_cell = prev->first;

                auto prev_block = find_block_by_cell(prev->first, prev->second.first);

                cells.erase(prev); cells.erase(it);
                blocks_heap.erase(prev_block);

                insert(new_start_cell, new_size);
            }
            else if (it != --cells.end() && next->second.second) {
                int new_size = it->second.first + next->second.first;
                int new_start_cell = it->first;

                auto next_block = find_block_by_cell(next->first, next->second.first);

                cells.erase(it); cells.erase(next);
                blocks_heap.erase(next_block); 
                insert(new_start_cell, new_size);
            }
            else {
                cells.erase(it);
                insert(alloc_start_cell, alloc_size);
            }
            alloc_requests.push_back({-1, 0});
        }
    }

    for (int cell : res) {
        cout << cell << endl;
    }
}