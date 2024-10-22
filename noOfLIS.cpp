#include <bits/stdc++.h>
using namespace std;

// Function to find the length of LIS and the number of such LISs
void solve(vector<int>& arr, int n, vector<int>& dp, vector<int>& noOfLIS) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (dp[i] == dp[j] + 1) {
                    noOfLIS[i] += noOfLIS[j]; // Accumulate count of LISs
                } 
                else if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;  // Update max length
                    noOfLIS[i] = noOfLIS[j]; // Reset count to match new max
                }
            }
        }
    }
}

int main() {
    vector<int> arr = {3, 10, 4, 1, 20, 18};
    int n = arr.size();

    // Initialize dp and noOfLIS vectors
    vector<int> dp(n, 1);     // Every element is a subsequence of length 1
    vector<int> noOfLIS(n, 1); // Each element initially forms one subsequence

    solve(arr, n, dp, noOfLIS);

    // Find the length of the longest increasing subsequence (LIS)
    int maxLength = *max_element(dp.begin(), dp.end());
    int noOfRes = 0;

    // Count the number of LISs with the maximum length
    for (int i = 0; i < n; i++) {
        if (dp[i] == maxLength) {
            noOfRes += noOfLIS[i];
        }
    }

    cout << "Length of LIS: " << maxLength << endl;
    cout << "Number of LIS: " << noOfRes << endl;

    return 0;
}
