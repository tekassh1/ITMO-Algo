// Optimized to knapstack problem O(nm), vector stores bool (no ML on 64mb limit)

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n; cin >> n;
    int sum = 0;

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    if (n == 1) {cout << arr[0]; return 0;}
    vector<vector<bool>> dp(n + 1, vector<bool>(sum / 2 + 1, false));
    dp[0][0] = true;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < sum / 2 + 1; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - arr[i - 1] >= 0)
                dp[i][j] = dp[i][j] || dp[i - 1][j - arr[i - 1]];
        }
    }

    for (int j = sum / 2; j >= 0; j--) {
        if (dp[n][j]) {
            cout << sum - 2 * j;
            break;
        }
    }
}