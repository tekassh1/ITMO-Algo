#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef struct pumpkin {
    int idx;
    int x_coord;
    int y_coord;
    double angle;
    int dist;
} pumpkin;

bool pumpkin_comparator(pumpkin p1, pumpkin p2) {
    if (p1.angle != p2.angle)
        return p1.angle < p2.angle;
    else
        return p1.dist < p2.dist;
}

int main() {
    int n; cin >> n;

    vector<pumpkin> vec;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int y; cin >> y;

        pumpkin p;
        p.idx = i + 1;
        p.x_coord = x;
        p.y_coord = y;
        p.angle = 0;
        p.dist = 0;

        if (i != 0) {
            double angle_rad = atan2(y - vec[0].y_coord, x - vec[0].x_coord);
            
            p.dist = sqrt(pow(x - vec[0].x_coord, 2) + pow(y - vec[0].y_coord, 2));
            p.angle = angle_rad;
        }
        vec.push_back(p);
    }
    sort(vec.begin() + 1, vec.end(), pumpkin_comparator);
    
    int max_gap_idx_f = 0;
    int max_gap_idx_s = 1;

    for (int i = 1; i < vec.size(); i++) {
        double gap = vec[i].angle - vec[i - 1].angle;
        if (gap >= M_PI) {
            max_gap_idx_f = i - 1;
            max_gap_idx_s = i;
        }
    }
    
    cout << n << endl << 1 << endl;

    for (int i = max_gap_idx_s; i < vec.size(); i++) {
        cout << vec[i].idx << endl;
    }

    for (int i = 1; i <= max_gap_idx_f; i++) {
        cout << vec[i].idx << endl;
    }

    return 0;
}