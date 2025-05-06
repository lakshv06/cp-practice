#include <bits/stdc++.h>
using namespace std;
#define print(a) for(auto it: a){cout<<it<<" ";}

void swap(int &a, int &b){
    if(&a==&b)return;
    a = a^b;
    b = a^b;
    a = a^b;
}

int partition(vector<int>&arr, int lo, int hi){
    int pivot = arr[hi];
    // int i = lo, j = hi;
    int i = lo-1;
    for(int j=lo; j<hi; j++){
        if(arr[j]<=pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    i++;
    swap(arr[hi], arr[i]);

    return i;
}

void quickSort(vector<int>&arr, int lo, int hi){
    if(lo<hi){
        int pi = partition(arr, lo, hi);
        quickSort(arr, lo, pi-1);
        quickSort(arr, pi+1, hi);
    }
}

int main(){
    vector<int>arr = {10, 8, 11, 4, 100};
    cout<<"Array before sorting: ";
    print(arr);
    int n = arr.size();
    quickSort(arr, 0, n-1);
    print(arr);
    return 0;
}