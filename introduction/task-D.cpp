#include <iostream>

using namespace std;

int main() {
    int curr, scale, destroy, save, days;
    cin >> curr; cin >> scale; cin >> destroy; cin >> save; cin >> days;
    
    for (int i = 0; i < days; i++) {
    	int prev = curr;
        curr *= scale;
        curr -= destroy;
        if (curr <= 0) {
            printf("0");
            return 0;
        }
        curr = (curr > save) ? save : curr;
    	if (curr == prev) break;
    }
    printf("%d", curr);
    return 0;
}