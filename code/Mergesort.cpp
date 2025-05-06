#include<bits/stdc++.h>
using namespace std;
#define print(a) for(auto it: a){cout<<it<<" ";}

void merge(vector<int>&arr, int lo, int mid, int hi){
    int n1 = mid-lo+1;
    int n2 = hi-mid;
    vector<int> left(n1), right(n2);
    
    for (int i = 0; i < n1; i++) left[i] = arr[lo + i];
    for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];
    
    // Merge the two arrays
    int i = 0, j = 0, k = lo;
    
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void mergeSort(vector<int>&arr, int lo, int hi){
    if(lo>=hi)return;

    int mid = lo+(hi-lo)/2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid+1, hi);
    merge(arr, lo, mid, hi);
}

int main(){
    vector<int>arr = {10, 8, 11, 4, 100};
    cout<<"Array before sorting: ";
    print(arr);
    int n = arr.size();
    mergeSort(arr, 0, n-1);
    print(arr);

    return 0;
}