/*
Codeforces 2010 C2, C1

At the Berland State University, the local network between servers does not always operate without errors. When transmitting two 
identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the 
first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of 
the merging must be a positive number less than the length of the message text.

For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described 
type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at 
one character, and in the second case, at four).

Given the received message t, determine if it is possible that this is the result of an error of the described type in the operation of
the local network, and if so, determine a possible value of s.

A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is 
"abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an 
error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

Input
The input consists of a single non-empty string t, consisting of lowercase letters of the Latin alphabet. The length of the string t does 
not exceed 100 characters.

Output
If the message t cannot contain an error, output "NO" (without quotes) in a single line of output.

Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string s — a possible message that could 
have led to the error. If there are multiple possible answers, any of them is acceptable.

*/

#pragma GCC optimize("O3") // Optimize with level 3
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <functional>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
using namespace std;

#define int long long int
#define double long double
#define all(x) x.begin(), x.end()
#define done(x) cout<<x<<endl; return;
#define endl '\n'
#define pii pair<int, int>

const int MOD = 1e9 + 7;

// const pii pq;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

vector<int> findDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first < b.first;
}

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

struct LexicographicalCompare {
    bool operator()(const std::string& a, const std::string& b) const {
        return (a + b) < (b + a);
    }
};

bool cmp1(const int &a, const int &b){
	return a>b;
}

bool cmp2(const pair<double, int>& a, const pair<double, int>& b, const vector<int>& aVector){
    if (a.first == b.first) {
        return aVector[a.second] < aVector[b.second];
    }
    return a.first < b.first;
}

 // Use a lambda to capture aVector and pass it to cmp2
    // std::sort(vec.begin(), vec.end(), [&aVector](const std::pair<double, int>& a, const std::pair<double, int>& b) {
    //     return cmp2(a, b, aVector);
    // });

int minimumDifference(vector<int>& nums) {
    int n = nums.size(),  sum = 0;
    sum = accumulate(nums.begin(), nums.end(),0);  // To find the total sum of the array 
    
    int N = n/2; // Divide it into two equals parts as length is even
    vector<vector<int>> left(N+1), right(N+1); // left array and right array
    
	//All possible sum in left and right part (Generating and storing using BIT-Masking)
    for(int mask = 0; mask<(1<<N); ++mask){  // (1<<n) means 2^n i.e we'll iterate through 0 to 2^n
        int idx = 0, l_sum = 0, r_sum = 0;
        for(int i=0; i<N; ++i){
            if(mask&(1<<i)){  // To check if the bit is set or not 
                idx++;
                l_sum += nums[i];
                r_sum += nums[i+N];
            }
        }
        cout<<idx<<endl;
        left[idx].push_back(l_sum);
        right[idx].push_back(r_sum);   // storing
    }

    for(int idx=0; idx<=N; ++idx){
        sort(right[idx].begin(), right[idx].end());   // as we'll perform binary search on right so we have to sort it first
    }

 int res = min(abs(sum-2*left[N][0]), abs(sum-2*right[N][0]));  // To get the minimum answer from the max sum from both array
		//iterating over left part
		for(int idx=1; idx<N; ++idx){ // iterate from 1 so we dont have to include 0 and check for all value except last as we have alr considered it
			for(auto &a : left[idx]){ // check the sum at each number position
				int b = (sum - 2*a)/2; // find the value to be minimized 
				int rightidx = N-idx; // find the number value in right array
				auto &v = right[rightidx]; // store the vector in v at right number position
				auto itr = lower_bound(v.begin(), v.end(),b); //binary search over right part

				if(itr!=v.end()) res = min(res, abs(sum-2*(a+(*itr)))); // if found in vector then only update otherwise continue

				}                
			}
		return res;

	}

vector<int> computeLPS(const string &t) {
    int n = t.size();
    vector<int> lps(n, 0); 
    int len = 0;
    int i = 1;

    // Build the LPS array
    while (i < n) {
        if (t[i] == t[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void solve() {
    string t;
    cin >> t;
    int n = t.size();

    vector<int> lps = computeLPS(t);

    if (lps[n - 1] > n / 2) {
        int len = lps[n - 1]; 
        string s = t.substr(0, len);

        cout << "YES" << endl;
        cout << s << endl;
    } else {
        cout << "NO" << endl;
    }
}


int32_t main() {
	// Remove for Interactive Problems
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
 
	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
 
	int testcases=1; 
	// cin>>testcases;
	for (;testcases > 0; testcases--) {
		// cout<<testcases<<endl;
		solve();
		
	}
	cerr<<"Time : "<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<endl;
	return 0;
}