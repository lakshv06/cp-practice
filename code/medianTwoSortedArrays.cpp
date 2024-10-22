#include <bits/stdc++.h>
using namespace std;

// median of two sorted arrays
double findMedian1(vector<int>& arr1, vector<int>& arr2, int n1, int n2) {
    int n = n1 + n2;
    vector<int> resVector(n, 0);
    int i = 0, j = 0, k = 0;

    // Merge the two arrays into resVector
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            resVector[k++] = arr1[i++];
        } else {
            resVector[k++] = arr2[j++];
        }
    }
    while (i < n1) {
        resVector[k++] = arr1[i++];
    }
    while (j < n2) {
        resVector[k++] = arr2[j++];
    }

    // Find and return the median
    if (n % 2 == 1) {
        return resVector[n / 2];
    } else {
        return (resVector[n / 2] + resVector[(n / 2) - 1]) / 2.0;
    }
}

double findMedian2(vector<int>& arr1, vector<int>& arr2, int n1, int n2) {
    // Ensure that we are doing binary search on the smaller array
    if (n1 > n2) return findMedian2(arr2, arr1, n2, n1);

    int lo = 0, hi = n1;  // Search space in the smaller array
    int N = (n1 + n2 + 1) / 2;  // Half of the total elements (rounded up)

    while (lo <= hi) {
        int mid1 = lo + (hi - lo) / 2;
        int mid2 = N - mid1;

        // Handle edge cases where partition splits at array boundaries
        int l1 = (mid1 == 0) ? INT_MIN : arr1[mid1 - 1];
        int l2 = (mid2 == 0) ? INT_MIN : arr2[mid2 - 1];
        int r1 = (mid1 == n1) ? INT_MAX : arr1[mid1];
        int r2 = (mid2 == n2) ? INT_MAX : arr2[mid2];

        // Check if we have found the correct partition
        if (l1 <= r2 && l2 <= r1) {
            if ((n1 + n2) % 2 == 1) {
                return max(l1, l2);  // Odd length case
            } else {
                return (max(l1, l2) + min(r1, r2)) / 2.0;  // Even length case
            }
        } else if (l1 > r2) {
            hi = mid1 - 1;  // Move left in arr1
        } else {
            lo = mid1 + 1;  // Move right in arr1
        }
    }

    return 0.0;  // Should never reach here
}

double solve(vector<int>& arr1, vector<int>& arr2, int n1, int n2) {
    // Choose between the two methods
    double res1 = findMedian1(arr1, arr2, n1, n2);
    double res2 = findMedian2(arr1, arr2, n1, n2);

    // return res1;
    return res2;
}

int main() {
    vector<int> arr1 = { -5, 3, 6, 12, 15, 16 };
    vector<int> arr2 = { -12, -10, -6, -3, 4, 10 };

    int n1 = arr1.size();
    int n2 = arr2.size();

    double median = solve(arr1, arr2, n1, n2);
    cout << "Median: " << median << endl;

    return 0;
}