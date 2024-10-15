// Online C++ compiler to run C++ program online
#include <iostream>
#include <bits/stdc++.h>

void swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

void merge(std::vector<int>& arr, int lo, int mid, int hi){
    
    int n1 = mid-lo+1;
    int n2 = hi-mid;
    
    std::vector<int>left(n1, 0);
    
    std::vector<int>right(n2, 0);
    
    for(int i=0; i<n1; i++){
        left[i] = arr[i+lo];
    }
    
    for(int i=0; i<n2; i++){
        right[i] = arr[mid+i+1];
    }
    
    int i=0, j=0, k=lo;
    
    while(i<n1 && j<n2){
        if(left[i]<=right[j]){
            arr[k++]=left[i++];
        }
        else{
            arr[k++]=right[j++];
        }
    }
    
    while(i<n1){
        arr[k++]=left[i++];
    }
    
    while(j<n2){
        arr[k++]=right[j++];
    }
    
}

void mergesort(std::vector<int>& arr, int lo, int hi){
    
    if(lo>=hi)return;
    
    int mid = lo+(hi-lo)/2;
    
    mergesort(arr, lo, mid);
    
    mergesort(arr, mid+1, hi);
    
    merge(arr, lo, mid, hi);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the pivot as the last element
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; // Increment the index of the smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(std::vector<int>& arr, int lo, int hi){
    if(lo<hi){
        int pi = partition(arr, lo, hi);
        quicksort(arr, lo, pi - 1);
        quicksort(arr, pi + 1, hi); 
    }
}

int main() {

    std::vector<int>arr1 = {01, -1, 8, -18, 201, 203, 89};
    
    std::vector<int>arr2 = arr1;
    
    int n = arr2.size();
    
    mergesort(arr1, 0, n-1);
    
    std::cout<<"Merge sort result: ";
    for(auto it: arr1){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
    
    quicksort(arr2, 0, n-1);
    
    std::cout<<"Quick sort result: ";
    for(auto it: arr2){
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;

    return 0;
}