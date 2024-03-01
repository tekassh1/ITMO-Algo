// Optimized to knapstack problem O(nm), vector stores int (TL on 64mb limit)

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

    vector<vector<int>> dp(n + 1, vector<int>(sum / 2 + 1, 0));
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < sum / 2 + 1; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - arr[i - 1] >= 0) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j - arr[i - 1]] + arr[i - 1]);
        }
    }
    
    cout << sum - 2 * dp[n][sum / 2];
}