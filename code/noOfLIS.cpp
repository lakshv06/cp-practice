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


//if constraints are- 0<n<10^5 then above one will fail-> we need to use segment tree to do range queries
// https://leetcode.com/problems/longest-increasing-subsequence-ii/

class SegmentTree {
public:
    vector<int> tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree.resize(4 * n, 0);  // Initialize the segment tree with 0s
    }

    // Update the value at index 'pos' in the segment tree
    void update(int pos, int value, int node, int start, int end) {
        if (start == end) {
            tree[node] = max(tree[node], value);  // Update with the max value
        } else {
            int mid = (start + end) / 2;
            if (pos <= mid) {
                update(pos, value, 2 * node + 1, start, mid);
            } else {
                update(pos, value, 2 * node + 2, mid + 1, end);
            }
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    // Query the maximum value in the range [L, R]
    int query(int L, int R, int node, int start, int end) {
        if (R < start || L > end) return 0;  // Out of range
        if (L <= start && end <= R) return tree[node];  // Fully within range

        int mid = (start + end) / 2;
        int leftQuery = query(L, R, 2 * node + 1, start, mid);
        int rightQuery = query(L, R, 2 * node + 2, mid + 1, end);
        return max(leftQuery, rightQuery);
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int maxValue = *max_element(nums.begin(), nums.end());  // Maximum value in nums

        // Initialize a segment tree for values from 0 to maxValue
        SegmentTree segTree(maxValue + 1);

        int maxLIS = 0;

        // Process each number in the input array
        for (int num : nums) {
            // Query the longest LIS in the range [num - k, num - 1]
            int bestLIS = segTree.query(max(0, num - k), num - 1, 0, 0, maxValue);

            // Update the segment tree with the new LIS length for the current number
            segTree.update(num, bestLIS + 1, 0, 0, maxValue);

            // Track the overall maximum LIS length
            maxLIS = max(maxLIS, bestLIS + 1);
        }

        return maxLIS;
    }
};
