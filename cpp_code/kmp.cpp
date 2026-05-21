#include<bits/stdc++.h>
using namespace std;

vector<int>createKMP(string &pattern, int n){
    vector<int>res(n, 0);

    int i = 0, len = 1;

    while(len<n){
        if(pattern[i]==pattern[len]){
            res[len] = i+1;
            i++;
            len++;
        } else{
            if(i!=0){
                i = res[i-1];
            } else{
                res[len] = 0;
                len++;
            }
        }
    }

    return res;
}

 int solve(string &pattern, string &text){
    int res = -1;
    int n = pattern.size();
    int m = text.size();
    vector<int>kmp = createKMP(pattern, n);

    int i = 0;
    int j = 0;

    while(i<n && j<m){
        if(pattern[i]==text[j]){
            i++;
            j++;
            if(i==n)return j-n;
        } else{
            if(i!=0){
                i = kmp[i-1];
            } else{
                j++;
            }
        }
    }

    return res;
}

int main(){
string text = "ababcabcabababd";

string pattern = "ababd";

int findIndex = solve(pattern, text);

cout<<findIndex;

return 0;

}